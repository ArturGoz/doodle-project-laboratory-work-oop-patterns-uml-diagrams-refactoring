#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool controller = true;
    QString skinchange = "ninja";
    QString backgroundchange = "default";
    int thebestscore = 0;
    ~MainWindow();

public slots:
    void startDoodleGame(const std::string& mylevel);
    void starteasyGame();
    void startmediumGame();
    void starthardGame();
    bool GetController();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
