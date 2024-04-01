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
	pairOfPath.first.replace(QChar('/'), QChar('\\'), Qt::CaseInsensitive);
	pairOfPath.second.replace(QChar('/'), QChar('\\'), Qt::CaseInsensitive);
	pairOfPath.second.remove(QChar(':'), Qt::CaseInsensitive);
	//pairOfPath.second.replace()
	auto firstDiskToLower = pairOfPath.first.front().toLower();
	auto secondDiskToLower = pairOfPath.second.front().toLower();
	pairOfPath.first[0] = firstDiskToLower;
	pairOfPath.second[0] = secondDiskToLower;
}

void XcopyExecutor::xcopy()
{
	bool isFile = false;
	QStringList arguments;
	QString program;
	QString::iterator it;


	if (pairOfPath.second.end() != qFind(pairOfPath.second.begin(), pairOfPath.second.end(), "."))
	{
		isFile = true;
	}

	connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onXCopyEnded()));
	connect(process_, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(onXCopyFailed(QProcess::ProcessError)));
	//R"(\\)""192.9.206.59\\c\\Soft"
	QString pathTo = R"(\\)" + ip + "\\" + pairOfPath.second;
	if (isFile)
	{
		arguments = QStringList() << pairOfPath.first << pathTo << "/y";
		program = "xcopy";
	}
	else
	{
		arguments = QStringList() << pairOfPath.first << pathTo << "/y" << "/i";// /s /e";// ;
		program = "xcopy";
	}
	//arguments = QStringList() << "f:\\HOHO.txt" << R"(\\)""192.9.206.151\\c\\Soft" << "/y";
	//process_->
	process_->start(program, arguments);//QStringList() << "-n" << "1" << ip_
	QByteArray output = process_->readAllStandardOutput();
}

void XcopyExecutor::onXCopyEnded()
{
	QByteArray output = process_->readAllStandardOutput();
	auto out = QString(output);
	if (!output.isEmpty())
	{
		qDebug() << out;
		emit xcopySucceded(out);
	}
	emit finished(out);
}

void XcopyExecutor::onXCopyFailed(QProcess::ProcessError error)
{
	qDebug() << "error enum val = " << error << endl;
	QByteArray output = process_->readAllStandardError();
	auto out = QString(output);
	if (!output.isEmpty())
	{
		qDebug() << out;
		emit xcopyFailed(out);
	}
	emit finished(out);
}
