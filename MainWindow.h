#pragma once
#include <qobject.h>
#include <qwidget.h>
#include <QHBoxLayout>

class MainWindow  : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

signals:
	void sendMessage();

public slots:
	void setupUi();
	void copySlot();

private:
	
	std::vector<QWidget> activeWidgets_;
	QHBoxLayout* mainWindowLayout;
};

