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
// функція яка запускає нашу гру
void MainWindow::startDoodleGame(const std::string& mylevel){
    srand(time(0));
    Music music;
 //загружаємо музику
    if (!music.openFromFile("C:/Users/artur/Downloads/Fluffing-a-Duck(chosic.com).ogg")) {
        QMessageBox::critical(this,"warning","!music");
    }
// створюємо наше вікно
    RenderWindow app(VideoMode(400, 533), "MyDoodleGame");
// максимальний фпс
    app.setFramerateLimit(60);
    Level level;


    TextureManager textureManager;

    BasicMechanics mech;


// створюємо наші текстури
    Sprite sBackground,
        sPlat(textureManager.getTexture(1)),
        sPers,
        sWhitePlat(textureManager.getTexture(3)),
        sBluePlatfrom(textureManager.getTexture(4)),
        sGameOver(textureManager.getTexture(6)),
        sBomb(textureManager.getTexture(7)),
        sYellowPlatform(textureManager.getTexture(8));

// перевірка що ми обрали в параметрах
    if (skinchange == "ninja") sPers.setTexture(textureManager.getTexture(2));
    else if(skinchange == "bunny") sPers.setTexture(textureManager.getTexture(9));
    else sPers.setTexture(textureManager.getTexture(10));
// перевірка що ми обрали в параметрах
    if (backgroundchange == "default") sBackground.setTexture(textureManager.getTexture(0));
    else if(backgroundchange == "ua") sBackground.setTexture(textureManager.getTexture(11));
    else sBackground.setTexture(textureManager.getTexture(12));
// зменшуємо в мастабі нашу бомбу
    sBomb.setScale(15.0f / sBomb.getLocalBounds().width, 15.0f / sBomb.getLocalBounds().height);




// координуємо нашу текстуру геймовер
    sGameOver.setPosition(0, 150);



    Game game;

    traps bomb(sBomb);

    EasyLevel easyLevel;
    MediumLevel mediumLevel;
    HardLevel hardLevel;

    WhitePlatform White_Platform;
    Platform Green_Platform;
    MovingPlatform Blue_Platform;
    ExtremePlatform YellowPlatform;


    Score sc;
    Sprite score[5];

// настроюємо наш score
    for (int i = 0; i < 5; i++) {
        score[i].setTexture(textureManager.getTexture(5));
        score[i].setTextureRect(IntRect(0, 0, 30, 47));
        score[i].setPosition(35 * i, 0);
        sc.SetFS(i,0);
    }

    level.SetLevel(mylevel);

// перевірка на який ми рівень потряпляємо

    if (level.GetLevel() == "e") {
        easyLevel.playLevel(Green_Platform);
    }
    else if (level.GetLevel() == "m") {
        mediumLevel.playLevel(Green_Platform, White_Platform);
    }
    else if (level.GetLevel() == "ha") {
        hardLevel.playLevel(Blue_Platform, White_Platform, Green_Platform, YellowPlatform);
    }

    int Size = Green_Platform.Size();


// запускаємо нашу гру
    RunGame(controller,this,music,textureManager ,hardLevel, mediumLevel, easyLevel, app, game, bomb, level, Green_Platform, White_Platform, Blue_Platform, YellowPlatform, sc, score, sGameOver, sBomb, sBackground, sPlat, sPers, sWhitePlat, sBluePlatfrom, sYellowPlatform, mech, Size, true);

    // присвоюємо наш найкращий результат
    if(thebestscore < sc.GetCurrentScore()) thebestscore = sc.GetCurrentScore();

    // перетворюємо з int -> string

    std::string convert = std::to_string(sc.GetCurrentScore()); // Convert integer to string
    QString qSt = QString::fromStdString(convert);
    ui->label_4->setText(qSt);

    // перетворюємо з int -> string

    convert= std::to_string(thebestscore); // Convert integer to string
    qSt = QString::fromStdString(convert);
     ui->label_5->setText(qSt);
}

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
void MainWindow::on_pushButton_2_clicked()
{
      hide();
      settings window;
      window.setModal(true);
      QRadioButton* radioButtonInSettings = window.getRadioButton();
      QRadioButton* radioButtonInSettings_2 = window.getRadioButton_2();

      QRadioButton* radioButtonInSettings_3 = window.getRadioButton3();
      QRadioButton* radioButtonInSettings_4 = window.getRadioButton4();
      QRadioButton* radioButtonInSettings_5 = window.getRadioButton5();

      QRadioButton* radioButtonInSettings_6 = window.getRadioButton6();
      QRadioButton* radioButtonInSettings_7 = window.getRadioButton7();
      QRadioButton* radioButtonInSettings_8 = window.getRadioButton8();

      if (!controller) radioButtonInSettings->setChecked(true);
      else radioButtonInSettings_2->setChecked(true);


      if (skinchange == "ninja") radioButtonInSettings_3->setChecked(true);
      else if(skinchange == "bunny") radioButtonInSettings_4->setChecked(true);
      else radioButtonInSettings_5->setChecked(true);

      if (backgroundchange == "default") radioButtonInSettings_6->setChecked(true);
      else if(backgroundchange == "ua") radioButtonInSettings_7->setChecked(true);
      else radioButtonInSettings_8->setChecked(true);


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


