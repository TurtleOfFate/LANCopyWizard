#pragma once
#include "PathRowWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"
#include <qdebug.h>
#include <QSignalMapper>
#include <QLineEdit>


PathRowWidget::PathRowWidget(QWidget* parent) : QWidget(parent)
{
	 pathFrom = new QLineEdit(this);
	 pathTo = new QLineEdit(this);
	 pathSpacer = new QSpacerItem(1,1);
	 rowLayout_ = new QHBoxLayout(this);
	 rowLayout_->addWidget(pathFrom);
	 rowLayout_->addSpacerItem(pathSpacer);
	 rowLayout_->addWidget(pathTo);
	 this->setLayout(rowLayout_);
}