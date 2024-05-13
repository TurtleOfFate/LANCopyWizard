#include "LanSender.h"
#include "XcopyExecutor.h"

LanSender::LanSender(QWidget* parent) : QWidget(parent)
{
	
}

void LanSender::PushIpToSend(QString ip_)
{
	ips.insert(ip_);
}

void LanSender::PushFromPathToSend(QString pathFrom, int rowNumber)
{
	pairsOfPaths[rowNumber].first = pathFrom;
}


void LanSender::PushToPathToSend(QString pathTo, int rowNumber)
{
	pairsOfPaths[rowNumber].second = pathTo;
}

void LanSender::onSendDataToXcopy()
{
	foreach (auto paths, pairsOfPaths)
	{
		foreach(auto ip, ips)
		{
			XcopyExecutor* xcopyExecutor = new XcopyExecutor(ip, paths);
			QThread* thread = new QThread;
			xcopyExecutor->moveToThread(thread);
			connect(thread, SIGNAL(started()), xcopyExecutor, SLOT(xcopy()));
			connect(xcopyExecutor, &XcopyExecutor::xcopyFailed, this, &LanSender::ErrorWhileXcopy);
			connect(xcopyExecutor, &XcopyExecutor::xcopySucceded, this, &LanSender::SuccededWhileXcopy);

			connect(xcopyExecutor, SIGNAL(finished(QString&)), SLOT(onXcopyFinished(QString&)));
			connect(xcopyExecutor, SIGNAL(finished(QString&)), thread, SLOT(quit()));

			connect(xcopyExecutor, SIGNAL(finished(QString&)), xcopyExecutor, SLOT(deleteLater()));
			connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

			thread->start();
		}
	}
}

void LanSender::ErrorWhileXcopy()
{
	QMessageBox::warning(this, "error", "Error while xcopy process. Please check path or ip");
}
void LanSender::SuccededWhileXcopy()
{
	QMessageBox::information(this, "Succeded", "everything ok");
}