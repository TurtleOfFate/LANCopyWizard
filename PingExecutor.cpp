#include "PingExecutor.h"
#include <QObject>
#include <QMutex>

void PingExecutor::ping()
{
    QObject::connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onPingEnded()));
#ifndef WIN32
    process_.start("ping", QStringList() << "-c" << "1" << ip_);
#else
    process_->start("ping", QStringList() << "-n" << "1" << ip_);
#endif
    process_->waitForFinished(10000);
    emit finished();
}

PingExecutor::PingExecutor(const QString& ip, QObject* parent) : QObject(parent)
{
    ip_ = ip;
    process_ = new QProcess(this);
}

QMutex messageMutex;
void PingExecutor::onPingEnded()
{
    QMutexLocker locker(&messageMutex);
    QByteArray output = process_->readAllStandardOutput();
    if (!output.isEmpty())
    {  
        if (-1 != QString(output).indexOf("ttl", 0, Qt::CaseInsensitive))
        {
            emit pingSucceded(ip_);
        }
        else
        {
            emit pingFailed(ip_);
        }     
       // qDebug() << "THREAD PingExecutor::onPingEnded: " << QThread::currentThread()->currentThreadId();
    }
}
