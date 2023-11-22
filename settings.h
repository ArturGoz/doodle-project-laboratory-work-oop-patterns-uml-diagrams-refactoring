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

    void on_radioButton_clicked();
    void on_radioButton_2_clicked();

private slots:



private:
   // Ui::settings *ui;
  //   QButtonGroup *movementButtonGroup;
  //  QButtonGroup *skinButtonGroup;
  //  QButtonGroup *backgroundButtonGroup;



};

#endif // SETTINGS_H
