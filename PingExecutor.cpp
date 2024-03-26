#include "PingExecutor.h"
#include <QObject>


PingExecutor::PingExecutor(QWidget* parent)
{

}

void PingExecutor::OnPing()
{
    QString baseNetowrk = "192.9.206.";
    for (int i = 0; i < 255; i++) 
    {
        QString currIp(baseNetowrk + QString::number(i));
        QObject::connect(&process_, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(OnPingEnded()));
#ifndef WIN32
        process_.start("ping", QStringList() << "-c" << "1" << currIp);
#else
        process_.start("ping", QStringList() << "-n" << "1" << currIp);
#endif
        process_.waitForFinished();

    }
}

void PingExecutor::OnPingEnded()
{
    QByteArray output = process_.readAllStandardOutput();
    if (!output.isEmpty())
    {
        qDebug() << output;
        if (-1 != QString(output).indexOf("ttl", 0, Qt::CaseInsensitive))
        {
            qDebug() << "PING OK";
        }
        else
        {
            qDebug() << "PING KO";
        }
    }
}