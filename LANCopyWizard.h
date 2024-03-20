#pragma once

#include <QtWidgets>
#include "ui_LANCopyWizard.h"

class MainWindow;
class LANCopyWizard : public QMainWindow
{
    Q_OBJECT

public:

    LANCopyWizard(QWidget *parent = nullptr);
    ~LANCopyWizard();

	MainWindow *mainWindow_ = nullptr;

private:
    Ui::LANCopyWizardClass ui;
};
