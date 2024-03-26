#include "PathSelectionWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"
#include <qdebug.h>
#include <QSignalMapper>
#include "PathRowWidget.h"
#include <QLabel>
#include <QHBoxLayout>

PathSelectionWidget::PathSelectionWidget(QWidget* parent) : QWidget(parent)
{
	parentLayout_ = new QVBoxLayout(this);

	QHBoxLayout* labelLayout = new QHBoxLayout();
	QLabel* labelFrom = new QLabel("    Copy from", this);
	QLabel* labelTo = new QLabel("  Copy to", this);
	labelLayout->setSpacing(100);
	labelLayout->addWidget(labelFrom);
	labelLayout->addWidget(labelTo);
	parentLayout_->addLayout(labelLayout);

	pathList_ = new QListWidget(this);	
	pathList_->setSelectionBehavior(QAbstractItemView::SelectItems);
	pathList_->setSelectionMode(QAbstractItemView::ExtendedSelection);
	addToList(pathList_);

	addPath_ = new QPushButton("Add", this);
	deletePath_= new QPushButton("Delete", this);

	parentLayout_->addWidget(pathList_);
	parentLayout_->addWidget(addPath_);
	parentLayout_->addWidget(deletePath_);

	this->setLayout(parentLayout_);

	createConnections();
}

void PathSelectionWidget::addToList(QListWidget *list)
{
	pathRows_.push_back(new PathRowWidget(this)); 
	auto newRow = pathRows_.back();

	QListWidgetItem* item = new QListWidgetItem(list);
	item->setSizeHint(newRow->sizeHint());
	list->setItemWidget(item, newRow);
}

void PathSelectionWidget::createConnections()
{
	QObject::connect(deletePath_, SIGNAL(clicked()), this, SLOT(onDeletePathClicked()));
	QObject::connect(addPath_, SIGNAL(clicked()), this, SLOT(onAddPathClicked()));
}

void PathSelectionWidget::deleteSelectedFromList(QListWidget* list)
{
	qDeleteAll(list->selectedItems());
}


void PathSelectionWidget::onAddPathClicked()
{
	addToList(pathList_);
}

void PathSelectionWidget::onDeletePathClicked()
{
	deleteSelectedFromList(pathList_);
}