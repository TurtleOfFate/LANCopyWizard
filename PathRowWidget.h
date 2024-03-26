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

	QLineEdit* currentEditPath_;
	QLineEdit* pathFrom_;
	QLineEdit* pathTo_;
	QSpacerItem* pathSpacer_;
	QHBoxLayout* rowLayout_;

private slots:

	void onChooseFileBrowse(QLineEdit* chosenEditPath);
	void onChooseFileFinished(int result);
};