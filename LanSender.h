#pragma once
#include <QObject>
#include <QWaitCondition>
#include <QSet>
#include <QMap>
#include <QPair>
#include <QString>
class LanSender : public QObject
{
	Q_OBJECT
public:
	LanSender(QObject* parent = nullptr);

	void PushIpToSend(QString ip_);
	void PushToPathToSend(QString pathTo, int rowNumber);
	void PushFromPathToSend(QString pathFrom, int rowNumber);
	void onSendDataToXcopy(void);
private:
	QMap<int, QPair<QString, QString>> pairsOfPaths; //first - from second - to
	QSet<QString> ips;
private slots:


};

