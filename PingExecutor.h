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
        //qDebug() << "DELETED PING EXECUTOR";
    };
public slots:
    void ping();
private slots:
    void onPingEnded();
signals:
    void finished(); 
    void pingSucceded(const QString& ip);
    void pingFailed(const QString& ip);
private:
    QProcess *process_;
    QString ip_;
};
