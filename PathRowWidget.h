#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QHBoxLayout>


class PathRowWidget : public QWidget
{
	Q_OBJECT

public:
	PathRowWidget(QWidget* parent = nullptr);
private:

	QLineEdit* pathFrom;
	QLineEdit* pathTo;
	QSpacerItem* pathSpacer;
	QHBoxLayout* rowLayout_;

private slots:

};