//
// Created by USER on 11/17/2022.
//

#ifndef MAZE_MAINMENU_H
#define MAZE_MAINMENU_H
#import <SFML/Graphics.hpp>

class mainMenu {
private:
    int char_num;
public:
    static void print();
    static void start();
    static int prerun();
    static void printExitBgSprite (sf::RenderWindow *window);
    static void printExitBtn(sf::RenderWindow *window, int x, int y);
    static void putIcoInWindow(sf::RenderWindow *window);
    static void exit();
    static void about();
    static void info();
};


#endif //MAZE_MAINMENU_H
