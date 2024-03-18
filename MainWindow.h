#pragma once
#include <qobject.h>
class MainWindow :public QObject
{
	Q_OBJECT

signals:
	void sendMessage();

public slots:
	void setupUi();
};

