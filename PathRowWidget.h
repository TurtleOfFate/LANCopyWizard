#pragma once
#include <qwidget.h>
#include <QHBoxLayout>
#include <QPushButton>
#include "qfiledialog.h"
class QLineEdit;
class FileDialog;
class QFileDialog;
class LanSender;

class PathRowWidget : public QWidget
{
	Q_OBJECT

public:
	PathRowWidget(int num, LanSender* sender,QWidget* parent = nullptr);



private:
	void createFileDialog();
	void createEditPaths();
	void createRowLayout();

private:
	QFileDialog* fileDialog_;

	QLineEdit* currentEditPath_;
	QLineEdit* pathFrom_;
	QLineEdit* pathTo_;
	QSpacerItem* pathSpacer_;
	QHBoxLayout* rowLayout_;
	int rowNumber;
	LanSender* sender;


private slots:

	void onChooseFileBrowse(QLineEdit* chosenEditPath);
	void onChooseFileFinished(int result);
	void onPushFromPathToSender(const QString&);
	void onPushToPathToSender(const QString&);
};