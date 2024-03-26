#pragma once
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QWidget>

class PingExecutor : public QObject 
{
    Q_OBJECT
public:
  
    PingExecutor(const QString& ip,QObject *parent = nullptr);
    ~PingExecutor()
    {
        qDebug() << "DELETED PING EXECUTOR";
    };
public slots:
    void ping();
private slots:
    void onPingEnded();
signals:
    void finished(); 

private:
    QProcess *process_;
    QString ip_;
};
