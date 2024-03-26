#include "IPController.h"
#include "PingExecutor.h"

IPController::IPController(QObject* parent) : QObject(parent)
{

}

void IPController::refreshActiveIPsOnLan()
{
	QString baseNetowrk = "192.9.206.";
	for (int i = 0; i < 255; i++)
	{

		QString currIp(baseNetowrk + QString::number(i));
		PingExecutor* pingExecutor = new PingExecutor(currIp);
		QThread* thread = new QThread;
		pingExecutor->moveToThread(thread);
		connect(thread, SIGNAL(started()), pingExecutor, SLOT(ping()));
		connect(pingExecutor, SIGNAL(finished()), thread, SLOT(quit()));
		//connect(this, SIGNAL(stopAll()), pingExecutor, SLOT(stop()));
		connect(pingExecutor, SIGNAL(finished()), pingExecutor, SLOT(deleteLater()));
		connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
		thread->start();
		
	}
	activeIpsRefreshed({ baseNetowrk });
}
