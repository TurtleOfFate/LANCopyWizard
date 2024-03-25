#pragma once
#include <qwidget.h>
#include <QHBoxLayout>
#include <QPushButton>

class QLineEdit;
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

	QPushButton* pathBrowse;
private slots:
	void onBrowse();
	//void onBrowse(QLineEdit* path);
};