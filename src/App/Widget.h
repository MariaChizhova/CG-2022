#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QWidget>

class Widget: public QWidget {
public:
	Widget(QWidget *parent = nullptr);
	QLabel * thresholdLabel_;
	QLabel *iterationsLabel_;
	QSlider *thresholdEdit;
	QSlider *iterationsEdit;
	QLabel *fpsLabel_;
	QLabel *fpsLabelValue_;
};