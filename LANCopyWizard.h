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

	MainWindow *myqapp = nullptr;
	QHBoxLayout *hlayout = nullptr;
	QLabel *label = nullptr;
	QPushButton *exitButt = nullptr;
	QPushButton *textbut = nullptr;
	QWidget *mainWindow = nullptr;

private:
    Ui::LANCopyWizardClass ui;
};
