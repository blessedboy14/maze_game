//
// Created by USER on 11/17/2022.
//

#ifndef MAIN_GAME_H
#define MAIN_GAME_H
#include <SFML/Graphics.hpp>

class Game {
public:
    static void print();
    static void win();
    static void game(int** &maze, int width);
    static void prerun(int num);
    static bool isHover(sf::FloatRect sprite, sf::Vector2f mp);
};


#endif //MAIN_GAME_H
