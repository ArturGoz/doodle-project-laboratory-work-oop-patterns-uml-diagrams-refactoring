#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QRadioButton>
#include <QButtonGroup>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:

    explicit settings(QWidget *parent = nullptr);
    Ui::settings* ui;
    QRadioButton* getRadioButton() const;
    QRadioButton* getRadioButton_2() const;
    QRadioButton* getRadioButton3() const;
    QRadioButton* getRadioButton4() const;
    QRadioButton* getRadioButton5() const;
    QRadioButton* getRadioButton6() const;
    QRadioButton* getRadioButton7() const;
    QRadioButton* getRadioButton8() const;
    ~settings();


public slots:


private slots:



private:
   // Ui::settings *ui;




};

#endif // SETTINGS_H
