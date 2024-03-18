#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LANCopyWizard.h"

class LANCopyWizard : public QMainWindow
{
    Q_OBJECT

public:
    LANCopyWizard(QWidget *parent = nullptr);
    ~LANCopyWizard();

private:
    Ui::LANCopyWizardClass ui;
};
