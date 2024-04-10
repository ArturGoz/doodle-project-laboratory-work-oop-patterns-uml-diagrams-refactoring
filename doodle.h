#ifndef DOODLE_H
#define DOODLE_H

#endif // DOODLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include "QMessageBox"
#include <QString>
#define Width_of_screen 400
#define Height_of_screen 533

using namespace sf;

class CreateGame;


class coordinates
{
public:
    int x, y, h;
    float dx, dy;
};

//Doodle_mech є класом в якому містяться координати нашого персонажа Doodle
//Відповідно в цьому класі містяться функції які оновлюють координати персонажа щодо гри актора
class Doodle_mech : public coordinates
{

public:
    Doodle_mech() {
        // doodle start
        x = 100;
        y = 100;
        h = 200;
        dx = 0;
        dy = 0;

    }
// падіння вниз яке приближує поразку гравця
    void TurnDown(float& dy, int& y)
    {
        dy += 0.2;
        y += dy;
    }
//При перенесенні персонажа за рамки вікна воно телепортує персонажа у протилежну горизонтальну сторону
    void Teleport(int& x)
    {
        if (x > Width_of_screen)
            x = -40;
        if (x < -40)
            x = Width_of_screen;
    }
//Перевірка падіння граця, якщо гравець перетнув нижнє вікно гри то це призведе до поразки
    void Fall(bool& gameover, int y, int score, float& dy)
    {
        if (y > Height_of_screen-13)
        {
            if (score != 0)
            {
                gameover = false;


            }
            else
                dy = -10;
        }
    }

};

// клас є абстракним та є використовую патерн “Шаблонний метод”
//клас Abstract_platform визначає базовий алгоритм у своїх методах createPlatform, movePlatforms та TouchToPlatform.
//Ці методи визначені як віртуальні, що дозволяє підкласам, таким як Platform, WhitePlatform, Blue_Platform та YellowPlatform, перевизначати їх.
//Кожен з цих підкласів може мати свою власну реалізацію цих методів та вони слідувають тому ж загальному алгоритму, що визначений в Abstract_platform.
//Це є характерною особливістю патерну “Шаблонний метод”.

// цей патерн у коді  визначає частину алгоритму в базовому класі, що дозволяє уникнути дублювання коду в підкласах.
//Якщо потрібно змінити частину алгоритму, вам потрібно змінити лише відповідний підклас, а не весь алгоритм.

//патерн “Шаблонний метод” дозволяє вам визначити загальний алгоритм створення, руху та взаємодії з платформами в базовому класі Abstract_platform, а конкретні деталі реалізації цих методів визначаються в підкласах.
//Це робить ваш код більш гнучким і легким для розширення.

class Abstract_platform
{
public:
    // видалення платформ з вектора
    void clearPlatforms() {
        plat.clear();
    }
    // відображення текстури платформи та постановки її позиції
    // у функції drawPlatforms використаний патерн Flyweight
    // Патерн Flyweight використовується для мінімізації використання пам’яті шляхом спільного використання якомога більше даних з подібними об’єктами
    //В моєму випадку, я використовую один спрайт (який містить текстуру, для кожного типів платформ) для відображення багатьох платформ.
    //Текстура спрайта є спільною для всіх платформ, тому вона завантажується в пам’ять тільки один раз, що є ефективним використанням ресурсів.
    // Я використовую лише 1 текстуру для відображення усіх моїх 1 типу платформ.
    // Тобто якщо у мене є 5 зелених платформ то у мене є 1 Sprite з зеленою тектурою яка буде відображувати всі 5 платформ, а не кожна платформа буде використовувати власну текстуру.
    // у моєму випадку це є ефективним бо у моєї гри не використовується багато платформ і тому компьютер може непомітно та швидко відобразити усі ці платформи 1 текстурою.
    void drawPlatforms(RenderWindow& app, Sprite& sPlat) {
        for (size_t i = 0; i < plat.size(); ++i) {
            sPlat.setPosition(plat[i]);
            app.draw(sPlat);
        }
    }

    float getPlatformX(int index) {
        return plat[index].x;
    }

    float getPlatformY(int index) {
        return plat[index].y;
    }

    void setPlatformX(int index, float x) {
        plat[index].x = x;
    }

    void setPlatformY(int index, float y) {
        plat[index].y = y;
    }
    int Size()
    {
        return plat.size();
    }

    virtual void createPlatform(int count) = 0;
    virtual void movePlatforms(float dy, int& y, int& h, Sprite score[], int fs[], int& sc) = 0;
    virtual void TouchToPlatform(int x, int y, float& dy, int index) = 0;

protected:
    std::vector<Vector2f> plat;

};

// клас Platform від якого буде відтворюватися множинне наслідування.
//Platform і є зеленою платформою у грі
class Platform : public Abstract_platform{
public:
    // відтворення координат для платформи
    virtual  void createPlatform(int count) override{
        for (int i = 0; i < count; ++i) {
            Vector2f p;
            p.x = rand() % 400;
            p.y = rand() % 533;
            plat.push_back(p);
        }
    }
    // функціє оновлює мої платформ, якщо платформа є за межами нашого екрану, вона відтворює нову платформу зверху екрана
    void movePlatforms(float dy, int& y, int& h, Sprite score[], int fs[], int& sc) override {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = h;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > Height_of_screen) {
                plat[i].y = 0;
                plat[i].x = rand() % Width_of_screen;
                ++sc;
                    // structure score numbers
                fs[4]++;
                if (fs[4] > 9) {
                    fs[4] -= 10;

                    fs[3]++;
                    if (fs[3] > 9) {
                        fs[3] -= 10;

                        fs[2]++;
                        if (fs[2] > 9) {
                            fs[2] -= 10;

                            fs[1]++;
                            if (fs[1] > 9) {
                                fs[1] -= 10;

                                fs[0]++;
                                if (fs[0] > 9)
                                    fs[0] -= 10;
                                score[0].setTextureRect(IntRect(30 * fs[0], 0, 30, 47));
                            }
                            score[1].setTextureRect(IntRect(30 * fs[1], 0, 30, 47));
                        }
                        score[2].setTextureRect(IntRect(30 * fs[2], 0, 30, 47));
                    }
                    score[3].setTextureRect(IntRect(30 * fs[3], 0, 30, 47));
                }
                score[4].setTextureRect(IntRect(30 * fs[4], 0, 30, 47));
            }
        }
    }
    // Стрибок по платформам від якої наж персонаж рухається вверх
    virtual  void TouchToPlatform(int x, int y, float& dy, int index) override
    {
        // width and height of platform // jump on them
        if ((x + 50 > getPlatformX(index)) && (x + 20 < getPlatformX(index) + 68) && (y + 70 > getPlatformY(index)) && (y + 70 < getPlatformY(index) + 14) && (dy > 0))
        {
            dy = -10;
        }
    }

};
//WhitePlatform і є білою платформую у грі
class WhitePlatform : virtual public Platform {
public:

    void settakenWhitePlatforms(int index, bool boolean) {
        takenWhitePlatforms[index] = boolean;
    }
    bool gettakenWhitePlatforms(int index) {
        return takenWhitePlatforms[index];
    }



    // функціє оновлює мої платформ, якщо платформа є за межами нашого екрану, вона відтворює нову платформу зверху екрана
    // також функція генерує наш буліан який слідкує чи персонаж вже стрибав на ній, якщо так то платформа не стане функцінувати.
    void movePlatforms(float dy, int& y,Sprite score[], int fs[], int& sc)  {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = 200;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > Height_of_screen) {
                if (gettakenWhitePlatforms(i))
                    settakenWhitePlatforms(i, false);
                sc++;
                plat[i].y = 0;
                plat[i].x = rand() % Width_of_screen;

                fs[4]++;
                if (fs[4] > 9) {
                    fs[4] -= 10;

                    fs[3]++;
                    if (fs[3] > 9) {
                        fs[3] -= 10;

                        fs[2]++;
                        if (fs[2] > 9) {
                            fs[2] -= 10;

                            fs[1]++;
                            if (fs[1] > 9) {
                                fs[1] -= 10;

                                fs[0]++;
                                if (fs[0] > 9)
                                    fs[0] -= 10;
                                score[0].setTextureRect(IntRect(30 * fs[0], 0, 30, 47));
                            }
                            score[1].setTextureRect(IntRect(30 * fs[1], 0, 30, 47));
                        }
                        score[2].setTextureRect(IntRect(30 * fs[2], 0, 30, 47));
                    }
                    score[3].setTextureRect(IntRect(30 * fs[3], 0, 30, 47));
                }
                score[4].setTextureRect(IntRect(30 * fs[4], 0, 30, 47));
            }
        }
    }

   // Стрибок по платформам від якої наж персонаж рухається вверх
    void TouchToPlatform(int x, int y, float& dy, int index) override
    {
        if ((x + 50 > getPlatformX(index)) && (x + 20 < getPlatformX(index) + 68) && (y + 70 > getPlatformY(index)) && (y + 70 < getPlatformY(index) + 14) && (dy > 0) && !gettakenWhitePlatforms(index))
        {

            dy = -10;

            settakenWhitePlatforms(index, true);
        }
    }


protected:
    bool takenWhitePlatforms[5] = { false, false, false, false, false };
};
// клас який генерує усі наші текстури
class TextureManager {
public:
    TextureManager() {
        LoadTextures();
    }

    Texture& getTexture(int index) {
        return textures[index];
    }

private:
    Texture textures[13];
    //функція загружає усі наші платформи
    void LoadTextures() {
        if (!textures[0].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/background.png"))
            std::cerr << "Failed to load background.png" << std::endl;

        if (!textures[1].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/platform.png"))
            std::cerr << "Failed to load platform.png" << std::endl;

        if (!textures[2].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/doodle.png"))
            std::cerr << "Failed to load doodle.png" << std::endl;

        if (!textures[3].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/WhitePlatform.png"))
            std::cerr << "Failed to load WhitePlatform.png" << std::endl;

        if (!textures[4].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/BluePlatfrom.png"))
            std::cerr << "Failed to load BluePlatfrom.png" << std::endl;

        if (!textures[5].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/score.png"))
            std::cerr << "Failed to load score.png" << std::endl;

        if (!textures[6].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/gameover.png"))
            std::cerr << "Failed to load gameover.png" << std::endl;
        if (!textures[7].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/boom.png"))
            std::cerr << "Failed to load boom.png" << std::endl;
        if (!textures[8].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/yellow.png"))
            std::cerr << "Failed to load yellow.png" << std::endl;

        if (!textures[9].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/doodlik-removebg-preview.png"))
            std::cerr << "Failed to load doodlik.png" << std::endl;

        if (!textures[10].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/contur-removebg-preview.png"))
            std::cerr << "Failed to load contur.png" << std::endl;

        if (!textures[11].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/uaa.jpg"))
            std::cerr << "Failed to load uaa.png" << std::endl;

        if (!textures[12].loadFromFile("C:/Users/artur/OneDrive/qttt/pzdc/imgg/fire.jpg"))
            std::cerr << "Failed to load fire.png" << std::endl;
    }
};


class MovingPlatform : virtual public Platform {
public:
   // відтворення координат для платформи
    // також відтворує руж наших платформ
    void createPlatform(int count) override {
        for (int i = 0; i < count; ++i) {
            Vector2f p;
            p.x = rand() % Width_of_screen;
            p.y = rand() % Height_of_screen;
            int move;
            move = rand() % 2 == 0 ? -1 : 1;
            direction.push_back(move);
            plat.push_back(p);
        }
    }
// оновлення наших платформ, якщо платформа доторкується до кордонів то вона змінює свій рух на протилежний
    void update() {
        for (size_t i = 0; i < plat.size(); ++i) {
            plat[i].x += direction[i] * 5;
            if (plat[i].x > 366)
                direction[i] = -1; // Если платформа достигла правой границы, изменяем направление на лево
            if (plat[i].x < 0)
                direction[i] = 1; // Если платформа достигла левой границы, изменяем направление на право
        }
    }
protected:
    std::vector<int> direction;
};

// платформа яка є змішується властивостями WhitePlatform та MovingPlatform
// також у цьому класі використовується патерн "Композиція"
// Композиція - це патерн проектування, який використовується для створення складних об’єктів з простіших.
//Ваш код використовує композицію через використання класів платформ.
    //Наприклад, клас ExtremePlatform складається з WhitePlatform та MovingPlatform.
//Це означає, що ExtremePlatform може використовувати функціональність обох цих класів, що робить його більш складним.

class ExtremePlatform :  public WhitePlatform, public MovingPlatform
{
public:


    void drawplatforms(RenderWindow& app, Sprite& sPlat) {
        WhitePlatform::drawPlatforms(app, sPlat);
    }

    void createplatform(int count)  {
        MovingPlatform::createPlatform(count);
    }

    void moveplatforms(float dy, int& y,Sprite score[], int fs[], int& sc) {
        WhitePlatform::movePlatforms(dy,y,score,fs,sc);
    }



private:

};

//клас для роботи з рівнями гри
class All_levels
{
public:
    std::string GetLevel()
    {
        return level;
    }
    // при отриманні даних функція відтворює наші платформи
    void SetLevel(std::string levelofgame,MovingPlatform& Blue_Platform, WhitePlatform& White_Platform, Platform& Green_Platform, ExtremePlatform& Yellow_Platfrom)
    {
        level = levelofgame;

        if (level == "e") {
            Green_Platform.createPlatform(10);
        }
        else if (level == "m") {
            Green_Platform.createPlatform(5);
            White_Platform.createPlatform(5);
        }
        else if (level == "ha") {
            Green_Platform.createPlatform(2);
            White_Platform.createPlatform(2);
            Blue_Platform.createPlatform(2);
            Yellow_Platfrom.createplatform(2);
        }
    }
    // фунція яка відтворює при рестарті гри, вона оновлює всі платформи
    void Clear_current_level(MovingPlatform& Blue_Platform, WhitePlatform& White_Platform, Platform& Green_Platform, ExtremePlatform& Yellow_Platfrom)
    {
        if (level == "e") {
            Green_Platform.createPlatform(10);
        }
        else if (level == "m") {
            Green_Platform.createPlatform(5);
            White_Platform.createPlatform(5);

            for (int i =0; i< 5;++i)
                White_Platform.settakenWhitePlatforms(i, false);
        }
        else if (level == "ha") {
            Green_Platform.createPlatform(2);
            White_Platform.createPlatform(2);
            Blue_Platform.createPlatform(2);
            Yellow_Platfrom.createplatform(2);

            for (int i =0; i< 2;++i)
            {
                White_Platform.settakenWhitePlatforms(i, false);
                Yellow_Platfrom.settakenWhitePlatforms(i, false);
            }
        }
    }

private:
    std::string level;
};

// клас для роботи з рахунком
class Score
{
public:
    Score()
    {
        current_score = 0;
    }
    void SetFS(int index, int number)
    {
        fs[index] = number;
    }
    int* GetFS()
    {
        return fs;
    }

    int& GetCurrentScore()
    {
        return current_score;
    }

private:
    int fs[5];
    int current_score;
};
// клас для пасток
class traps : public coordinates
{
public:
    void constructor(Sprite& sBomb)
    {
        i = 1;
        x = 200;
        y = -1;
        dy = 2.5;
        sBomb.setPosition(-100, -100);
    }
    // відтворення бомби
    void createBomb(int number,Sprite& sBomb)
    {
        if (number > 50 * i)
        {

            ++i;
            dx = rand() % 400;
            sBomb.setPosition(dx, 0);// Изменение объекта Sprite через ссылку
            y = 0;

        }
    }
   // падіння вниз бомби
    void down(Sprite& sBomb)
    {
        if (y >= 0)
        {
            y += dy;
            sBomb.setPosition(dx, y);
        }
        if (y > 533)
        {
            sBomb.setPosition(-100, -100);
            y = -1;
        }

    }
    //функція яка перевіряє чи наш персонаж пересікся з боибою, якщо так то гра стає поразкою
    void BOOM(bool& gameover,Sprite sPers,Sprite& sBomb )
    {
        FloatRect bombBounds = sBomb.getGlobalBounds();
        FloatRect doodleBounds = sPers.getGlobalBounds();

        if (bombBounds.intersects(doodleBounds)) {

            std::cout << "boOOOOm" << std::endl;
            gameover = false;
        }
    }
    void SetI(int num)
    {
        i = num;
    }
private:
    int i;
};

// створюю абстракний клас для використання патерну "Command", який має метод execute()

//Клас Command імплементують класи CloseApp,Music_ON_OFF,GamePauseResetGameClass.
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

//клас InputHandler контролює ввід користовача, в моєму випадку це кнопки
// Цей клас використовує патерн “Command” для обробки вводу користувача.
//Він має чотири приватні поля типу Command* (buttonF1_, buttonF2_, buttonESC_, buttonTAB_), кожне з яких відповідає за конкретну команду.
// Коли користувач натискає відповідну клавішу, викликається метод execute() відповідного об’єкта команди.

//Таким чином, патерн “Command” дозволяє  відокремити код, який ініціює операції, від коду, який фактично їх виконує.
//Це робить мій код більш гнучким і легким для розширення.

//InputHandler асоціює клас Command.

\
class InputHandler
{
public:
    InputHandler(bool& buttonPressed,bool& buttonPressed2,bool& buttonPressed3, bool& buttonPressed4):
        isF1Pressed(buttonPressed),isTabPressed(buttonPressed2),gamePaused(buttonPressed3),isF2Pressed(buttonPressed4)  {}

   // функція яка перевіряє чи була натиснена кнопка і потом викликає execute
    void handleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) buttonF1_->execute();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) buttonF2_->execute();
        else if (Keyboard::isKeyPressed(Keyboard::Escape)) buttonESC_->execute();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) buttonTAB_->execute();


        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            isF1Pressed = false;
        }

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        {

            // Якщо клавіша "Tab" була відпущена
            if (isTabPressed) {
                // Інвертуємо стан гри (пауза/продовження)
                gamePaused = !gamePaused;
            }
            isTabPressed = false;

        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
            isF2Pressed = false;

    }

    // Методи bind…: Ці методи використовуються для прив’язки конкретних команд до відповідних кнопок.
    //  Коли ці методи викликаються, вони призначають вказівник на об’єкт команди відповідному полю класу InputHandler.
    void bindMusic(Command* command) { buttonF1_ = command; }
    void bindReset(Command* command) { buttonF2_ = command; }
    void bindClose(Command* command) { buttonESC_ = command; }
    void bindPause(Command* command) { buttonTAB_ = command; }

private:
    Command* buttonF1_;
    Command* buttonF2_;
    Command* buttonESC_;
    Command* buttonTAB_;
    bool& isF1Pressed;
    bool& isTabPressed;
    bool& gamePaused;
    bool& isF2Pressed;
};

// клас який має функцію, яку можна викликати за допомогою клавіши, цей клас буде використовуватися в класі InputHandler для використання патерну Command

class CloseApp : public Command
{
public:
    CloseApp(RenderWindow& app) : appMain(app) {}
    virtual void execute() { appMain.close(); }

private:
    RenderWindow& appMain;
};


// клас який має функцію, яку можна викликати за допомогою клавіши, цей клас буде використовуватися в класі InputHandler для використання патерну Command
class Music_ON_OFF : public Command
{
public:

    Music_ON_OFF(bool& m, bool& f, Music& mm): isMusicPlaying(m),isF1Pressed(f),music(mm) {}
    virtual void execute()
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !isF1Pressed) {
            isF1Pressed = true;

            // Інвертуємо стан відтворення музики
            if (isMusicPlaying) {
                music.stop();
            }
            else {
                music.play();
            }

            isMusicPlaying = !isMusicPlaying;
        }


    }
private:
    bool& isMusicPlaying;
    bool& isF1Pressed;
    Music& music;
};

// клас який має функцію, яку можна викликати за допомогою клавіши, цей клас буде використовуватися в класі InputHandler для використання патерну Command
class GamePause : public Command
{
public:
    GamePause(bool& t, bool& p): isTabPressed(t), gamePaused(p){}
    virtual void execute()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            isTabPressed = true;
        }

        else {
            // Якщо клавіша "Tab" була відпущена
            if (isTabPressed) {
                // Інвертуємо стан гри (пауза/продовження)
                gamePaused = !gamePaused;
            }
            isTabPressed = false;
        }
    }
private:
    bool& isTabPressed;
    bool& gamePaused;
};




// абстракний клас GameObserver
// Використовую патерн Observer у цьому класі

//Патерн “Observer” - це поведінковий патерн проектування, який створює механізм підписки,
// дозволяючи об’єктам слідкувати за подіями, що відбуваються в інших об’єктах.
// Спостерігач (Observer): Об’єкт, який слідкує за змінами в іншому об’єкті.
// Суб’єкт (Subject): Об’єкт, за змінами в якому слідкує спостерігач.
// у класі CreateGame я використовую std::vector<GameObserver*> observers; що буде об'єктом який буде слідкувати за замінами
//  також у класі CreateGame я використовую  void addObserver(GameObserver* observer) та void Do_All(bool gameover) {}
// за допомогою addObserver(GameObserver* observer) я передаю субєкт до observer і якщо буде якась зміна у моєму випадку зміна це Закінчення гри
// я буду використовувати функції Do_All() яка буде послідовно йти по вектору у якому будуть субьекти та виконувати  функції  суб’єктів
// єдиний мінус цього що я ще не розробив достатньо коду для цього патерну і використовую 1  суб’єкт це клас ScoreDisplay
// хоча можна було б додати більше функцій після закінчення гри, а я викликаю тільки показ рахунку після поразки

//Переваги патерну “Observer” включають:
//додавати нових спостерігачів без зміни коду суб’єкта.
//Суб’єкт не знає про конкретних спостерігачів, лише про інтерфейс спостерігача. Спостерігачі та суб’єкт можуть оновлюватися незалежно один від одного.
//Зміни в суб’єкті можуть бути автоматично трансльовані до всіх спостерігачів.

//Клас GameObserver імплементують класи ScoreDisplay.
class GameObserver {
public:
    virtual ~GameObserver() {}
    virtual void OnGameOverChanged(bool gameover) = 0;
};





// клас ScoreDisplay буде суб’єктом для нашого патерну Observer
class ScoreDisplay : public GameObserver {
public:
    ScoreDisplay(Score& sc1, QWidget* parent1): sc(sc1),parent(parent1) {}
    void OnGameOverChanged(bool gameover) override {
        if (!gameover) {
            std::string asd = std::to_string(sc.GetCurrentScore()); // Convert integer to string
            QString qString = QString::fromStdString(asd);
            QMessageBox::about(parent,"  Your score  ", qString);
        }
    }
private:
    Score& sc;
    QWidget* parent;
};

// MoveStrategy абстракний клас яикй буде використоуватися для патерну "Стратегія"
// Клас CreateGame буде містити cилку на MoveStrategy у вигляді std::unique_ptr<MoveStrategy> strategy;
//У функції RunGame класу CreateGame має такий код:
// if (Keyboard::isKeyPressed(Keyboard::Right)) strategy = std::make_unique<MoveRight>();
//else if (Keyboard::isKeyPressed(Keyboard::Left)) strategy = std::make_unique<MoveLeft>();
// Я використав функції підкласів MoveLeft та MoveRight які наслідують MoveStrategy.
//використання патерну “Стратегія” дозволяє вам легко змінювати напрямок руху героя гри, залежно від того, яку клавішу натиснув користувач.
//Крім того, це робить код більш чистим та організованим,оскільки логіка кожного напрямку руху ізольована в своєму власному класі.

//Клас MoveStrategy імплементують класи MoveLeft, MoveRight
class MoveStrategy
{
public:
    virtual void move(Doodle_mech& doodlick) = 0;
};

// клас який був взаємодіяти з патерном “Стратегія”
class MoveLeft : public MoveStrategy
{
public:
        // рух персонажа вліво
    void move(Doodle_mech& doodlick) override
    {
        doodlick.x -= 4;
    }
};

// клас який був взаємодіяти з патерном “Стратегія”
class MoveRight : public MoveStrategy
{
public:
    // рух персонажа вправо
    void move(Doodle_mech& doodlick) override
    {
        doodlick.x += 4;
    }
};


// мій основний клас який буде виклакати нашу гру
//CreateGame агрегує клас InputHandler
//CreateGame агрегує класс GameObserver
//CreateGame агрегує класс MoveStrategy
class CreateGame
{
public:
    CreateGame(QString& skinchange, QString& backgroundchange, std::string mylevel,RenderWindow& app1,QWidget* parent1):
        inputHandler(isF1Pressed,isTabPressed,gamePaused,isF2Pressed),app(app1),
        closeApp(app),music_ON_OFF(isMusicPlaying,isF1Pressed,music),
        gamePause(isTabPressed,gamePaused),
        parent(parent1),
        scoreDisplay(sc,parent)
    {
        srand(time(0));

        if (!music.openFromFile("C:/Users/artur/Downloads/Fluffing-a-Duck(chosic.com).ogg")) {
              QMessageBox::critical(parent1,"warning","!music");
        }
        music.play();
        music.setLoop(true);

        sPlat = Sprite(textureManager.getTexture(1));
        sWhitePlat = Sprite(textureManager.getTexture(3));
        sBluePlatfrom = Sprite(textureManager.getTexture(4));
        sGameOver = Sprite(textureManager.getTexture(6));
        sBomb = Sprite(textureManager.getTexture(7));
        sYellowPlatform = Sprite(textureManager.getTexture(8));
        bomb.constructor(sBomb);
        // перевірка що ми обрали в параметрах
        if (skinchange == "ninja") sPers.setTexture(textureManager.getTexture(2));
        else if(skinchange == "bunny") sPers.setTexture(textureManager.getTexture(9));
        else sPers.setTexture(textureManager.getTexture(10));
        // перевірка що ми обрали в параметрах
        if (backgroundchange == "default") sBackground.setTexture(textureManager.getTexture(0));
        else if(backgroundchange == "ua") sBackground.setTexture(textureManager.getTexture(11));
        else sBackground.setTexture(textureManager.getTexture(12));
        // створення нашого рахунку. вставлення текстур в масиви класу Score
        for (int i = 0; i < 5; i++) {
            score[i].setTexture(textureManager.getTexture(5));
            score[i].setTextureRect(IntRect(0, 0, 30, 47));
            score[i].setPosition(35 * i, 0);
            sc.SetFS(i,0);
        }

        // зміни розмірів бомби
        sBomb.setScale(15.0f / sBomb.getLocalBounds().width, 15.0f / sBomb.getLocalBounds().height);
        sGameOver.setPosition(0, 150);
        levelset.SetLevel(mylevel,Blue_Platform, White_Platform, Green_Platform, YellowPlatform);
        Size = Green_Platform.Size();
        gameover = true;
        isTabPressed = false;
        gamePaused = false;

        isF1Pressed = false;
        isMusicPlaying =true;

        isF2Pressed = false;

        ifgameover = true;

        inputHandler.bindPause(&gamePause);
        inputHandler.bindMusic(&music_ON_OFF);
        inputHandler.bindClose(&closeApp);


        addObserver(&scoreDisplay);

    }

    // основна функція яка запускає нашу гру
    void RunGame (bool& controller) {
        ResetGameClass resetGameClass(*this,isF2Pressed);
        inputHandler.bindReset(&resetGameClass);


        while (app.isOpen()) {
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed)
                    app.close();
            }

            app.clear();

            inputHandler.handleInput();


            if (!gamePaused)
            {
                if (gameover)
                {

                    if (controller)
                    {
                        if (Keyboard::isKeyPressed(Keyboard::Right))
                        {
                            strategy = std::make_unique<MoveRight>();
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Left))
                        {
                            strategy = std::make_unique<MoveLeft>();
                        }
                    }
                    else
                    {
                        if (Keyboard::isKeyPressed(Keyboard::D))
                        {
                            strategy = std::make_unique<MoveRight>();
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::A))
                        {
                            strategy = std::make_unique<MoveLeft>();
                        }
                    }

                    if (strategy)
                    {
                       strategy->move(doodlick);
                    }

                    Blue_Platform.update();
                    YellowPlatform.update();

                    doodlick.TurnDown(doodlick.dy, doodlick.y);

                    doodlick.Teleport(doodlick.x);

                    bomb.createBomb(sc.GetCurrentScore(),sBomb);

                    bomb.down(sBomb);

                    bomb.BOOM(gameover, sPers,sBomb);

                    doodlick.Fall(gameover, doodlick.y, sc.GetCurrentScore(), doodlick.dy);

                    if (doodlick.y < doodlick.h)
                    {
                        Green_Platform.movePlatforms(-doodlick.dy, doodlick.y, doodlick.h, score, sc.GetFS(), sc.GetCurrentScore());
                        if (levelset.GetLevel() == "m" || levelset.GetLevel() == "ha")
                            White_Platform.movePlatforms(-doodlick.dy, doodlick.y, score, sc.GetFS(), sc.GetCurrentScore());
                        if (levelset.GetLevel() == "ha")
                        {
                            Blue_Platform.movePlatforms(-doodlick.dy, doodlick.y, doodlick.h, score, sc.GetFS(), sc.GetCurrentScore());
                            YellowPlatform.moveplatforms(-doodlick.dy, doodlick.y, score, sc.GetFS(), sc.GetCurrentScore());
                        }
                    }

                    for (int i = 0; i < Size; ++i)
                    {
                        Green_Platform.TouchToPlatform(doodlick.x, doodlick.y, doodlick.dy, i);
                        if (levelset.GetLevel() == "m" || levelset.GetLevel() == "ha")
                            White_Platform.TouchToPlatform(doodlick.x, doodlick.y, doodlick.dy, i);
                        if (levelset.GetLevel() == "ha")
                        {
                            Blue_Platform.TouchToPlatform(doodlick.x, doodlick.y, doodlick.dy, i);
                            YellowPlatform.TouchToPlatform(doodlick.x, doodlick.y, doodlick.dy, i);
                        }
                    }
                }
            }


            sPers.setPosition(doodlick.x, doodlick.y);

            app.draw(sBackground);
            app.draw(sPers);

            Green_Platform.drawPlatforms(app, sPlat);
            White_Platform.drawPlatforms(app, sWhitePlat);
            Blue_Platform.drawPlatforms(app, sBluePlatfrom);
            YellowPlatform.drawplatforms(app, sYellowPlatform);

            app.draw(sBomb);


            for (int i = 0; i < 5; ++i)
                app.draw(score[i]);


            if (!gameover)
            {
                app.draw(sGameOver);

                if(ifgameover)
                {
                    Do_All(gameover);
                    ifgameover = false;
                }

            }



            app.display();
        }
    }

    // функція рестарту
    void ResetGame() {

        doodlick = Doodle_mech();
        bomb.constructor(sBomb);

        Green_Platform.clearPlatforms();
        White_Platform.clearPlatforms();
        Blue_Platform.clearPlatforms();
        YellowPlatform.clearPlatforms();

        for (int i = 0; i < 5; i++) {
            score[i].setTexture(textureManager.getTexture(5));
            score[i].setTextureRect(IntRect(0, 0, 30, 47));
            score[i].setPosition(35 * i, 0);
            sc.SetFS(i, 0);
        }

        levelset.Clear_current_level(Blue_Platform, White_Platform, Green_Platform, YellowPlatform);

        sc.SetFS(0, 0);
        sc.SetFS(1, 0);
        sc.SetFS(2, 0);
        sc.SetFS(3, 0);
        sc.SetFS(4, 0);
        sc.GetCurrentScore() = 0;
        gameover = true;
        ifgameover = true;
    }




    int getCurrentScore() {
        return sc.GetCurrentScore();
    }

    class ResetGameClass : public Command
    {
    public:
        ResetGameClass(CreateGame& createGame,bool& isf2pressed) : createGame_(createGame),isF2Pressed(isf2pressed) {}

        virtual void execute()
        {
            if(!isF2Pressed)
            {
            createGame_.ResetGame();
                isF2Pressed = true;
            }
        }

    private:

        CreateGame& createGame_;
        bool& isF2Pressed;

    };

    // додавання субєкту до спостерігача
    void addObserver(GameObserver* observer) {
        observers.push_back(observer);
    }

    // виконання змін якщо спостерігач щось помітив
    void Do_All(bool gameover) {
        if (!gameover) {
            for (GameObserver* observer : observers) {
                observer->OnGameOverChanged(gameover);
            }
        }
    }


private:
    GamePause gamePause;
    QWidget* parent;
    Music music;
    TextureManager textureManager;
    All_levels levelset;
    Doodle_mech doodlick;
    traps bomb;
    Platform Green_Platform;
    WhitePlatform White_Platform;
    MovingPlatform Blue_Platform;
    ExtremePlatform YellowPlatform;
    Score sc;
    Sprite score[5];
    Sprite sGameOver; //&
    Sprite sBomb; Sprite sBackground; Sprite sPlat; Sprite sPers; Sprite sWhitePlat; Sprite sBluePlatfrom; Sprite sYellowPlatform;
    int Size;
    bool isTabPressed;
    bool gamePaused;
    bool isF1Pressed;
    bool isMusicPlaying;
    bool ifgameover;
    InputHandler inputHandler;
    bool gameover;
    RenderWindow& app;
    CloseApp closeApp;
    Music_ON_OFF music_ON_OFF;

    std::vector<GameObserver*> observers;
    ScoreDisplay scoreDisplay;

    bool isF2Pressed;

    std::unique_ptr<MoveStrategy> strategy;



};


