#include "Widget.h"
#include <QHBoxLayout>
#include <QSlider>

Widget::Widget(QWidget * parent)
	: QWidget(parent)
{
	QGridLayout * grid = new QGridLayout();
	timeSlider_ = new QLabel("Magic: ", this);
	timeSliderEdit_ = new QSlider(this);
	timeSliderEdit_->setOrientation(Qt::Horizontal);
	timeSliderEdit_->setMaximum(3000);
	timeSliderEdit_->setMinimum(0);
	timeSliderEdit_->setValue(0);
	fpsLabel_ = new QLabel("FPS: ", this);
	fpsLabelValue_ = new QLabel(QString::number(0), this);
	fragment = new QRadioButton("Fragment", this);
	vertex = new QRadioButton("Vertex", this);
	vertex->setChecked(true);

	grid->addWidget(timeSlider_, 0, 0);
	grid->addWidget(timeSliderEdit_, 0, 1);
	grid->addWidget(fpsLabel_, 2, 0);
	grid->addWidget(fpsLabelValue_, 2, 1);
	grid->addWidget(vertex, 3, 0);
	grid->addWidget(fragment, 3, 1);
	setLayout(grid);
}