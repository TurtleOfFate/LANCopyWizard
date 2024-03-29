#include "XcopyExecutor.h"
#include <QtAlgorithms>

XcopyExecutor::XcopyExecutor(QString& ip, QPair<QString, QString>& pathPair, QObject* parent): QObject(parent)
{
	this->ip = ip;
	this->pairOfPath = pathPair;
	process_ = new QProcess(this);
	parsePathToValidForm();
}

void XcopyExecutor::parsePathToValidForm()
{

}

void XcopyExecutor::xcopy()
{
bool isFile = false;
QStringList arguments;
QString program;
QString::iterator it;

pairOfPath.first.replace('/', '\\');
pairOfPath.second.replace('/', '\\');
pairOfPath.second.replace(':', '\\');
//while ((it = qFind(pairOfPath.first.begin(), pairOfPath.first.end(), "/")) != pairOfPath.first.end())
//	{
//		*it = '\\';
//	}
//while ((it = qFind(pairOfPath.second.begin(), pairOfPath.first.end(), "/")) != pairOfPath.second.end())
//	{
//	*it = '\\';
//	}
//if ((it = qFind(pairOfPath.second.begin(), pairOfPath.first.end(), "/")) != pairOfPath.second.end())
//	{
//	*it = ':';
//	}

	if (pairOfPath.first.end() != qFind(pairOfPath.first.begin(), pairOfPath.first.end(), "."))
	{
		isFile = true;
	}
connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onXCopyEnded()));
	if (isFile)
	{
		arguments = QStringList() << pairOfPath.first << " " << R"(\\)" << ip << "\\" << pairOfPath.second << "/y";
		program = "xcopy";
	}
	else
	{
		arguments = QStringList() << pairOfPath.first << " " << R"(\\)" << ip << "\\" << pairOfPath.second << "/y /s /e";
		program = "call echo d | xcopy";
	}
process_->start(program, arguments);//QStringList() << "-n" << "1" << ip_
}

void XcopyExecutor::onXCopyEnded()
{
	QByteArray output = process_->readAllStandardOutput();
	auto out = QString(output);
	if (!output.isEmpty())
	{
		if (-1 != out.indexOf("ttl", 0, Qt::CaseInsensitive))
		{
			emit xcopySucceded(out);
		}
		else
		{
			emit xcopyFailed(out);
		}
	}
	emit finished(out);
}