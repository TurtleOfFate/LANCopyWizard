#include "IPController.h"
#include "PingExecutor.h"
#include <QMutex>

IPController::IPController(QObject* parent) : QObject(parent)
{

}

static QMutex activeIpsMutex;
void IPController::onIpActive(const QString& ip)
{
	QMutexLocker locker(&activeIpsMutex);
	//qDebug() << ip;
	activeIps_.insert(ip);
}

static QMutex unavailableIpsMutex;
void IPController::onIpUnavailable(const QString& ip)
{
	QMutexLocker locker(&unavailableIpsMutex);
	//qDebug() << "IpUnavailable" << ip;
}

void IPController::refreshActiveIPsOnLan(const QString& baseIP)
{
	if (isIpsRefreshing_)
		return;
	isIpsRefreshing_ = true;
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
		//connect(pingExecutor, SIGNAL(pingFailed(const QString&)), this, SLOT(onIpUnavailable(const QString&)));
		thread->start();	
	}	
}

void IPController::onPingFinished()
{
	executedPingsCounter_.fetch_add(1);
	if (executedPingsCounter_.load() == hostsCount_)
	{
		//qDebug() << "THREAD onPingFinished: " << QThread::currentThread()->currentThreadId();
		QList<QString> values;
		if (!activeIps_.empty())
		{
			values = activeIps_.values();
			auto hostsComparator = [](const QString& lhs, const QString& rhs)
				{
					QStringList lhsIp = lhs.split(".");
					QStringList rhsIp = rhs.split(".");
					int lhsIpHostAddress = lhsIp[3].toInt();
					int rhsIpHostAddress = rhsIp[3].toInt();
					if (lhsIpHostAddress < rhsIpHostAddress)
						return true;
					return false;
				};
			qSort(values.begin(), values.end(), hostsComparator);
		}
		else
		{
			values.push_back("Cant ping at least one of ip adress in selected network.");
			values.push_back("Please check that the input is correct, or lan network connection");
		}

		emit activeIpsRefreshed(values);
		activeIps_.clear();
		executedPingsCounter_.store(0);
		isIpsRefreshing_ = false;
	}
}
