#include "LANCopyWizard.h"
#include <QtWidgets>
#include "MainWindow.h"

LANCopyWizard::LANCopyWizard(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	MainWindow myqapp;
	QHBoxLayout* hlayout = new QHBoxLayout;
	QLabel* label = new QLabel("hello world!");
	QPushButton* exitButt = new QPushButton("Exit");
	QPushButton* textbut = new QPushButton("show text");
	QWidget* mainWindow = new QWidget;
	QObject::connect(exitButt, &QPushButton::clicked, &QApplication::quit);


	bool bok = true;
	bok = QObject::connect(textbut, SIGNAL(clicked()), &myqapp, SLOT(setupUi()));
	Q_ASSERT(bok);
	hlayout->addWidget(label);
	hlayout->addWidget(exitButt);
	hlayout->addWidget(textbut);
	mainWindow->setLayout(hlayout);
	mainWindow->show();
}

LANCopyWizard::~LANCopyWizard()
{}
