#include "choose.h"
#include <SFML/Graphics.hpp>
#include "../main/mainMenu.h"
#include <windows.h>
#include "../game/Game.h"

sf::RenderWindow charsWindow;

const int W = 27;
const int H = 11;
const int mltp = 30;
const int BASE_OFFSET = 25;
const int IMG_OFFSET = 175;
const int WIDTH = 30;
const int IMG_MLTPL = 3;
const int HEIGHT = 50;

std::string Dir = "C:/maze/chars/";
std::string mask = "png";
sf::Sprite exitMark;
sf::Sprite questMark;

bool isHover2(sf::FloatRect sprite, sf::Vector2f mp){
    if(sprite.contains(mp)) {
        return true;
    } else {
        return false;
    }
}

void printQuestBtn(sf::RenderWindow *window) {
    sf::Image questionImg;
    questionImg.loadFromFile("C:/maze/img/utility/about.png");
    sf::Texture questionTexture;
    questionTexture.loadFromImage(questionImg);
    questMark.setTexture(questionTexture);
    questMark.setScale(0.5,0.5);
    questMark.setPosition(755,10);
    window->draw(questMark);
}

void printBg () {
    sf::Texture bg;
    bg.loadFromFile("C:/maze/img/utility/phon3.png");
    sf::Sprite background(bg);
    background.setPosition(0,0);
    charsWindow.draw(background);
}

int getCharNum() {
    std::vector<std::string> s;
    std::string path;
    path+= Dir + "*." + mask;
    WIN32_FIND_DATA ffd;
    HANDLE hl = FindFirstFileA(path.c_str(),&ffd);
    int counter = 0;
    if (hl != INVALID_HANDLE_VALUE) {
        do {
            counter++;
        } while (FindNextFileA(hl,&ffd) != 0);
    } else {
        MessageBoxA(nullptr, "FILES NOT FOUND !!!", "About", MB_OK);
    }
    return counter+2;
}

void choose::printExitBtn(sf::RenderWindow *window) {
    sf::Image questionImg;
    questionImg.loadFromFile("C:/maze/img/utility/close.png");
    sf::Texture questionTexture;
    questionTexture.loadFromImage(questionImg);
    exitMark.setTexture(questionTexture);
    exitMark.setScale(0.5,0.5);
    exitMark.setPosition(780, 10);
    window->draw(exitMark);
}

void choose::print() {
    charsWindow.create(sf::VideoMode(W * mltp, H * mltp), "CHOOSE YOUR CHARACTER !" ,sf::Style::None);
    sf::Image img;
    img.loadFromFile("C:/maze/img/newico.png");
    charsWindow.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
    printBg();
    choose::printExitBtn(&charsWindow);
    int char_num = getCharNum();
    sf::Sprite *stArr[char_num];
    for (int i = 0; i < char_num; ++i) {
        std::string path;
        path+=Dir + "char";
        int num = i + 1;
        if (num != 7 && num != 8) {
            path+=std::to_string(num);
        } else {
            path+=std::to_string(num) + "/up";
        }
        path+="." + mask;
        img.loadFromFile(path);
        sf::Texture hero;
        hero.loadFromImage(img);
        stArr[i] = new sf::Sprite;
        if (i < 4) {
            stArr[i]->setPosition((float)BASE_OFFSET + (float)i*(WIDTH+IMG_OFFSET),BASE_OFFSET);
        } else {
            stArr[i]->setPosition((float)BASE_OFFSET + (float)(i-4)*(WIDTH+IMG_OFFSET),BASE_OFFSET + HEIGHT*IMG_MLTPL);
        }
        stArr[i]->setTexture(hero);
        if (num == 7 || num == 8) {
            stArr[i]->setScale(0.6, 0.6);
        }
        charsWindow.draw(*stArr[i]);
    }
    printQuestBtn(&charsWindow);
    charsWindow.display();
    while(charsWindow.isOpen()) {
        sf::Event event{};
        while (charsWindow.pollEvent(event)){
            if(event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mp;
                    mp.x = (float)sf::Mouse::getPosition(charsWindow).x;
                    mp.y = (float)sf::Mouse::getPosition(charsWindow).y;
                    if (Game::isHover(exitMark.getGlobalBounds(), mp)) {
                        charsWindow.close();
                    }
                    if(Game::isHover(questMark.getGlobalBounds(), mp)) {
                        mainMenu::info();
                    }
                    for (int i = 0; i < char_num; ++i) {
                        if(isHover2(stArr[i]->getGlobalBounds(), mp)) {
                            charsWindow.close();
                            Game::prerun(i+1);
                        }
                    }
                }
            }
        }
    }
}