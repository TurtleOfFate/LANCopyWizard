#pragma once
#include "PathRowWidget.h"
#include <qlistwidget.h>
#include <qdebug.h>
#include <QSignalMapper>
#include <QLineEdit>
#include <QFileDialog>
#include <QCoreApplication>
#include <QLabel>
#include <QWidget>
#include <QAction>
#include "LanSender.h"

PathRowWidget::PathRowWidget(int num , LanSender* sender, QWidget* parent) : QWidget(parent)
{
	rowNumber = num;
	this->sender = sender;
	createFileDialog();
	createEditPaths();
	createRowLayout();
}

void PathRowWidget::createFileDialog()
{
	fileDialog_ = new QFileDialog(this);

	connect(fileDialog_, &QFileDialog::currentChanged, this, [&](const QString& str)
		{
			QFileInfo info(str);
			if (info.isFile())
			{
				fileDialog_->setFileMode(QFileDialog::ExistingFile);
			}
			else if (info.isDir())
			{
				fileDialog_->setFileMode(QFileDialog::Directory);
			}
		});

	fileDialog_->setOption(QFileDialog::DontUseNativeDialog);
	QObject::connect(fileDialog_, SIGNAL(finished(int)), this, SLOT(onChooseFileFinished(int)));
}

void PathRowWidget::createEditPaths()
{
	pathFrom_ = new QLineEdit(this);
	currentEditPath_ = pathFrom_;

	pathTo_ = new QLineEdit(this);

	QIcon browseFolderIcon;
	QSize pixSize = QSize(64, 64);
	browseFolderIcon.addPixmap(style()->standardIcon(QStyle::SP_DirIcon).pixmap(pixSize), QIcon::Normal, QIcon::On);

	QAction* onPathFromFolderBrowseClicked = pathFrom_->addAction(browseFolderIcon, QLineEdit::ActionPosition::TrailingPosition);
	connect(onPathFromFolderBrowseClicked, &QAction::triggered, this, std::bind(&PathRowWidget::onChooseFileBrowse, this, pathFrom_));
	connect(pathFrom_, SIGNAL(textChanged(const QString&)), SLOT(onPushFromPathToSender(const QString&)));

	QAction* onPathToFolderBrowseClicked = pathTo_->addAction(browseFolderIcon, QLineEdit::ActionPosition::TrailingPosition);
	connect(onPathToFolderBrowseClicked, &QAction::triggered, this, std::bind(&PathRowWidget::onChooseFileBrowse, this, pathTo_));
	connect(pathTo_, SIGNAL(textChanged(const QString&)), SLOT(onPushToPathToSender(const QString&)));
}



void PathRowWidget::createRowLayout()
{
	pathSpacer_ = new QSpacerItem(1, 1);
	rowLayout_ = new QHBoxLayout(this);
	rowLayout_->addWidget(pathFrom_);
	rowLayout_->addSpacerItem(pathSpacer_);
	rowLayout_->addWidget(pathTo_);
	this->setLayout(rowLayout_);
}


void PathRowWidget::onChooseFileBrowse(QLineEdit* chosenEditPath)
{
	fileDialog_->open();
	currentEditPath_ = chosenEditPath;
}

void PathRowWidget::onChooseFileFinished(int result)
{
	if (result == QDialog::Rejected)
		return;
	QStringList files = fileDialog_->selectedFiles();
	if (files.empty())
		return;
	QString chosenPath = files[0];
	if (currentEditPath_ == pathFrom_)
	currentEditPath_->setText(chosenPath);
	currentEditPath_->setToolTip(chosenPath);
}

void PathRowWidget::onPushFromPathToSender(const QString& from)
{
	sender->PushFromPathToSend(from, rowNumber);
}
void PathRowWidget::onPushToPathToSender(const QString& to)
{
	sender->PushToPathToSend(to, rowNumber);
}