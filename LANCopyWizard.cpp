#include "LANCopyWizard.h"
#include <QtWidgets>
#include "MainWindow.h"

LANCopyWizard::LANCopyWizard(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	 myqapp = new MainWindow;
	 hlayout = new QHBoxLayout;
	 label = new QLabel("hello world!");
	 exitButt = new QPushButton("Exit");
	 textbut = new QPushButton("show text");
	 mainWindow = new QWidget;
	QObject::connect(exitButt, &QPushButton::clicked, &QApplication::quit);


	bool bok = true;
	bok = QObject::connect(textbut, &QPushButton::clicked, myqapp, &MainWindow::setupUi);
	Q_ASSERT(bok);
	hlayout->addWidget(label);
	hlayout->addWidget(exitButt);
	hlayout->addWidget(textbut);
	mainWindow->setLayout(hlayout);
	mainWindow->show();


}

LANCopyWizard::~LANCopyWizard()
{
	delete myqapp;
	delete hlayout;
	delete label;
	delete exitButt;
	delete textbut;
	delete mainWindow;
}
