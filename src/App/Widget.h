#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>

class Widget: public QWidget {
public:
	Widget(QWidget *parent = nullptr);
	QLabel *timeSlider_;
	QSlider *timeSliderEdit_;
	QLabel *fpsLabel_;
	QLabel *fpsLabelValue_;
	QRadioButton *fragment;
    QRadioButton *vertex;
};