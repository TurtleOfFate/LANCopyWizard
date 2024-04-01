#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProcess>

class LanSender;
class QListWidgetItem;
class QHostInfo;
class IPController;
class IPSelectionWidget : public QWidget
{
	Q_OBJECT

public:
	IPSelectionWidget(LanSender* sender, IPController* controller, QWidget* parent = nullptr);
	void addAddress(const QString& ip);
	void removeAddress(const QString& ip);
private:
	void createConnections();
private:
	QListWidget *ipList_;
	QPushButton *refresh_;
	QPushButton *CopyToSelected;
	QVBoxLayout *parentLayout_;

	QHBoxLayout *baseIpLayout_;
	QLineEdit *firstBaseIp;
	QLineEdit *secondBaseIp;
	QLineEdit *thirdBaseIp;
	QString baseIp = "..";

	void toggleCheckState(QListWidgetItem* item);
	QSet<QListWidgetItem*> previousSelectedItems_;
	QSet<QListWidgetItem*> selectedIpItems_;
	IPController* ipController_;
	QProcess* proc;
	LanSender* sender;
private slots:

	void onPushBaseIp(const QString& ip, int number);

	void onRefreshClicked();

	void onIPsRefreshed(const QList<QString>& ips);

	void onIpAdd(const QString& ip);

	void onIpDelete(const QString& ip);

	void onIpClicked(QListWidgetItem * currentItem);

	void onSendClicked();

	void onXCopyEnded();

	void onItemPressed(QListWidgetItem* item);

	void onItemActivated(QListWidgetItem* item);

	void onItemChanged(QListWidgetItem* item);

	void currentItemChanged(QListWidgetItem* item, QListWidgetItem* previous);

	void itemSelectionChanged();
signals:
	void ipForSend(const QString& ip);
};

