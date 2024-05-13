#pragma once
#include <QObject>
#include <QPair>
#include <QString>
#include <QThread>
#include <QProcess>
#include <QDebug>
class XcopyExecutor : public QObject
{
    Q_OBJECT
public:
    XcopyExecutor(QString& ip, QPair<QString, QString>& pathPair, QObject* parent = nullptr);

signals:
    void xcopyFailed();
    void xcopySucceded();
    void finished(QString& output);
private:
    QPair<QString, QString> pairOfPath;
    QString ip;
    QString out;
    QProcess* process_;
    QProcess* process2_;
    QByteArray error;

    void parsePathToValidForm();

private slots:
    void xcopy();
    void onXCopyEnded();

    void onReadFromProcessErrorOutput();

    void onReadFromProcessOutput();

    void onXCopyFailed(QProcess::ProcessError error);

};
