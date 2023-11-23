#include "settings.h"
#include "mainwindow.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    // створюю QButtonGroup щоб мати 1 властивість з 3 або 2 і тд
    QButtonGroup *skinButtonGroup = new QButtonGroup(this);
    skinButtonGroup->addButton(ui->radioButton_3);
    skinButtonGroup->addButton(ui->radioButton_4);
    skinButtonGroup->addButton(ui->radioButton_5);

// створюю QButtonGroup щоб мати 1 властивість з 3 або 2 і тд
    QButtonGroup *movementButtonGroup = new QButtonGroup(this);
    movementButtonGroup->addButton(ui->radioButton);
    movementButtonGroup->addButton(ui->radioButton_2);
// створюю QButtonGroup щоб мати 1 властивість з 3 або 2 і тд
    QButtonGroup *backgroundButtonGroup = new QButtonGroup(this);
    backgroundButtonGroup->addButton(ui->radioButton_6);
    backgroundButtonGroup->addButton(ui->radioButton_7);
    backgroundButtonGroup->addButton(ui->radioButton_8);



}

settings::~settings()
{
    delete ui;
}


QRadioButton* settings::getRadioButton() const {
    return ui->radioButton;
}
QRadioButton* settings::getRadioButton_2() const {
    return ui->radioButton_2;
}
QRadioButton* settings::getRadioButton3() const {
    return ui->radioButton_3;
}
QRadioButton* settings::getRadioButton4() const {
    return ui->radioButton_4;
}
QRadioButton* settings::getRadioButton5() const {
    return ui->radioButton_5;
}
QRadioButton* settings::getRadioButton6() const {
    return ui->radioButton_6;
}
QRadioButton* settings::getRadioButton7() const {
    return ui->radioButton_7;
}
QRadioButton* settings::getRadioButton8() const {
    return ui->radioButton_8;
}







