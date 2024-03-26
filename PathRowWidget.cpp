#pragma once
#include "PathRowWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"
#include <qdebug.h>
#include <QSignalMapper>
#include <QLineEdit>
#include <QFileDialog>
#include <QCoreApplication>

PathRowWidget::PathRowWidget(QWidget* parent) : QWidget(parent)
{
	fileDialog_ = new QFileDialog(parent);

	connect(fileDialog_, &QFileDialog::currentChanged, this, [&](const QString& str)
	{
		QFileInfo info(str);
		if (info.isFile())
			fileDialog_->setFileMode(QFileDialog::ExistingFile);
		else if (info.isDir())
			fileDialog_->setFileMode(QFileDialog::Directory);		
	});

	 pathBrowse = new QPushButton("...", this);
	 pathFrom_ = new QLineEdit(this);
	 pathTo_ = new QLineEdit(this);
	 pathSpacer_ = new QSpacerItem(1,1);
	 rowLayout_ = new QHBoxLayout(this);
	 rowLayout_->addWidget(pathBrowse);
	 rowLayout_->addWidget(pathFrom_);
	 rowLayout_->addSpacerItem(pathSpacer_);
	 rowLayout_->addWidget(pathTo_);
	
	 fileDialog_->setOption(QFileDialog::DontUseNativeDialog);

	 QObject::connect(pathBrowse, SIGNAL(clicked()), this, SLOT(onChooseFileBrowse()));	
	 QObject::connect(fileDialog_, SIGNAL(finished(int)), this, SLOT(onChooseFileFinished(int)));

	 this->setLayout(rowLayout_);
}

void PathRowWidget::onChooseFileBrowse()
{
	fileDialog_->open();
}

void PathRowWidget::onChooseFileFinished(int result)
{
	if (result == QDialog::Rejected)
		return;
	QStringList files = fileDialog_->selectedFiles();
	if (files.empty())
		return;
	pathFrom_->setText(files[0]);
}

