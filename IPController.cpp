#include "IPController.h"
#include "PingExecutor.h"
#include <QMutex>

IPController::IPController(QObject* parent) : QObject(parent)
{

}

QMutex activeIpsMutex;
void IPController::onIpActive(const QString& ip)
{
	QMutexLocker locker(&activeIpsMutex);
	qDebug() << ip;
	activeIPs_.insert(ip);
}

QMutex unavailableIpsMutex;
void IPController::onIpUnavailable(const QString& ip)
{
	QMutexLocker locker(&unavailableIpsMutex);
	qDebug() << "IpUnavailable" << ip;
}

void IPController::refreshActiveIPsOnLan()
{
	QString baseNetowrk = "192.9.206.";
	for (int i = 0; i < hostsCount_; i++)
	{
		QString currIp(baseNetowrk + QString::number(i));
		PingExecutor* pingExecutor = new PingExecutor(currIp);
		QThread* thread = new QThread;
		pingExecutor->moveToThread(thread);
		connect(thread, SIGNAL(started()), pingExecutor, SLOT(ping()));
		connect(pingExecutor, SIGNAL(finished()), this, SLOT(onPingFinished()));
		connect(pingExecutor, SIGNAL(finished()), thread, SLOT(quit()));
		//connect(this, SIGNAL(stopAll()), pingExecutor, SLOT(stop()));
		connect(pingExecutor, SIGNAL(finished()), pingExecutor, SLOT(deleteLater()));
		connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
		connect(pingExecutor, SIGNAL(pingSucceded(const QString&)), this, SLOT(onIpActive(const QString&)));
		connect(pingExecutor, SIGNAL(pingSucceded(const QString&)), this, SLOT(onIpUnavailable(const QString&)));
		thread->start();	
	}
	
}

void IPController::onPingFinished()
{
	executedPingsCounter_.fetch_add(1);
	if (executedPingsCounter_.load() == hostsCount_)
	{
		emit activeIpsRefreshed(activeIPs_);
		executedPingsCounter_.store(0);
	}
}
