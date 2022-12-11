//
// Created by USER on 11/17/2022.
//

#include "mainMenu.h"

#include <SFML/Graphics.hpp>

#include <windows.h>
#include "../choose/choose.h"
#include <random>
#include "../game/Game.h"

const int W = 40;
const int H = 28;
const int mltp = 30;
const int FONT_SIZE = 50;

sf::RenderWindow startWindow;
sf::Font mainFont;
sf::Text ExitGame;
sf::Text startGame;
sf::Text AboutGame;
sf::Text ChooseChr;
sf::RenderWindow exitWindow;
sf::Text YesLbl;
sf::Text NoLbl;
sf::Text helpText;
sf::Sprite exitIco;
sf::RenderWindow aboutWindow;

bool isHover(sf::FloatRect sprite, sf::Vector2f mp){
    if(sprite.contains(mp)) {
        return true;
    } else {
        return false;
    }
}

void printBgSprite () {
    sf::Texture bg;
    bg.loadFromFile("C:/maze/img/utility/phon.png");
    sf::Sprite background(bg);
    background.setPosition(0,0);
    startWindow.draw(background);
}

void printStartText () {
    startGame.setString("Start Game");
    startGame.setFont(mainFont);
    startGame.setCharacterSize(FONT_SIZE);
    startGame.setPosition((W * mltp) / 2.0 - 90.0,220);
    startWindow.draw(startGame);
}

void printAboutText () {
    AboutGame.setString("About");
    AboutGame.setFont(mainFont);
    AboutGame.setCharacterSize(50);
    AboutGame.setPosition((W * mltp) / 2.0 - 50,220 + AboutGame.getCharacterSize()*1.2);
    startWindow.draw(AboutGame);
}

void printExitText () {
    ExitGame.setString("Exit Game");
    ExitGame.setFont(mainFont);
    ExitGame.setCharacterSize(50);
    ExitGame.setPosition((W * mltp) / 2.0 - 76.0,220 + ExitGame.getCharacterSize()*4.9);
    startWindow.draw(ExitGame);
}

void printChooseText () {
    ChooseChr.setString("Choose Character");
    ChooseChr.setFont(mainFont);
    ChooseChr.setCharacterSize(50);
    ChooseChr.setPosition((W * mltp) / 2.0 - 145,220 + ChooseChr.getCharacterSize()*2.3);
    startWindow.draw(ChooseChr);
}

void printInfoText () {
    helpText.setString("Instruction");
    helpText.setFont(mainFont);
    helpText.setCharacterSize(50);
    helpText.setPosition((W * mltp) / 2.0 - 100,220 + helpText.getCharacterSize()*3.6);
    startWindow.draw(helpText);
}

void mainMenu::putIcoInWindow(sf::RenderWindow *window) {
    sf::Image img;
    img.loadFromFile("C:/maze/img/newico.png");
    window->setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
}

void mainMenu::printExitBtn(sf::RenderWindow *window, int x, int y) {
    sf::Image questionImg;
    questionImg.loadFromFile("C:/maze/img/utility/close.png");
    sf::Texture questionTexture;
    questionTexture.loadFromImage(questionImg);
    exitIco.setTexture(questionTexture);
    exitIco.setScale(0.5,0.5);
    exitIco.setPosition(x, y);
    window->draw(exitIco);
}

void mainMenu::info() {
    sf::RenderWindow infoWindow(sf::VideoMode(1000, 800), "Info", 0);
    sf::Texture arrows;
    sf::Text allText;
    sf::Sprite chr_sprite;
    allText.setFont(mainFont);
    allText.setFillColor(sf::Color(10,10,10));
    allText.setCharacterSize(65);
    sf::Texture bg;
    bg.loadFromFile("C:/maze/img/utility/infoBg2.png");
    sf::Sprite background(bg);
    background.setPosition(0,0);
    infoWindow.draw(background);
    arrows.loadFromFile("C:/maze/img/utility/mvm.png");
    sf::Sprite arrowSprite(arrows);
    arrowSprite.setPosition(60,25);
    arrowSprite.setScale(0.4,0.4);
    allText.setString("   Use this keys to\n move your character");
    allText.setPosition(500, 10);
    infoWindow.draw(arrowSprite);
    infoWindow.draw(allText);
    mainMenu::printExitBtn(&infoWindow, 970, 10);
    allText.setString("SPELLS");
    allText.setCharacterSize(90);
    allText.setPosition(400, 130);
    infoWindow.draw(allText);
    sf::Texture chr_texture;
    chr_texture.loadFromFile("C:/maze/chars/char7/up.png");
    chr_sprite.setTexture(chr_texture);
    chr_sprite.setScale(0.6,0.6);
    chr_sprite.setPosition(100, 250);
    allText.setString("    Tank can destroy single wall with shot\nto use your spell you should stand near the\n wall "
                      "then press R and choose the direction.");
    allText.setCharacterSize(42);
    allText.setPosition(340, 250);
    infoWindow.draw(chr_sprite);
    infoWindow.draw(allText);

    sf::Sprite chr_sprite2;
    sf::Sprite chr_sprite3;
    chr_texture.loadFromFile("C:/maze/chars/char8/up.png");
    chr_sprite2.setTexture(chr_texture);
    chr_sprite2.setScale(0.75,0.70);
    chr_sprite2.setPosition(100, 430);
    allText.setString("   The beatle can reveal wide circle\n area for three seconds to use your\nspell press R then click on the screen");
    allText.setCharacterSize(42);
    allText.setPosition(380, 430);
    infoWindow.draw(chr_sprite2);
    infoWindow.draw(allText);
    sf::Rect<float> exit{{970,10}, {30,30}};
    std::string path;
    for (int i = 1; i < 7; i++) {
        path = "c:/maze/img/chars/char";
        path += std::to_string(i);
        path+= ".png";
        chr_texture.loadFromFile(path);
        chr_sprite3.setTexture(chr_texture);
        chr_sprite3.setScale(1.25,1.25);
        if (i < 4)
            chr_sprite3.setPosition(50 + (i - 1) * 70, 630);
        else
            chr_sprite3.setPosition(50 + (i - 4) * 70, 700);
        infoWindow.draw(chr_sprite3);
    }
    allText.setString("   The rest of chars can teleport\nto teleport click mouse in point and\n"
                      "your char will tp in nearest free cell\n  the max tp range is eight hundreds");
    allText.setCharacterSize(40);
    allText.setPosition(400, 600);
    infoWindow.draw(allText);
    infoWindow.display();
    while (infoWindow.isOpen()) {
        sf::Event event{};
        while (infoWindow.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (Game::isHover(exit, static_cast<sf::Vector2f>(sf::Mouse::getPosition(infoWindow)))) {
                        infoWindow.close();
                    }
                }
            }
        }
    }
}

void mainMenu::print() {
    mainMenu::putIcoInWindow(&startWindow);
    printBgSprite();
    printStartText();
    printAboutText();
    printExitText();
    printChooseText();
    printInfoText();
}

int mainMenu::prerun() {
    srand(time(NULL));
    int num = rand()%7;
    return num+1;
}

void mainMenu::start() {
    startWindow.create(sf::VideoMode(W * mltp, H * mltp), "NIGHT STALKER !", sf::Style::None);
    mainFont.loadFromFile("C:/maze/font/font.ttf");
    print();
    startWindow.display();
    while(startWindow.isOpen()) {
        sf::Event event{};

        while (startWindow.pollEvent(event)){
            sf::Vector2f mp;
            mp.x = (float)sf::Mouse::getPosition(startWindow).x;
            mp.y = (float)sf::Mouse::getPosition(startWindow).y;
            if(event.type == sf::Event::Closed) {
                mainMenu::exit();
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if(isHover(ExitGame.getGlobalBounds(), mp)) {
                        mainMenu::exit();
                    } else if (isHover(AboutGame.getGlobalBounds(), mp)) {
                        mainMenu::about();
                    } else if (isHover(ChooseChr.getGlobalBounds(),mp)) {
                        choose::print();
                    } else if(isHover(startGame.getGlobalBounds(), mp)) {
                        startWindow.setVisible(false);
                        Game::prerun(mainMenu::prerun());
                    } else if(isHover(helpText.getGlobalBounds(), mp)) {
                        mainMenu::info();
                    }
                }
            }
        }
        sf::Vector2f mp;
        mp.x = (float)sf::Mouse::getPosition(startWindow).x;
        mp.y = (float)sf::Mouse::getPosition(startWindow).y;
    }
}

void printExitAsk() {
    sf::Text exitAsk;
    exitAsk.setString("Are you really\n want to exit");
    exitAsk.setFont(mainFont);
    exitAsk.setCharacterSize(45);
    exitAsk.setPosition(95, 30);
    exitWindow.draw(exitAsk);
    sf::Image questionImg;
    questionImg.loadFromFile("C:/maze/img/utility/question.png");
    sf::Texture questionTexture;
    questionTexture.loadFromImage(questionImg);
    sf::Sprite question;
    question.setTexture(questionTexture);
    question.setPosition(219 + 85 , exitAsk.getGlobalBounds().top + exitAsk.getGlobalBounds().height - 23);
    exitWindow.draw(question);
}

void printYesNo() {
    YesLbl.setString("YES");
    YesLbl.setFont(mainFont);
    YesLbl.setCharacterSize(45);
    YesLbl.setPosition(65, 140);
    exitWindow.draw(YesLbl);
    NoLbl.setString("NO");
    NoLbl.setFont(mainFont);
    NoLbl.setCharacterSize(45);
    NoLbl.setPosition(335 -NoLbl.getGlobalBounds().width, 140);
    exitWindow.draw(NoLbl);
}

void mainMenu::printExitBgSprite (sf::RenderWindow *window) {
    sf::Texture bg;
    bg.loadFromFile("C:/maze/img/utility/exit_bg.png");
    sf::Sprite background(bg);
    background.setPosition(0,0);
    window->draw(background);
}

sf::Vector2i randomlyChoose(int width, int height) {
    srand(time(nullptr));
    float x = YesLbl.getGlobalBounds().left + 10;
    float y = YesLbl.getGlobalBounds().top + 10;
    sf::Vector2f tempVec = {x,y};
    while (isHover(YesLbl.getGlobalBounds(), tempVec)) {
        x = rand()%width;
        y = rand()%height;
        tempVec = {x,y};
    }
    int newX = floor(tempVec.x);
    int newY = floor(tempVec.y);
    sf::Vector2i newMouse = {newX,newY};
    return newMouse;
}

void mainMenu::exit() {
    exitWindow.create(sf::VideoMode(400,210), "Exit?",sf::Style::None);
    printExitBgSprite(&exitWindow);
    printExitAsk();
    printYesNo();
    mainMenu::putIcoInWindow(&exitWindow);
    exitWindow.display();
    srand(time(nullptr));
    int repeatTimes = 0;
    repeatTimes = rand()%2;
    while(exitWindow.isOpen()) {
        sf::Event event;

        while(exitWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                exitWindow.close();
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mp;
                    mp.x = (float)sf::Mouse::getPosition(exitWindow).x;
                    mp.y = (float)sf::Mouse::getPosition(exitWindow).y;
                    if(isHover(YesLbl.getGlobalBounds(), mp)) {
                        if (repeatTimes != 0) {
                            sf::Vector2i newMouse = randomlyChoose(400, 210);
                            sf::Mouse::setPosition(newMouse, exitWindow);
                            repeatTimes--;
                        } else {
                            exitWindow.close();
                            startWindow.close();
                        }
                    }
                    if(isHover(NoLbl.getGlobalBounds(), mp)) {
                        exitWindow.close();
                    }
                }
            }
        }
    }
}

void printAboutInfo() {
    sf::Text aboutInfo;
    aboutInfo.setString("\t\tDeveloper\n   BSUIR POIT student\n    Prokopchuk Daniil");
    aboutInfo.setFont(mainFont);
    aboutInfo.setCharacterSize(45);
    aboutInfo.setPosition(20, 22);
    aboutWindow.draw(aboutInfo);
}

void mainMenu::about() {
    aboutWindow.create(sf::VideoMode(400,210), "About",sf::Style::None);
    printExitBgSprite(&aboutWindow);
    mainMenu::printExitBtn(&aboutWindow, 370, 10);
    mainMenu::putIcoInWindow(&aboutWindow);
    printAboutInfo();
    aboutWindow.display();
    while(aboutWindow.isOpen()) {
        sf::Event event{};
        while (aboutWindow.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mp((float)sf::Mouse::getPosition(aboutWindow).x, (float)sf::Mouse::getPosition(aboutWindow).y);
                    if (isHover(exitIco.getGlobalBounds(), mp)) {
                        aboutWindow.close();
                    }
                }
            }
        }
    }
}
