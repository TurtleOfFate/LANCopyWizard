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
	 pathSpacer = new QSpacerItem(10,10);
	 rowLayouts_ = new QHBoxLayout(this);
}