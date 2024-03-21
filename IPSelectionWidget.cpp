#include "IPSelectionWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"
#include <qdebug.h>

IPSelectionWidget::IPSelectionWidget(const QVector<IPAddress> &addresses,QWidget* parent) : QWidget(parent)
{
	parentLayout_ = new QVBoxLayout(this);
	ipList_ = new QListWidget(this);
	refresh_ = new QPushButton(this);
	CopyToSelected = new QPushButton(this);

	parentLayout_->addWidget(ipList_);
	parentLayout_->addWidget(refresh_);
	parentLayout_->addWidget(CopyToSelected);

	ipList_->setSelectionBehavior(QAbstractItemView::SelectItems);
	ipList_->setSelectionMode(QAbstractItemView::ExtendedSelection);
	
	for (int i = 0; i < addresses.size(); i++)
	{
		const IPAddress &address = addresses[i];
		QListWidgetItem* item = new QListWidgetItem(ipList_);

		//item->setFlags(item->flags() & (~Qt::ItemIsUserCheckable));
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

	QObject::connect(ipList_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(ipClicked(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemSelectionChanged()), this, SLOT(highlightChecked()));
	QObject::connect(ipList_, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
}

void IPSelectionWidget::onItemPressed(QListWidgetItem* item)
{
	qDebug() << "onItemPressed" << '\n';
	for (int i = 0; i < ipList_->count(); i++)
	{
		auto item = ipList_->item(i);
		if (item->isSelected())
		{
			selectedIpItems_.emplace(item);
		}
		else
		{
			selectedIpItems_.erase(item);
		}
	}
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
void IPSelectionWidget::highlightChecked() {
	//if (it->checkState() == Qt::Checked)
	//ipList_->blockSignals(true);
	//for (int i = 0; i < ipList_->count(); i++)
	//{
	//	auto item = ipList_->item(i);
	//	if (item->isSelected())
	//	{
	//	//	item->setBackgroundColor(QColor("#ffffb2"));
	//		//qDebug() << "item sel" << '\n';
	//		previousSelectedItems_.emplace(item);
	//	}
	//	else
	//	{
	//		//item->setBackgroundColor(QColor("#dddddd"));
	//		//selectedIpItems_.erase(item);

	//	}
	//		//ipList_->it(i)->setCheckState(Qt::Unchecked);

	//}
	//	it->setBackgroundColor(QColor("#ffffb2"));
	//else
	//	it->setBackgroundColor(QColor("#ffffff"));
}

void IPSelectionWidget::checkAllSelected(QListWidgetItem* item) {
	if (item->checkState() == Qt::Checked)
		item->setBackgroundColor(QColor("#ffffb2"));
	else
		item->setBackgroundColor(QColor("#ffffff"));
}

void IPSelectionWidget::ipClicked(QListWidgetItem* item)
{

	qDebug() << "ipClicked" << '\n';
	//ipList_->blockSignals(true);//
	//const QSignalBlocker blocker(ipList_);
	//if (it->data(Qt::CheckStateRole) != Qt::Checked)
	//	it->setData(Qt::CheckStateRole, Qt::Checked);
	//else
	//	it->setData(Qt::CheckStateRole, Qt::Unchecked);
	//Qt::CheckState itemState = item->checkState();//data(Qt::CheckStateRole);
	//if (itemState == Qt::Unchecked)
	//	item->setData(Qt::CheckStateRole, Qt::Checked);
	//else
	//	item->setData(Qt::CheckStateRole, Qt::Unchecked);

	auto selectedItems = selectedIpItems_;//ipList_->selectedItems();
	for (auto itr = selectedItems.begin(); itr != selectedItems.end(); itr++)
	{
		auto &selectedItem = *itr;
		if (selectedItem->data(Qt::CheckStateRole) == Qt::Unchecked)
		{
			selectedItem->setData(Qt::CheckStateRole, Qt::Checked);
		}
		else if (selectedItem->data(Qt::CheckStateRole) == Qt::Checked)
		{
			selectedItem->setData(Qt::CheckStateRole, Qt::Unchecked);
		}
	}

	//for (int i = 0; i < ipList_->count(); i++)
	//{
	//	auto it = ipList_->item(i);
	//	if (it->isSelected() )//&& it->data(Qt::CheckStateRole) != Qt::Unchecked
	//	{
	//		//it->setData(Qt::CheckStateRole, Qt::Checked);
	//		//it->setBackgroundColor(QColor("#ffffb2"));
	//	}
	//	else if(it->isSelected() && it->data(Qt::CheckStateRole) == Qt::Checked)
	//	{
	//		//it->setData(Qt::CheckStateRole, Qt::Checked);
	//		//it->setBackgroundColor(QColor("#fdffb2"));
	//	}
	//	//ipList_->it(i)->setCheckState(Qt::Unchecked);

	//}
	//if (it == nullptr)
	//	return;
	
}