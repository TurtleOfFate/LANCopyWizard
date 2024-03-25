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
	 pathBrowse = new QPushButton("...", this);
	 pathFrom = new QLineEdit(this);
	 pathTo = new QLineEdit(this);
	 pathSpacer = new QSpacerItem(1,1);
	 rowLayout_ = new QHBoxLayout(this);
	 rowLayout_->addWidget(pathBrowse);
	 rowLayout_->addWidget(pathFrom);
	 rowLayout_->addSpacerItem(pathSpacer);
	 rowLayout_->addWidget(pathTo);

	 QObject::connect(pathBrowse, SIGNAL(clicked()), this, SLOT(onBrowse()));
	// QObject::connect(addPathField, SIGNAL(clicked()), this, SLOT(onAddPathClicked()));

	 this->setLayout(rowLayout_);
}

void PathRowWidget::onBrowse()
{

	QString runPath = QCoreApplication::applicationDirPath(); // Get the root path of the project
	QString file_name = QFileDialog::getOpenFileName(this, QStringLiteral("Select a document"), runPath, "", nullptr, QFileDialog::DontResolveSymlinks);
//	QString file_name = QFileDialog::getExistingDirectory(0, "Select a Directory", pathFrom->text(), QFileDialog::DontResolveSymlinks);

	if (!file_name.isEmpty())
	{
		pathFrom->setText(file_name);
	}
}