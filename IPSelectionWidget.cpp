#include "IPSelectionWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"
#include <qdebug.h>
#include <QSignalMapper>
#include <QHostInfo>

IPSelectionWidget::IPSelectionWidget(const QVector<IPAddress> &addresses,QWidget* parent) : QWidget(parent)
{
	
	ipList_ = new QListWidget(this);
	refresh_ = new QPushButton("refresh", this);
	CopyToSelected = new QPushButton("copy to selected ip", this);

	parentLayout_ = new QVBoxLayout(this);
	parentLayout_->addWidget(ipList_);
	parentLayout_->addWidget(refresh_);
	parentLayout_->addWidget(CopyToSelected);

	ipList_->setSelectionBehavior(QAbstractItemView::SelectItems);
	ipList_->setSelectionMode(QAbstractItemView::ExtendedSelection);
	
	for (int i = 0; i < addresses.size(); i++)
	{
		const IPAddress &address = addresses[i];
		QListWidgetItem* item = new QListWidgetItem(ipList_);

		item->setFlags(item->flags() & (~Qt::ItemIsUserCheckable));
		item->setCheckState(Qt::CheckState::Unchecked);
		item->setData(Qt::ItemDataRole::ToolTipRole, QObject::tr("I'm TOOLTIP %1").arg(i));
		item->setData(Qt::DisplayRole, QObject::tr(address.getAddress().toUtf8()));
	}
	this->setLayout(parentLayout_);	
	

	createConnections();
}

void IPSelectionWidget::createConnections()
{
	QObject::connect(ipList_, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onItemPressed(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onItemActivated(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemEntered(QListWidgetItem*)), this, SLOT(onItemEntered(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onItemChanged(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem *)), this, SLOT(currentItemChanged(QListWidgetItem*, QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onIpClicked(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemSelectionChanged()), this, SLOT(highlightChecked()));
	QObject::connect(ipList_, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
}

void IPSelectionWidget::lookUp(const QHostInfo& host)
{
	if (host.error() != QHostInfo::NoError) {

		qDebug() << "Lookup failed:" << host.errorString();
		return;
	}

	//if (host.addresses()[0].toString() == host.hostName())
	//	return;
	qDebug() << host.addresses()[0].toString() << '\n';
	//QTableWidgetItem* ipItem = new QTableWidgetItem;
	//ipItem->setText(host.addresses()[0].toString());
	//QTableWidgetItem* hostItem = new QTableWidgetItem;
	//hostItem->setText(host.hostName());

	//if (ipItem->text() != hostItem->text()) {

	//	ipItem->setTextColor(QColor(Qt::red));
	//	hostItem->setTextColor(QColor(Qt::red));
	//}
	//ui->tableWidget->setItem(useRow, Col1, ipItem);
	//ui->tableWidget->setItem(useRow, Col2, hostItem);
	//useRow++;
}
void IPSelectionWidget::onItemPressed(QListWidgetItem* item)
{
	qDebug() << "onItemPressed" << '\n';
	previousSelectedItems_ = selectedIpItems_;
	selectedIpItems_.clear();
	for (int i = 0; i < ipList_->count(); i++)
	{
		auto item = ipList_->item(i);
		if (item->isSelected())
			selectedIpItems_.emplace(item);
	}

	//for (int i = 1; i < 256; i++) {
	//	QHostInfo::lookupHost(QString("192.9.206.%1").arg(i), this, SLOT(lookUp(QHostInfo)));
	//}
}
void IPSelectionWidget::onItemActivated(QListWidgetItem* item)
{
	qDebug() << "onItemActivated" << '\n';
}
void IPSelectionWidget::onItemChanged(QListWidgetItem* item)
{
	qDebug() << "onItemChanged" << '\n';
}
void IPSelectionWidget::currentItemChanged(QListWidgetItem* item, QListWidgetItem* previous)
{
	qDebug() << "currentItemChanged" << '\n';
}
void IPSelectionWidget::onItemEntered()
{
	qDebug() << "onItemEntered" << '\n';
}
void IPSelectionWidget::itemSelectionChanged()
{
	qDebug() << "itemSelectionChanged" << '\n';
}

void IPSelectionWidget::toggleCheckState(QListWidgetItem* item)
{
	if (item->checkState() == Qt::Unchecked)
		item->setCheckState(Qt::Checked);
	else if (item->checkState() == Qt::Checked)
		item->setCheckState(Qt::Unchecked);
}

void IPSelectionWidget::onIpClicked(QListWidgetItem * currentItem)
{
	qDebug() << "onIpClicked" << '\n';

	auto selectedItems = selectedIpItems_;

	for (auto itr = selectedItems.begin(); itr != selectedItems.end(); itr++)
	{
		auto &selectedItem = *itr;
		if (selectedItem == currentItem)
			continue;		
		if (currentItem->checkState() == Qt::Unchecked)
			selectedItem->setCheckState(Qt::Checked);
		else if (currentItem->checkState() == Qt::Checked)
			selectedItem->setCheckState(Qt::Unchecked);
	}
	toggleCheckState(currentItem);
}