#include <QApplication>
#include <QRadioButton>
#include <QSurfaceFormat>
#include <QVBoxLayout>
#include <QWidget>

#include "FractalWindow.h"
#include "Widget.h"

#define STB_IMAGE_IMPLEMENTATION
#include "assimp/contrib/stb/stb_image.h"


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
	format.setDepthBufferSize(16);

	Widget * widget = new Widget(nullptr);
	FractalWindow * window = new FractalWindow(widget->fpsLabelValue_);
	window->setFormat(format);

	QWidget * container = QWidget::createWindowContainer(window);
	container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	auto window1 = new QWidget();

	QVBoxLayout * layout = new QVBoxLayout(nullptr);
	layout->addWidget(container);

	QObject::connect(widget->fragment, &QRadioButton::toggled, window, [&](bool checked) { if (checked) window->setVertex(false); });
	QObject::connect(widget->vertex, &QRadioButton::toggled, window, [&](bool checked) { if (checked) window->setVertex(true); });
	QObject::connect(widget->timeSliderEdit_, &QSlider::valueChanged, window, [&](int x) { window->setMagicTime(x); });
	layout->addWidget(widget, 0, Qt::Alignment(Qt::AlignBottom));

	window1->setLayout(layout);
	window1->showFullScreen();
	window1->show();

	window->setAnimated(true);

	return app.exec();
}