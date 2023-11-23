# doodle-project-and-laba-1-laba-2-laba3
doodle project and  laba 1 laba 2 laba3
ДОКУМЕНТАЦІЯ
За допомогою цього коду підлючати у фреймфорк qt бібліотеку sfml 

 

LIBS += -L"..\SFML-2.6.0\lib" 

LIBS += -L"..\SFML-2.6.0\bin" 

  

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window 

CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window 

  

INCLUDEPATH += "..\SFML-2.6.0\include" 

  

DEPENDPATH += "..\SFML-2.6.0\include" 

 

Doodle.h: 

 

#include <SFML/Graphics.hpp>  -> для використання графіки sfml 

#include <SFML/Audio.hpp>  -> для використання музики 

#include <iostream>  -> загальна  бібліотека 

#include <vector> -> контейнер для 1 лаби 

#include <string> -> для зручності в проведенні тестів та написання тексту 

#include "QMessageBox" -> для виведення помилок у коді, або виведення даних(у мене виведення рахунку) 

#include <QString>  ->  для зручності в проведенні тестів та написання тексту(унікальна бібліотека qtcreator де є більше функцій) 

 

class Game -> використання координат типу x y dx dy для того щоб взаємодіяти з об’єктами. Успадковую її 

 

class BasicMechanics -> механіка для мого Дудла який падає, пригає і тд. 

class Platform -> загальний клас для платформ, де міститься усі взаємодії з платформами. Успадковую її 

class WhitePlatform : virtual public Platform -> біла платформа з унікальними властивостями 

class MovingPlatform : virtual public Platform -> голуба платформа з унікальними властивостями 

class ExtremePlatform :  public WhitePlatform, public MovingPlatform -> жовта  з властивостями минулих платформ. Трійне успадкування 

class TextureManager ->  клас для  загрузки текстур та взаємодії з ними. 

class Level -> клас для взаємодії з рівнями 

class EasyLevel -> клас де обираються платформи для легкого рівня 

class MediumLevel -> клас де обираються платформи для середнього рівня 

class HardLevel -> клас де обираються платформи для складного рівня 

class Score -> клас для взаємодією з рахунком 

class traps : public Game -> клас для взаємодії з пастками 

void ResetGame -> функція для рестарту гри 

void RunGame -> функція яка викликає нашу гру 

 

Mainwindow.h 

 

#include <QMainWindow> -> для роботи з MainWindow 

#include <QRadioButton> -> для роботи з RadioButton 

 

class MainWindow -> загальний клас де міститься всі більшість даних та функцій 

 

    void startDoodleGame(); -> функція для старту гри 

    void starteasyGame(); -> функція для старту легкої гри 

    void startmediumGame(); -> функція для старту средньої гри 

    void starthardGame(); -> функція для старту складної гри 

 

Добавив змінні для загальної роботи з параметрами й підраховуванням найращого рахунку: 

    bool controller = true; 

    QString skinchange = "ninja"; 

    QString backgroundchange = "default"; 

    int thebestscore = 0; 

 

Settings.h 

 

#include <QDialog> для роботи з вікном  Dialog 

#include <QRadioButton> для роботи з RadioButton 

#include <QButtonGroup> для роботи з ButtonGroup 

 

class settings -> загальний клас для роботи з параметрами 

Геттери для роботи з параметрами  

    QRadioButton* getRadioButton() const; 

    QRadioButton* getRadioButton_2() const; 

    QRadioButton* getRadioButton3() const; 

    QRadioButton* getRadioButton4() const; 

    QRadioButton* getRadioButton5() const; 

    QRadioButton* getRadioButton6() const; 

    QRadioButton* getRadioButton7() const; 

    QRadioButton* getRadioButton8() const; 

 

Tutorial.h 

class tutorial клас для роботи з туторіалом (нічого цікавого) 
