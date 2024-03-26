#include "PathSelectionWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"
#include <qdebug.h>
#include <QSignalMapper>
#include "PathRowWidget.h"
#include <QLabel>
#include <QHBoxLayout>

PathSelectionWidget::PathSelectionWidget( QWidget* parent) : QWidget(parent)
{
	parentLayout_ = new QVBoxLayout(this);

	QHBoxLayout* labelLayout = new QHBoxLayout();
	QLabel* labelFrom = new QLabel("    copy from", this);
	QLabel* labelTo = new QLabel("  copy to", this);
	labelLayout->setSpacing(100);
	labelLayout->addWidget(labelFrom);
	labelLayout->addWidget(labelTo);
	parentLayout_->addLayout(labelLayout);

	pathList_ = new QListWidget(this);	
	pathList_->setSelectionBehavior(QAbstractItemView::SelectItems);
	pathList_->setSelectionMode(QAbstractItemView::ExtendedSelection);
	addPathItemToList(pathList_);

	addPathField = new QPushButton("add new path", this);
	Submit= new QPushButton("submit paths", this);

	parentLayout_->addWidget(pathList_);
	parentLayout_->addWidget(addPathField);
	parentLayout_->addWidget(Submit);

	this->setLayout(parentLayout_);

	createConnections();
}



void PathSelectionWidget::addPathItemToList(QListWidget *list)
{
	pathRows_.push_back(new PathRowWidget(this)); 
	auto newRow = pathRows_.back();

	QListWidgetItem* item = new QListWidgetItem(list);
	item->setData(Qt::ItemDataRole::ToolTipRole, QObject::tr("I'm TOOLTIP 1"));
	item->setSizeHint(newRow->sizeHint());
	list->setItemWidget(item, newRow);
}


void PathSelectionWidget::createConnections()
{
	QObject::connect(Submit, SIGNAL(clicked()), this, SLOT(onSubmitClicked()));
	QObject::connect(addPathField, SIGNAL(clicked()), this, SLOT(onAddPathClicked()));
}

void PathSelectionWidget::onSubmitClicked()
{
	qDebug() << "submitpath" << '\n';
}


void PathSelectionWidget::onAddPathClicked()
{
	addPathItemToList(pathList_);
}