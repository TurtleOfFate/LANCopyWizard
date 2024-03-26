#pragma once
#include <QVector>
#include <QString>
#include <QObject>

class IPController : public QObject 
{
	Q_OBJECT
public:
	IPController(QObject* parent = nullptr);
	void refreshActiveIPsOnLan();
	QVector<QString> getActiveIPsList() const
	{ 
		return activeIPs_; 
	};
private:
	QVector<QString> activeIPs_;
signals:
	void activeIpsRefreshed(QVector<QString> activeIPs);

};

