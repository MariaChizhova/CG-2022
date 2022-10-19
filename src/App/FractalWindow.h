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

class FractalWindow final : public fgl::GLWindow
{

public:
	explicit FractalWindow(QLabel *fpsLabel): fpsLabel_(fpsLabel){};
	void init() override;
	void render() override;
	void setIterations(int iterations);
	void setThreshold(float threshold);

protected:
	void mousePressEvent(QMouseEvent * e) override;
	void mouseReleaseEvent(QMouseEvent * e) override;
	void mouseMoveEvent(QMouseEvent * e) override;
	void wheelEvent(QWheelEvent * e) override;

private:
	GLint iterationsUniform_ = -1;
	GLint thresholdUniform_ = -1;
	GLint zoomUniform_ = -1;
	GLint shiftUniform_ = -1;

	int iterations_ = 100;
	float threshold_ = 2.0;

	QOpenGLBuffer vbo_{QOpenGLBuffer::Type::VertexBuffer};
	QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};
	QOpenGLVertexArrayObject vao_;

	std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

	size_t frame_ = 0;
	QVector2D mousePressPosition_{0., 0.};
	float zoom_ = 0.5;
	QVector2D globalShift_{0., 0.};
	QVector2D shift_{0., 0.};
	bool isPressed_ = false;
	float fps_ = 0;
	QElapsedTimer time_;
	QLabel * fpsLabel_;
};