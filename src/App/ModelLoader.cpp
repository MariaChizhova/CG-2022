#include "ModelLoader.h"

ModelLoader::ModelLoader(const std::string & path, QOpenGLShaderProgram & program, QOpenGLFunctions * functions)
	: program_(program)
	, functions_(functions)
{
	load(path);
}


void ModelLoader::Draw()
{
	for (auto & mesh: meshes_)
	{
		mesh->Draw(program_, *functions_);
	}
}


void ModelLoader::load(const std::string & path)
{
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FixInfacingNormals);

	if (!scene || !scene->mRootNode)
	{
		qDebug() << "Error loading file: " << importer.GetErrorString();
		exit(1);
	}
	dir_ = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void ModelLoader::processNode(aiNode * node, const aiScene * scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(processMesh(mesh, scene));
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

std::unique_ptr<Mesh> ModelLoader::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
		if (mesh->HasNormals())
		{
			vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
		}
		if (mesh->mTextureCoords[0])
		{
			vertex.tex_coords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
			vertex.tangent = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
			vertex.bitangent = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
		}


		QVector3D product = vertex.normal * vertex.bitangent * vertex.tangent;
		if (std::signbit(product.x()) ||
			std::signbit(product.y()) ||
			std::signbit(product.z()))
		{
			std::swap(vertex.tangent, vertex.bitangent);
			vertex.normal = -vertex.bitangent*vertex.tangent;
		}
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
	for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, i, &path);;
		unsigned int texture_id;
		functions_->glGenTextures(1, &texture_id);
		int width, height, number_of_components;
		unsigned char * data = stbi_load((dir_ + '/' + path.C_Str()).c_str(), &width, &height, &number_of_components, 0);
		if (data)
		{
			functions_->glBindTexture(GL_TEXTURE_2D, texture_id);
			functions_->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			functions_->glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
	}
	return std::make_unique<Mesh>(vertices, indices, program_);
}