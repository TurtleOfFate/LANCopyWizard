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
private:
    QPair<QString, QString> pairOfPath;
    QString ip;
    QProcess* process_;
    QProcess* process2_;

    void parsePathToValidForm();

private slots:
    void xcopy();
    void onXCopyEnded();

    void onReadFromProcessOutput();

    void onXCopyFailed(QProcess::ProcessError error);

signals:

   void xcopyFailed(QString& output);
   void xcopySucceded( QString& output);
   void finished(QString& output);
};
