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

using namespace sf;


class Game {
public:
    int x, y, h;
    float dx, dy;
    Game() {
        x = 100;
        y = 100;
        h = 200;
        dx = 0;
        dy = 0;

    }
};

class BasicMechanics
{
public:
    void TurnDown(float& dy, int& y)
    {
        dy += 0.2;
        y += dy;
    }
    void Teleport(int& x)
    {
        if (x > 400)
            x = -40;
        if (x < -40)
            x = 400;
    }
    void Fall(bool& gameover, int y, int score, float& dy)
    {
        if (y > 520)
        {
            if (score != 0)
                gameover = false;
            else
                dy = -10;
        }
    }

};

class Platform {
public:
    virtual void createPlatform(int count) {
        for (int i = 0; i < count; ++i) {
            Vector2f p;
            p.x = rand() % 400;
            p.y = rand() % 533;
            plat.push_back(p);
        }
    }

    void clearPlatforms() {
        plat.clear();
    }

// рухаю платформи у верх та змінюю текстури у рахуноку
    void movePlatforms(float dy, int& y, int& h, Sprite score[], int fs[], int& sc) {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = h;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > 533) {
                plat[i].y = 0;
                plat[i].x = rand() % 400;
                ++sc;

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
// прижок вверх
    virtual void TouchToPlatform(int x, int y, float& dy, int index)
    {
        if ((x + 50 > getPlatformX(index)) && (x + 20 < getPlatformX(index) + 68) && (y + 70 > getPlatformY(index)) && (y + 70 < getPlatformY(index) + 14) && (dy > 0))
        {
            dy = -10;
        }
    }
    int Size()
    {
        return plat.size();
    }



protected:
    std::vector<Vector2f> plat;

};

class WhitePlatform : virtual public Platform {
public:

    void settakenWhitePlatforms(int index, bool boolean) {
            takenWhitePlatforms[index] = boolean;
    }
    bool gettakenWhitePlatforms(int index) {
            return takenWhitePlatforms[index];
    }



// такі є самі функції як і в platform тільки додав перевірку на доторкання до платформи
    void movePlatforms(float dy, int& y,Sprite score[], int fs[], int& sc)  {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = 200;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > 533) {
                if (gettakenWhitePlatforms(i))
                    settakenWhitePlatforms(i, false);
                sc++;
                plat[i].y = 0;
                plat[i].x = rand() % 400;

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

    void createPlatform(int count) override {
        for (int i = 0; i < count; ++i) {
            Vector2f p;
            p.x = rand() % 400;
            p.y = rand() % 533;
            int move;
            move = rand() % 2 == 0 ? -1 : 1;
            direction.push_back(move);
            plat.push_back(p);
        }
    }



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


class Level
{
public:
    void SetLevel(std::string levelofgame)
    {
        level = levelofgame;
    }

    std::string GetLevel()
    {
        return level;
    }


private:
    std::string level;
};

class EasyLevel
{
public:
    void playLevel(Platform& Green_Platform)
    {
        Green_Platform.createPlatform(10);
    }
};

class MediumLevel
{
public:
    void playLevel(Platform& Green_Platform, WhitePlatform& White_Platform)
    {
        Green_Platform.createPlatform(5);
        White_Platform.createPlatform(5);
    }
};

class HardLevel
{
public:
    void playLevel(MovingPlatform& Blue_Platform, WhitePlatform& White_Platform, Platform& Green_Platform, ExtremePlatform& Yellow_Platfrom)
    {
        Green_Platform.createPlatform(2);
        White_Platform.createPlatform(2);
        Blue_Platform.createPlatform(2);
        Yellow_Platfrom.createplatform(2);
    }
};

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

class traps : public Game
{
public:
    traps(Sprite& b) : sBomb(b) // Передача по ссылке
    {
        i = 1;
        x = 200;
        y = -1;
        dy = 2.5;
        sBomb.setPosition(-100, -100);
    }

    void createBomb(int number)
    {
        if (number > 50 * i)
        {

            ++i;
            dx = rand() % 400;
            sBomb.setPosition(dx, 0);// Изменение объекта Sprite через ссылку
            y = 0;

        }
    }

    void down()
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
    void BOOM(bool& gameover,Sprite sBomb,Sprite sPers)
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
    void SetSBOMB()
    {
        sBomb.setPosition(-100,-100);
    }

private:
    int i;
    int dx;
    Sprite& sBomb; // Ссылка на объект Sprite
};

void ResetGame(traps& trap, int size,bool& ifgameover,TextureManager& textureManager, HardLevel& hardLevel, MediumLevel& mediumLevel, EasyLevel& easyLevel, Level& level, Game& game, Platform& Green_Platform, WhitePlatform& White_Platform, MovingPlatform& Blue_Platform, ExtremePlatform& YellowPlatform, Score& sc, Sprite score[], bool& gameover) {
    game.x = 100;
    game.y = 100;
    game.h = 200;
    game.dy = 0;

  trap.dy = 2.5;
   trap.y = -1;
  trap.SetI(1);
   trap.x = 200;
  trap.SetSBOMB();


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

    if (level.GetLevel() == "e") {
        easyLevel.playLevel(Green_Platform);
    }
    else if (level.GetLevel() == "m") {
        mediumLevel.playLevel(Green_Platform, White_Platform);

        for (int i =0; i< size;++i)
        White_Platform.settakenWhitePlatforms(i, false);
    }
    else if (level.GetLevel() == "ha") {
        hardLevel.playLevel(Blue_Platform, White_Platform, Green_Platform, YellowPlatform);
        for (int i =0; i< size;++i)
        {
        White_Platform.settakenWhitePlatforms(i, false);
        YellowPlatform.settakenWhitePlatforms(i, false);
        }
    }

    sc.SetFS(0, 0);
    sc.SetFS(1, 0);
    sc.SetFS(2, 0);
    sc.SetFS(3, 0);
    sc.SetFS(4, 0);
    sc.GetCurrentScore() = 0;
    gameover = true;
    ifgameover = true;
}

void RunGame (bool& controller,QWidget* parent,Music &music, TextureManager& textureManager,HardLevel& hardLevel,MediumLevel& mediumLevel,EasyLevel& easyLevel,RenderWindow& app, Game& game, traps& bomb, Level& level, Platform& Green_Platform, WhitePlatform& White_Platform, MovingPlatform& Blue_Platform, ExtremePlatform& YellowPlatform, Score& sc, Sprite score[], Sprite& sGameOver, Sprite& sBomb, Sprite& sBackground, Sprite& sPlat, Sprite& sPers, Sprite& sWhitePlat, Sprite& sBluePlatfrom, Sprite& sYellowPlatform, BasicMechanics& mech,int& Size, bool gameover) {


    music.play();
    music.setLoop(true);

    bool isTabPressed = false;
    bool gamePaused = false;

    bool isF1Pressed = false;
    bool isMusicPlaying =true;

    bool ifgameover = true;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }

        app.clear();

        if (Keyboard::isKeyPressed(Keyboard::Escape)) app.close();

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

        // Перевірка, чи клавіша "F1" відпущена
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            isF1Pressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
           ResetGame(bomb,Size,ifgameover,textureManager, hardLevel, mediumLevel, easyLevel, level, game, Green_Platform, White_Platform, Blue_Platform, YellowPlatform,sc, score,gameover);
        }



        if (!gamePaused)
        {
            if (gameover)
            {

                if(controller)
                {
        if (Keyboard::isKeyPressed(Keyboard::Right)) game.x += 4;
        if (Keyboard::isKeyPressed(Keyboard::Left)) game.x -= 4;
                }
                else
                {
        if (Keyboard::isKeyPressed(Keyboard::D)) game.x += 4;
        if (Keyboard::isKeyPressed(Keyboard::A)) game.x -= 4;
                }

        Blue_Platform.update();
        YellowPlatform.update();

        mech.TurnDown(game.dy, game.y);

        mech.Teleport(game.x);

        bomb.createBomb(sc.GetCurrentScore());

        bomb.down();

        bomb.BOOM(gameover, sBomb, sPers);

        mech.Fall(gameover, game.y, sc.GetCurrentScore(), game.dy);

        if (game.y < game.h)
        {
            Green_Platform.movePlatforms(-game.dy, game.y, game.h, score, sc.GetFS(), sc.GetCurrentScore());
            if (level.GetLevel() == "m" || level.GetLevel() == "ha")
                White_Platform.movePlatforms(-game.dy, game.y, score, sc.GetFS(), sc.GetCurrentScore());
            if (level.GetLevel() == "ha")
            {
                Blue_Platform.movePlatforms(-game.dy, game.y, game.h, score, sc.GetFS(), sc.GetCurrentScore());
                YellowPlatform.moveplatforms(-game.dy, game.y, score, sc.GetFS(), sc.GetCurrentScore());
            }
        }

        for (int i = 0; i < Size; ++i)
        {
            Green_Platform.TouchToPlatform(game.x, game.y, game.dy, i);
            if (level.GetLevel() == "m" || level.GetLevel() == "ha")
                White_Platform.TouchToPlatform(game.x, game.y, game.dy, i);
            if (level.GetLevel() == "ha")
            {
                Blue_Platform.TouchToPlatform(game.x, game.y, game.dy, i);
                YellowPlatform.TouchToPlatform(game.x, game.y, game.dy, i);
            }
        }
       }
      }


        sPers.setPosition(game.x, game.y);

        app.draw(sBackground);
        app.draw(sPers);

        Green_Platform.drawPlatforms(app, sPlat);
        White_Platform.drawPlatforms(app, sWhitePlat);
        Blue_Platform.drawPlatforms(app, sBluePlatfrom);
        YellowPlatform.drawplatforms(app, sYellowPlatform);

        app.draw(sBomb);

        for (int i = 0; i < 5; ++i)
            app.draw(score[i]);

        if (!gameover and ifgameover)
        {
            app.draw(sGameOver);


            std::string asd = std::to_string(sc.GetCurrentScore()); // Convert integer to string
            QString qString = QString::fromStdString(asd);

            QMessageBox::about(parent,"  Your score  ", qString);
            ifgameover = false;

             //   RunGame(music,textureManager,hardLevel, mediumLevel, easyLevel, app, game, bomb, level, Green_Platform, White_Platform, Blue_Platform, YellowPlatform, sc, score, sGameOver, sBomb, sBackground, sPlat, sPers, sWhitePlat, sBluePlatfrom, sYellowPlatform, mech, Size, true);

        }

        app.display();
    }
}
