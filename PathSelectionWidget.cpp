#include "PathSelectionWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"
#include <qdebug.h>
#include <QSignalMapper>
#include "PathRowWidget.h"

PathSelectionWidget::PathSelectionWidget( QWidget* parent) : QWidget(parent)
{

	parentLayout_ = new QVBoxLayout(this);
	pathRows_.push_back( new PathRowWidget(this)); // добавляем первую строку с путями в вектор
	auto firstRow = pathRows_.back();
	addParhField= new QPushButton(this);
	Submit= new QPushButton(this);


	
	parentLayout_->addWidget(Submit);
	parentLayout_->addWidget(addParhField);


	pathList_ = new QListWidget(this);
	parentLayout_->addWidget(pathList_);
	pathList_->setSelectionBehavior(QAbstractItemView::SelectItems);
	pathList_->setSelectionMode(QAbstractItemView::ExtendedSelection);


	QListWidgetItem* item = new QListWidgetItem(pathList_);
	//item->setFlags(item->flags() & (~Qt::ItemIsUserCheckable));
	//item->setCheckState(Qt::CheckState::Unchecked);
	item->setData(Qt::ItemDataRole::ToolTipRole, QObject::tr("I'm TOOLTIP 1"));
	//item->setData(Qt::DisplayRole, QObject::tr(address.getAddress().toUtf8()));
	item->setSizeHint(firstRow->sizeHint());
	//lstWgt->setItemWidget(item, wgt);
	pathList_->setItemWidget(item, firstRow);

	this->setLayout(parentLayout_);

	createConnections();

}
void PathSelectionWidget::createConnections()
{
	QObject::connect(Submit, SIGNAL(clicked()), this, SLOT(onSubmitClicked()));
	QObject::connect(addParhField, SIGNAL(clicked()), this, SLOT(onAddPathClicked()));
}

void PathSelectionWidget::onSubmitClicked()
{
	qDebug() << "submitpath" << '\n';
}


void PathSelectionWidget::onAddPathClicked()
{
	pathRows_.push_back(new PathRowWidget(this)); // добавляем строку с путями в вектор
	auto newRow = pathRows_.back();

	QListWidgetItem* item = new QListWidgetItem(pathList_);

	//item->setFlags(item->flags() & (~Qt::ItemIsUserCheckable));
	//item->setCheckState(Qt::CheckState::Unchecked);
	item->setData(Qt::ItemDataRole::ToolTipRole, QObject::tr("I'm TOOLTIP %1").arg(pathRows_.size()));
	//item->setData(Qt::DisplayRole, QObject::tr(address.getAddress().toUtf8()));
	pathList_->setItemWidget(item, newRow);
	qDebug() << "submitpath" << '\n';
}