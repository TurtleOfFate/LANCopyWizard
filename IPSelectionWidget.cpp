#include "IPSelectionWidget.h"
#include <qlistwidget.h>
#include "IPAddress.h"

IPSelectionWidget::IPSelectionWidget(QWidget* parent) : QWidget(parent)
{
	parentLayout_ = new QVBoxLayout(this);
	ipList_ = new QListWidget(this);
	refresh_ = new QPushButton(this);
	CopyToSelected = new QPushButton(this);

	parentLayout_->addWidget(ipList_);
	parentLayout_->addWidget(refresh_);
	parentLayout_->addWidget(CopyToSelected);
	//QAbstractItemModel* model = new QStandardItemModel();
	//model->setHeaderData(0, Qt::Horizontal, "IP");
	//IPAddressModel* model = new IPAddressModel(ipList_);
	for (int i = 0; i < 100; i++)
	{
		QListWidgetItem* item = new QListWidgetItem(ipList_);
		item->setCheckState(Qt::CheckState::Unchecked);
		item->setData(Qt::ItemDataRole::ToolTipRole, QObject::tr("I'm TOOLTIP %1").arg(i));
		item->setData(Qt::DisplayRole, QObject::tr("Item %1").arg(i));
	}
	this->setLayout(parentLayout_);
	
}
