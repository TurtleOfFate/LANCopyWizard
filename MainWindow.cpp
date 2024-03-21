#include "MainWindow.h"
#include <QtWidgets>
#include "IPSelectionWidget.h"
#include "IPAddress.h"

MainWindow::MainWindow(QWidget* parent)
{
	QVector<IPAddress> addresses;
	addresses.append(IPAddress("192.9.200.6"));
	addresses.append(IPAddress("192.9.200.7"));
	addresses.append(IPAddress());
	IPSelectionWidget* widget = new IPSelectionWidget(addresses,this);
	widget->show();
}
MainWindow::~MainWindow()
{

}


void MainWindow::setupUi()
{
	//QWidget* myWindow = new QWidget;
	//QVBoxLayout* vlayout = new QVBoxLayout(myWindow);
	//QHBoxLayout* hlayout = new QHBoxLayout;
	//QLabel* some_text_from_button = new QLabel("what do yo wanna do with your life?");
	//hlayout->setSpacing(20);
	//vlayout->setSpacing(20);
	//hlayout->addWidget(some_text_from_button);

	//QPushButton* exitButt = new QPushButton("cancel");
	//exitButt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//QPushButton* textbut = new QPushButton("Copy from many to one");
	//textbut->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	//QPushButton* textbut1 = new QPushButton("Copy from one to many");
	//QPushButton* textbut2 = new QPushButton("Copy with preselected configuration");
	//QPushButton* textbut3 = new QPushButton("Show current configuration");

	//QObject::connect(exitButt, &QPushButton::clicked, this, &QApplication::quit);
	//QObject::connect(textbut, &QPushButton::clicked, this, &MainWindow::copySlot);
	//QObject::connect(textbut1, &QPushButton::clicked, this, &MainWindow::copySlot);
	//QObject::connect(textbut2, &QPushButton::clicked, this, &MainWindow::copySlot);
	//QObject::connect(textbut3, &QPushButton::clicked, this,&MainWindow::copySlot);



	//hlayout->addWidget(exitButt);
	//vlayout->addWidget(textbut);
	//vlayout->addWidget(textbut1);
	//vlayout->addWidget(textbut2);
	//vlayout->addWidget(textbut3);
	//vlayout->addLayout(hlayout);

	//myWindow->show();
}

void MainWindow::copySlot()
{
}