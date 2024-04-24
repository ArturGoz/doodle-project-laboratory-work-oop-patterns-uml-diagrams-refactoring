#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "doodle.h"
#include  "settings.h"
#include  "tutorial.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // конекчу свої функції з кнопками
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(starteasyGame()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(startmediumGame()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(starthardGame()));


}
MainWindow::~MainWindow()
{
    delete ui;
}

//std::mutex mt;

// функція яка запускає нашу гру
void MainWindow::startDoodleGame(const std::string& mylevel){

// створюємо наше вікно
    RenderWindow app(VideoMode(Width_of_screen, Height_of_screen), "MyDoodleGame");


    // максимальний фпс
    // використовується патерн Game Loop
    // обмеження FPS є ключовою частиною патерну “Game Loop”.
    // становлення максимального FPS допомагає контролювати швидкість, з якою оновлюється стан гри.
    //Це важливо, оскільки дозволяє гарантувати, що гра працює з постійною швидкістю незалежно від швидкості обробки комп’ютера.
    app.setFramerateLimit(60);

    CreateGame game(skinchange,backgroundchange,mylevel,app,this);
   // game.testResetGame();
   // game.testResetGameClass();
   // game.testDoAll(); // повинен відразу видаватися наш рахунок
  //  game.testRunGame(controller);
// запускаємо нашу гру
    game.RunGame(controller);


    // присвоюємо наш найкращий результат
   if(thebestscore < game.getCurrentScore()) thebestscore = game.getCurrentScore();

    // перетворюємо з int -> string

    std::string convert = std::to_string(game.getCurrentScore()); // Convert integer to string
    QString qSt = QString::fromStdString(convert);
    ui->label_4->setText(qSt);

    // перетворюємо з int -> string

    convert= std::to_string(thebestscore); // Convert integer to string
    qSt = QString::fromStdString(convert);
     ui->label_5->setText(qSt);
}


// передаємо рівень гри за e -> easy, m -> medium, ha -> hard
void MainWindow::starteasyGame(){
      hide();
      startDoodleGame("e");
      show();
}
void MainWindow::startmediumGame(){
      hide();
      startDoodleGame("m");
      show();
}
void MainWindow::starthardGame(){
      hide();
      startDoodleGame("ha");
      show();
}

// функція яка співпрацює з налаштуванням і присвоює нам дані які ми вибрали
// натискаємо на кнопку Параметрів
void MainWindow::on_pushButton_2_clicked()
{
      hide();
      settings window;
      window.setModal(true);

//mt.lock();
          QRadioButton* radioButtonInSettings = window.getRadioButton();
          QRadioButton* radioButtonInSettings_2 = window.getRadioButton_2();

          QRadioButton* radioButtonInSettings_3 = window.getRadioButton3();
          QRadioButton* radioButtonInSettings_4 = window.getRadioButton4();
          QRadioButton* radioButtonInSettings_5 = window.getRadioButton5();

          QRadioButton* radioButtonInSettings_6 = window.getRadioButton6();
          QRadioButton* radioButtonInSettings_7 = window.getRadioButton7();
          QRadioButton* radioButtonInSettings_8 = window.getRadioButton8();
//mt.unlock();
      \
// загальні перевірки що ми обрали в параметрах і змінюває наші параметри
 //auto start = std::chrono::high_resolution_clock::now();
   //   std::thread t1([&](){
      if (!controller) radioButtonInSettings->setChecked(true);
      else radioButtonInSettings_2->setChecked(true);


      if (skinchange == "ninja") radioButtonInSettings_3->setChecked(true);
      else if(skinchange == "bunny") radioButtonInSettings_4->setChecked(true);
      else radioButtonInSettings_5->setChecked(true);
 //});
      if (backgroundchange == "default") radioButtonInSettings_6->setChecked(true);
      else if(backgroundchange == "ua") radioButtonInSettings_7->setChecked(true);
      else radioButtonInSettings_8->setChecked(true);


      //    t1.join();
     // auto finish = std::chrono::high_resolution_clock::now(); // End timing here

    //  std::chrono::duration<double> elapsed = finish - start;
    //  std::cout << "Elapsed time: " << elapsed.count() << " s\n";

      window.exec();

      if(radioButtonInSettings->isChecked())  controller = false;
      else  controller = true;

      if(radioButtonInSettings_3->isChecked()) skinchange = "ninja";
      else if (radioButtonInSettings_4->isChecked()) skinchange = "bunny";
      else skinchange = "contur";

      if(radioButtonInSettings_6->isChecked()) backgroundchange = "default";
      else if (radioButtonInSettings_7->isChecked()) backgroundchange = "ua";
      else backgroundchange = "fire";


      show();
}

// натискаємо на кнопку tutorial
void MainWindow::on_pushButton_6_clicked()
{
      hide();
      tutorial window;
      window.setModal(true);
      window.exec();
      show();
}

bool  MainWindow::GetController()
{
      return controller;
}


