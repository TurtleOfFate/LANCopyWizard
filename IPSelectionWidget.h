#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <unordered_set>

class IPAddress;
class QListWidgetItem;
class QHostInfo;
class IPSelectionWidget : public QWidget
{
	Q_OBJECT

public:
	IPSelectionWidget(const QVector<IPAddress> &addresses, QWidget* parent = nullptr);
private:
	void createConnections();

private:
	QListWidget *ipList_;
	QPushButton *refresh_;
	QPushButton *CopyToSelected;
	QVBoxLayout *parentLayout_;
	void toggleCheckState(QListWidgetItem* item);
	std::unordered_set<QListWidgetItem*> previousSelectedItems_;
	std::unordered_set<QListWidgetItem*> selectedIpItems_;

private slots:
	void lookUp(const QHostInfo& host);

	void onIpClicked(QListWidgetItem * currentItem);

	void onItemPressed(QListWidgetItem* item);

	void onItemActivated(QListWidgetItem* item);

	void onItemChanged(QListWidgetItem* item);

	void currentItemChanged(QListWidgetItem* item, QListWidgetItem* previous);

	void onItemEntered();

	void itemSelectionChanged();
};

