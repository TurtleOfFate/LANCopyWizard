#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <unordered_set>

class IPAddress;
class QListWidgetItem;

class IPSelectionWidget : public QWidget
{
	Q_OBJECT

public:
	IPSelectionWidget(const QVector<IPAddress> &addresses, QWidget* parent = nullptr);
	void createConnections();

private:
	QListWidget *ipList_;
	QPushButton *refresh_;
	QPushButton *CopyToSelected;
	QVBoxLayout *parentLayout_;

	std::unordered_set<QListWidgetItem*> selectedIpItems_;
private slots:
	void highlightChecked();
	void checkAllSelected(QListWidgetItem* item);
	void ipClicked(QListWidgetItem* item);
};

