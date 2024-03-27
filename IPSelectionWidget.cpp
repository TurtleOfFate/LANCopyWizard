#include "IPSelectionWidget.h"
#include <qlistwidget.h>
#include <qdebug.h>
#include <QSignalMapper>
#include <QHostInfo>
#include <QProcess>
#include <QNetworkInterface>
#include "PingExecutor.h"
#include "IPController.h"
#include <QString>

IPSelectionWidget::IPSelectionWidget(IPController* controller,QWidget* parent) : QWidget(parent)
{
	qDebug() << "MAIN THREAD " << QThread::currentThread()->currentThreadId();
	ipController_ = controller;
	ipList_ = new QListWidget(this);
	refresh_ = new QPushButton("Refresh", this);
	CopyToSelected = new QPushButton("Send", this);

	parentLayout_ = new QVBoxLayout(this);
	parentLayout_->addWidget(ipList_);
	parentLayout_->addWidget(refresh_);
	parentLayout_->addWidget(CopyToSelected);

	ipList_->setSelectionBehavior(QAbstractItemView::SelectItems);
	ipList_->setSelectionMode(QAbstractItemView::ExtendedSelection);
	
	this->setLayout(parentLayout_);	

	createConnections();
	controller->refreshActiveIPsOnLan();
}

void IPSelectionWidget::addAddress(const QString& ip)
{
	QListWidgetItem* item = new QListWidgetItem(ipList_);

	item->setFlags(item->flags() & (~Qt::ItemIsUserCheckable));
	item->setCheckState(Qt::CheckState::Unchecked);
	item->setData(Qt::DisplayRole, QObject::tr(ip.toUtf8()));
}

void IPSelectionWidget::onIPsRefreshed(const QList<QString>& ips)
{
	qDebug() << "THREAD onIPsRefreshed: " << QThread::currentThread()->currentThreadId();
	ipList_->clear();
	foreach(auto ip, ips)
	{
		addAddress(ip);
	}
}


void IPSelectionWidget::removeAddress(const QString& ip)
{
	for (int i = 0; i < ipList_->count(); i++)
	{
		auto item = ipList_->item(i);
		if (item->text() == ip)
			ipList_->removeItemWidget(item);
	}
}

void IPSelectionWidget::createConnections()
{
	QObject::connect(refresh_, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
	
	QObject::connect(ipController_, SIGNAL(activeIpsRefreshed(const QList<QString>&)), this, SLOT(onIPsRefreshed(const QList<QString>&)));
	QObject::connect(ipList_, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onItemPressed(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onItemActivated(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onItemChanged(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem *)), this, SLOT(currentItemChanged(QListWidgetItem*, QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onIpClicked(QListWidgetItem*)));
	QObject::connect(ipList_, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
}


void IPSelectionWidget::onRefreshClicked()
{
	ipController_->refreshActiveIPsOnLan();
}
void IPSelectionWidget::onXCopyEnded()
{
	QByteArray output = proc->readAllStandardOutput();
	qDebug() << output;
}
void IPSelectionWidget::onItemPressed(QListWidgetItem* item)
{
	//qDebug() << "onItemPressed" << '\n';
	previousSelectedItems_ = selectedIpItems_;
	selectedIpItems_.clear();
	for (int i = 0; i < ipList_->count(); i++)
	{
		auto item = ipList_->item(i);
		if (item->isSelected())
			selectedIpItems_.insert(item);
	}
	proc = new QProcess(this);
	QObject::connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onXCopyEnded()));
	auto command = QStringList() << "c:\\hehe.txt" << R"(\\)""192.9.206.59\\c\\Soft" << "/y";
	//proc->start("xcopy", command);//QStringList() << "-n" << "1" << ip_
	//cont->activeIpsRefreshed(active);
	//QString baseNetowrk = "192.9.206.";
	//for (int i = 0; i < 255; i++)
	//{

	//	QString currIp(baseNetowrk + QString::number(i));
	//	PingExecutor* pingExecutor = new PingExecutor(currIp);
	//	QThread* thread = new QThread;
	//	pingExecutor->moveToThread(thread);
	//	connect(thread, SIGNAL(started()), pingExecutor, SLOT(ping()));
	//	connect(pingExecutor, SIGNAL(finished()), thread, SLOT(quit()));
	//	//connect(this, SIGNAL(stopAll()), pingExecutor, SLOT(stop()));
	//	connect(pingExecutor, SIGNAL(finished()), pingExecutor, SLOT(deleteLater()));
	//	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	//	thread->start();
	//}

	//PingExecutor* pingExecutor = new PingExecutor;
	////pingExecutor->ping();

	//QThread* thread = new QThread;
	////pingExecutor->ping(); /* передаем список файлов для обработки */

	//pingExecutor->moveToThread(thread);

	///*  Теперь внимательно следите за руками.  Раз: */
	//connect(thread, SIGNAL(started()), pingExecutor, SLOT(ping()));
	///* … и при запуске потока будет вызван метод process(), который создаст построитель отчетов, который будет работать в новом потоке

	//Два: */
	//connect(pingExecutor, SIGNAL(finished()), thread, SLOT(quit()));
	//thread->start();

//	QString baseNetowrk = "192.9.206.";
//#if defined(WIN32)
//	QString parameter = "-n";
//#else
//	QString parameter = "-c";
//#endif
//	for (int i = 0; i < 255; i++) {
//		QString currIp(baseNetowrk + QString::number(i));
//		int exitCode = QProcess::execute("ping", QStringList() << parameter << "1" << currIp);
//		if (exitCode == 0) {
//			qDebug() << "alive:" << baseNetowrk + QString::number(i);
//		}
//		else {
//			qDebug() << "dead";
//		}
//	}



	//QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
	//for (int i = 0; i < interfaces.count(); i++)
	//{
	//	QList<QNetworkAddressEntry> entries = interfaces.at(i).addressEntries();
	//	for (int j = 0; j < entries.count(); j++)
	//	{
	//		if (entries.at(j).ip().protocol() == QAbstractSocket::IPv4Protocol)
	//		{
	//			QString ip = entries.at(j).ip().toString();
	//			int exitCode = QProcess::execute("ping", QStringList()
	//				<< "-n" << "1"
	//				<< ip);
	//			if (exitCode == 0) {
	//				// it's alive
	//				qDebug() << "alive" << '\n';
	//			}
	//			else {
	//				// it's dead
	//				qDebug() << "dead" << '\n';
	//			}
	//			qDebug() << entries.at(j).ip().toString();
	//			qDebug() << entries.at(j).netmask().toString();
	//		}
	//	}
	//}
}
void IPSelectionWidget::onItemActivated(QListWidgetItem* item)
{
	//qDebug() << "onItemActivated" << '\n';
}
void IPSelectionWidget::onItemChanged(QListWidgetItem* item)
{
	//qDebug() << "onItemChanged" << '\n';
}
void IPSelectionWidget::currentItemChanged(QListWidgetItem* item, QListWidgetItem* previous)
{
	//qDebug() << "currentItemChanged" << '\n';
}

void IPSelectionWidget::itemSelectionChanged()
{
	//qDebug() << "itemSelectionChanged" << '\n';
}

void IPSelectionWidget::toggleCheckState(QListWidgetItem* item)
{
	if (item->checkState() == Qt::Unchecked)
		item->setCheckState(Qt::Checked);
	else if (item->checkState() == Qt::Checked)
		item->setCheckState(Qt::Unchecked);
}



void IPSelectionWidget::onIpAdd(const QString& ip)
{
	addAddress(ip);
}

void IPSelectionWidget::onIpDelete(const QString& ip)
{
	removeAddress(ip);
}

void IPSelectionWidget::onIpClicked(QListWidgetItem * currentItem)
{
	//qDebug() << "onIpClicked" << '\n';

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