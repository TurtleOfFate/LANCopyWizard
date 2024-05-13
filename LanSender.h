#pragma once
#include <QObject>
#include <QWaitCondition>
#include <QSet>
#include <QMap>
#include <QPair>
#include <QString>
#include <QWidget>
#include <QMessageBox>
class LanSender : public QWidget
{
	Q_OBJECT
public:
	LanSender(QWidget* parent = nullptr);

	void PushIpToSend(QString ip_);
	void PushToPathToSend(QString pathTo, int rowNumber);
	void PushFromPathToSend(QString pathFrom, int rowNumber);
	void onSendDataToXcopy(void);
private:
	QMap<int, QPair<QString, QString>> pairsOfPaths; //first - from second - to
	QSet<QString> ips;
	QWidget* errorWidget;
	QTextLine* errorText;
private slots:

	void ErrorWhileXcopy();
	void SuccededWhileXcopy();
};

