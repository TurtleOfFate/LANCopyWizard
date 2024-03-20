#include "LANCopyWizard.h"
#include <QtWidgets>
#include "MainWindow.h"

LANCopyWizard::LANCopyWizard(QWidget *parent)
    : QMainWindow(parent)
{
	mainWindow_ = new MainWindow(this);
	mainWindow_->show();
}

LANCopyWizard::~LANCopyWizard()
{
}
