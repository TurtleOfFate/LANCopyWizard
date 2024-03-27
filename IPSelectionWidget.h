#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <unordered_set>

class IPAddress;
class QListWidgetItem;
class QHostInfo;
class IPController;
class IPSelectionWidget : public QWidget
{
	Q_OBJECT

public:
	IPSelectionWidget(const QVector<IPAddress> &addresses, QWidget* parent = nullptr);
	void addAddress(const QString& ip);
	void removeAddress(const QString& ip);
private:
	void createConnections();

	void setAddresses(const QVector<IPAddress>& addresses);

	
private:
	QListWidget *ipList_;
	QPushButton *refresh_;
	QPushButton *CopyToSelected;
	QVBoxLayout *parentLayout_;
	void toggleCheckState(QListWidgetItem* item);
	std::unordered_set<QListWidgetItem*> previousSelectedItems_;
	std::unordered_set<QListWidgetItem*> selectedIpItems_;
	IPController* ipController_;
private slots:
	void onRefreshClicked();

	void onIPsRefreshed(const QSet<QString>& ips);

	void onIpAdd(const QString& ip);

	void onIpDelete(const QString& ip);

	void onIpClicked(QListWidgetItem * currentItem);

	void onItemPressed(QListWidgetItem* item);

	void onItemActivated(QListWidgetItem* item);

	void onItemChanged(QListWidgetItem* item);

	void currentItemChanged(QListWidgetItem* item, QListWidgetItem* previous);

	void itemSelectionChanged();
};

