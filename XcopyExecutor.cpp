#include "XcopyExecutor.h"
#include <QtAlgorithms>

XcopyExecutor::XcopyExecutor(QString& ip, QPair<QString, QString>& pathPair, QObject* parent): QObject(parent)
{
	this->ip = ip;
	this->pairOfPath = pathPair;
	process_ = new QProcess(this);
	process2_ = new QProcess(this);
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

	//connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onXCopyEnded()));
	//connect(process_, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(onXCopyFailed(QProcess::ProcessError)));

	connect(process2_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onXCopyEnded()));
	connect(process2_, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(onXCopyFailed(QProcess::ProcessError)));

	connect(process2_, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadFromProcessOutput()));

	//R"(\\)""192.9.206.59\\c\\Soft"
	QString pathTo = R"(\\)" + ip + "\\" + pairOfPath.second;
	if (isFile)
	{
		arguments = QStringList() << pairOfPath.first << pathTo << "/y";
		program = "xcopy";
		process2_->start(program, arguments);
		//process2_->write("F\n"); // write our answer to the process
	}
	else
	{

		arguments = QStringList() << pairOfPath.first << pathTo << "/y" << "/i";// /s /e";// ;
		program = "xcopy";
		process2_->start(program, arguments);	
		process2_->write("D\n"); // write our answer to the process
	}

	//arguments = QStringList() << "f:\\HOHO.txt" << R"(\\)""192.9.206.151\\c\\Soft" << "/y";
	//process_->
	//process2_->start(program, arguments);//QStringList() << "-n" << "1" << ip_
	//QString output = process2_->readAllStandardOutput().simplified();
	//qDebug().noquote() << "output: " << output;
	//if (output.contains(")?", Qt::CaseInsensitive))
	//{
	//	process2_->write("D\n"); // write our answer to the process
	//}
	//process2_->write("doskey / history\n");
	//output = process2_->readAllStandardOutput().simplified();
	//qDebug().noquote() << "output after doskey: " << output;
	//process2_->setProcessChannelMode(QProcess::ForwardedChannels);
	//QByteArray output = process2_->readAllStandardOutput();

	//QString output = compilator->readAllStandardOutput().simplified();
	//qDebug().noquote() << "output: " << output;

	//if (output.contains("(Y/N)?", Qt::CaseInsensitive))
	//{
	//	compilator->write("Y\n"); // write our answer to the process
	//}

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

void XcopyExecutor::onReadFromProcessOutput()
{
	//static int countOfReadEnter = 0;
	//QString output = process2_->readAllStandardOutput().simplified();
	//if (countOfReadEnter == 0)
	//{
	//	qDebug().noquote() << "output: " << output << endl;
	//	if (output.contains(")?", Qt::CaseInsensitive))
	//	{
	//		process2_->write("D\n"); // write our answer to the process
	//		process2_->write("doskey / history\n");
	//	}
	//	else
	//	{
	//		process2_->write("doskey / history\n");
	//	}
	//	countOfReadEnter++;
	//}
	//else 
	//{
	//	qDebug().noquote() << "output after doskey: " << output.toUtf8();
	//}
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
