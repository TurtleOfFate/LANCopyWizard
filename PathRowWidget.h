#pragma once
#include <qwidget.h>
#include <QHBoxLayout>
#include <QPushButton>
#include "qfiledialog.h"
class QLineEdit;
class FileDialog;
class QFileDialog;

class PathRowWidget : public QWidget
{
	Q_OBJECT

public:
	PathRowWidget(QWidget* parent = nullptr);


private:
	QFileDialog* fileDialog_;

	QLineEdit* pathFrom_;
	QLineEdit* pathTo_;
	QSpacerItem* pathSpacer_;
	QHBoxLayout* rowLayout_;
	QPushButton* pathBrowse;

private slots:
	void onChooseFileBrowse();
	void onChooseFileFinished(int result);
};