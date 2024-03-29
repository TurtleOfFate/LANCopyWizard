#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>


class IPAddress;
class QListWidgetItem;
class PathRowWidget;
class LanSender;

class PathSelectionWidget : public QWidget
{
	Q_OBJECT

public:
	PathSelectionWidget(LanSender* sender, QWidget* parent = nullptr);
private:
	QListWidget* pathList_;
	QPushButton* deletePath_;
	QPushButton* addPath_;
	QVBoxLayout* parentLayout_;
 	QVector<PathRowWidget*> pathRows_;

	LanSender* sender;

	void createConnections();
	void deleteSelectedFromList(QListWidget* list);
	void addToList(QListWidget* list);

private slots:

	void onAddPathClicked();

	void onDeletePathClicked();

};
