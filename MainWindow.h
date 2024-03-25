#pragma once
#include <qobject.h>
#include <qwidget.h>
#include <QGridLayout>
#include <QSplitter>

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
	
	QVector<QWidget> activeWidgets_;
	QSplitter * mainWindowSplitter_;
	QGridLayout *mainGrid_;
};

