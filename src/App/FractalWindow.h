#pragma once

#include <Base/GLWindow.hpp>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>

#include <QElapsedTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>
#include <unordered_map>

#include "ModelLoader.h"

class FractalWindow final : public fgl::GLWindow
{

public:
	explicit FractalWindow(QLabel * fpsLabel)
		: fpsLabel_(fpsLabel){};
	void init() override;
	void render() override;
	void setMagicTime(int time);
	void setVertex(bool isVertex);

private:
	int magic_time_ = 0;
	bool isVertex_ = true;

	QOpenGLBuffer vbo_{QOpenGLBuffer::Type::VertexBuffer};
	QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};
	QOpenGLVertexArrayObject vao_;

	std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;
	std::unique_ptr<ModelLoader> model_;

	QVector3D cameraPos_{0, 8, 20};
	QVector3D lightPos_{2, 4, -4};
	QVector3D cameraDirection_{0, 0, -10};

	size_t frame_ = 0;
	QElapsedTimer time_;
	QLabel * fpsLabel_;
};