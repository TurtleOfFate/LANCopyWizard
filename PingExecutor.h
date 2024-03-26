#pragma once
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QWidget>

class PingExecutor : public QObject 
{
    Q_OBJECT
public:
    PingExecutor(const QString& ip);

    PingExecutor::~PingExecutor()
    {
        if (process_ != nullptr) {
            delete process_;
        }
    }

public slots:
    void ping();
    void ping(const QString& ip);
private slots:
    void onPingEnded();
signals:
    void finished(); 

private:
    QProcess *process_;
    QString ip_;
};
