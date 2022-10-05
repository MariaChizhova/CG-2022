#include "Widget.h"
#include <QHBoxLayout>
#include <QSlider>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
	QGridLayout *grid = new QGridLayout();
	iterationsLabel_ = new QLabel("Iterations: ", this);
	iterationsEdit = new QSlider(this);
	iterationsEdit->setOrientation(Qt::Horizontal);
	iterationsEdit->setMaximum(300);
	iterationsEdit->setMinimum(0);
	iterationsEdit->setValue(100);
	thresholdLabel_ = new QLabel("Threshold: ", this);
	thresholdEdit = new QSlider(this);
	thresholdEdit->setOrientation(Qt::Horizontal);
	thresholdEdit->setMaximum(150);
	thresholdEdit->setMinimum(0);
	thresholdEdit->setValue(2);

	grid->addWidget(iterationsLabel_, 0, 0);
	grid->addWidget(iterationsEdit, 0, 1);
	grid->addWidget(thresholdLabel_, 1, 0);
	grid->addWidget(thresholdEdit, 1, 1);
	setLayout(grid);
}