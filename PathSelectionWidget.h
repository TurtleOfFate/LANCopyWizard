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
	QListWidget* listOfPaths;
	QPushButton* Submit;
	QPushButton* addParhField;
	QVBoxLayout* parentLayout_;
 	QVector<PathRowWidget*> pathRows_;

	void createConnections();
//	void toggleCheckState(QListWidgetItem* item);


private slots:

	void onSubmitClicked();

	void onAddPathClicked();

	//void onItemPressed(QListWidgetItem* item);

	//void onItemActivated(QListWidgetItem* item);

	//void onItemChanged(QListWidgetItem* item);

	//void currentItemChanged(QListWidgetItem* item, QListWidgetItem* previous);

	//void onItemEntered();

	//void itemSelectionChanged();
};
