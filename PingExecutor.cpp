#include "PingExecutor.h"
#include <QObject>

void PingExecutor::ping()
{
    process_ = new QProcess;
    QString baseNetowrk = "192.9.206.";
    //for (int i = 0; i < 255; i++) 
    {
       // QString currIp(baseNetowrk + QString::number(i));
        QObject::connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onPingEnded()));
#ifndef WIN32
        process_.start("ping", QStringList() << "-c" << "1" << ip_);
#else
        process_->start("ping", QStringList() << "-n" << "1" << ip_);
#endif
        process_->waitForFinished();

    }
    emit finished();
}

PingExecutor::PingExecutor(const QString& ip)
{
    ip_ = ip;
}

void PingExecutor::ping(const QString& ip)
{
    process_ = new QProcess;
    QObject::connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onPingEnded()));
#ifndef WIN32
    process_.start("ping", QStringList() << "-c" << "1" << ip);
#else
    process_->start("ping", QStringList() << "-n" << "1" << ip);
#endif
    process_->waitForFinished();
    emit finished();
}

void PingExecutor::onPingEnded()
{
    QByteArray output = process_->readAllStandardOutput();
    if (!output.isEmpty())
    {
       // qDebug() << output;
        if (-1 != QString(output).indexOf("ttl", 0, Qt::CaseInsensitive))
        {
            qDebug() << "PING OK" << ip_;
        }
        else
        {
            //qDebug() << "PING KO";
        }
    }
}

