#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector2D>
#include <QVector3D>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/contrib/stb/stb_image.h>

struct Vertex {
	QVector3D position;
	QVector3D normal;
	QVector2D tex_coords;
	QVector3D tangent;
	QVector3D bitangent;
};

class Mesh
{
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	QOpenGLBuffer vbo_{QOpenGLBuffer::Type::VertexBuffer};
	QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};
	QOpenGLVertexArrayObject vao_;

public:
	Mesh(
		const std::vector<Vertex> & vertices,
		const std::vector<unsigned int> & indices,
		QOpenGLShaderProgram & program)
	{
		this->vertices_ = vertices;
		this->indices_ = indices;

		vao_.create();
		vao_.bind();

		vbo_.create();
		vbo_.bind();
		vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
		vbo_.allocate(vertices_.data(), static_cast<int>(vertices_.size() * sizeof(Vertex)));

		ibo_.create();
		ibo_.bind();
		ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
		ibo_.allocate(indices_.data(), static_cast<int>(indices_.size() * sizeof(unsigned int)));

		program.enableAttributeArray(0);
		program.setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, position), 3, sizeof(Vertex));

		program.enableAttributeArray(1);
		program.setAttributeBuffer(1, GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));

		program.enableAttributeArray(2);
		program.setAttributeBuffer(2, GL_FLOAT, offsetof(Vertex, tex_coords), 2, sizeof(Vertex));

		program.enableAttributeArray(3);
		program.setAttributeBuffer(3, GL_FLOAT, offsetof(Vertex, tangent), 3, sizeof(Vertex));

		program.enableAttributeArray(4);
		program.setAttributeBuffer(4, GL_FLOAT, offsetof(Vertex, bitangent), 3, sizeof(Vertex));
		vao_.release();
	}

	void Draw(QOpenGLShaderProgram & program, QOpenGLFunctions & functions)
	{
		program.setUniformValue(program.uniformLocation("texture_diffuse"), 0);
		functions.glBindTexture(GL_TEXTURE_2D, 1);
		vao_.bind();
		functions.glDrawElements(GL_TRIANGLES, static_cast<int>(indices_.size()), GL_UNSIGNED_INT, nullptr);
		vao_.release();
		functions.glActiveTexture(GL_TEXTURE0);
	}
};

class ModelLoader
{
public:
	ModelLoader(const std::string & path, QOpenGLShaderProgram & program, QOpenGLFunctions * functions);
	void Draw();

private:
	std::vector<std::unique_ptr<Mesh>> meshes_;
	QOpenGLShaderProgram & program_;
	QOpenGLFunctions * functions_;
	std::string dir_;

	void load(const std::string & path);
	void processNode(aiNode * node, const aiScene * scene);
	std::unique_ptr<Mesh> processMesh(aiMesh * mesh, const aiScene * scene);
};
