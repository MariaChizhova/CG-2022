#include "FractalWindow.h"

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QScreen>
#include <array>

void FractalWindow::init()
{
	// Configure shaders
	program_ = std::make_unique<QOpenGLShaderProgram>(this);
	program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/diffuse.vs");
	program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/diffuse.fs");
	program_->link();

	// Bind attributes
	program_->bind();

	std::string path = "../../../cookies/scene.gltf";
	model_ = std::unique_ptr<ModelLoader>(new ModelLoader(path, *program_, this));

	// Release all
	program_->release();

	vao_.release();

	ibo_.release();
	vbo_.release();

	// Uncomment to enable depth test and face cullin
	glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_CULL_FACE);

	// Clear all FBO buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FractalWindow::render()
{
	// Configure viewport
	const auto retinaScale = devicePixelRatio();
	glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate MVP matrix
	QMatrix4x4 model, view, projection;
	view.lookAt(cameraPos_, cameraPos_ + cameraDirection_, {0.0f, 1.0f, 0.0f});
	projection.perspective(60.0f, 4.0f / 3.0f, 0.3f, 100.0f);

	// Bind VAO and shader program
	program_->bind();
	vao_.bind();

	// Update uniform value
	program_->setUniformValue(program_->uniformLocation("model"), model);
	program_->setUniformValue(program_->uniformLocation("view"), view);
	program_->setUniformValue(program_->uniformLocation("projection"), projection);
	program_->setUniformValue(program_->uniformLocation("lightPos"), lightPos_);
	program_->setUniformValue(program_->uniformLocation("viewPos"), cameraPos_);
	program_->setUniformValue(program_->uniformLocation("isVertex"), isVertex_);
	program_->setUniformValue(program_->uniformLocation("time"), magic_time_ / 3000.0f);
	model_->Draw();

	// Release VAO and shader program
	program_->release();

	// Increment frame counter
	++frame_;
	int fps = int((double)frame_ / ((double)time_.elapsed() * 0.001));
	fpsLabel_->setText(QString::number(fps));
	if (frame_ % 100 != 0)
	{
		time_.start();
		frame_ = 0;
	}
}


void FractalWindow::setMagicTime(int time)
{
	magic_time_ = time;
}

void FractalWindow::setVertex(bool isVertex)
{
	isVertex_ = isVertex;
}
