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
	QPushButton* Submit;
	QPushButton* addPathField;
	QVBoxLayout* parentLayout_;
 	QVector<PathRowWidget*> pathRows_;

	void createConnections();
	void addPathItemToList(QListWidget* list);

private slots:

	void onSubmitClicked();

	void onAddPathClicked();

};
