#pragma once
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QWidget>

class PingExecutor : public QThread 
{
    Q_OBJECT

public:
    PingExecutor(QWidget* parent = nullptr);
    void OnPing();
private slots:
   // void OnPing();
    void OnPingEnded();
private:
    QProcess process_;
};



//QString baseNetowrk = "192.9.206.";
//#if defined(WIN32)
//QString parameter = "-n";
//#else
//QString parameter = "-c";
//#endif
//for (int i = 0; i < 255; i++) {
//    QString currIp(baseNetowrk + QString::number(i));
//    int exitCode = QProcess::execute("ping", QStringList() << parameter << "1" << currIp);
//    if (exitCode == 0) {
//        qDebug() << "alive:" << baseNetowrk + QString::number(i);
//    }
//    else {
//        qDebug() << "dead";
//    }
//}