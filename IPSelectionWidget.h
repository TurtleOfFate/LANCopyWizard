#pragma once
#include <qwidget.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>

class IPSelectionWidget : public QWidget
{
	Q_OBJECT

public:
	IPSelectionWidget(QWidget* parent = nullptr);
private:
	QListWidget *ipList_;
	QPushButton *refresh_;
	QPushButton *CopyToSelected;
	QVBoxLayout *parentLayout_;
};

