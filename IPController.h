#pragma once

#include <QString>
#include <QObject>
#include <QSet>
#include <QWaitCondition>

class IPController : public QObject 
{
	Q_OBJECT
public:
	IPController(QObject* parent = nullptr);
	void refreshActiveIPsOnLan();

	QSet<QString> getActiveIPs() const
	{ 
		return activeIPs_; 
	};

public slots:
	void onIpActive(const QString& ip);
	void onIpUnavailable(const QString& ip);
	void onPingFinished();
signals:
	void activeIpsRefreshed(QSet<QString> activeIPs);
	
private:
	QSet<QString> activeIPs_;
	bool isIpsRefreshing_ = false;
	int refreshedIpsCount = 0;
	std::atomic<int> executedPingsCounter_ = 0;
	const int hostsCount_ = 255;
};

