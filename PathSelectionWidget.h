#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>


class IPAddress;
class QListWidgetItem;
class PathRowWidget;

class PathSelectionWidget : public QWidget
{
	Q_OBJECT

public:
	PathSelectionWidget(QWidget* parent = nullptr);
private:
	QListWidget* pathList_;
	QPushButton* deletePath_;
	QPushButton* addPath_;
	QVBoxLayout* parentLayout_;
 	QVector<PathRowWidget*> pathRows_;

	void createConnections();
	void deleteSelectedFromList(QListWidget* list);
	void addToList(QListWidget* list);

private slots:

	void onAddPathClicked();

	void onDeletePathClicked();

};
