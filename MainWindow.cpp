#include "MainWindow.h"
#include <QtWidgets>

void MainWindow::setupUi()
{
	QWidget* myWindow = new QWidget;
	QHBoxLayout* hlayout = new QHBoxLayout;
	QLabel* some_text_from_button = new QLabel("some text from button!");
	hlayout->addWidget(some_text_from_button);
	myWindow->setLayout(hlayout);
	myWindow->show();
}
