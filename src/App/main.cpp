#include <QApplication>
#include <QSurfaceFormat>

#include "FractalWindow.h"
#include "Widget.h"

namespace
{
constexpr auto g_sampels = 16;
constexpr auto g_gl_major_version = 3;
constexpr auto g_gl_minor_version = 3;
}// namespace

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSamples(g_sampels);
	format.setVersion(g_gl_major_version, g_gl_minor_version);
	format.setProfile(QSurfaceFormat::CoreProfile);

	FractalWindow window;
	window.setFormat(format);

	QWidget * container = QWidget::createWindowContainer(&window);
	container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout * layout = new QVBoxLayout(nullptr);
	Widget * widget = new Widget();
	layout->addWidget(container);
	layout->addWidget(widget, 0, Qt::Alignment(Qt::AlignBottom));
	QObject::connect(widget->iterationsEdit, &QSlider::valueChanged, &window,
					 &FractalWindow::setIterations);
	QObject::connect(widget->thresholdEdit, &QSlider::valueChanged, &window,
					 &FractalWindow::setThreshold);
	auto window1 = new QWidget;
	window1->resize(640, 480);
	window1->setLayout(layout);
	window1->show();

	window.setAnimated(true);
	return app.exec();
}