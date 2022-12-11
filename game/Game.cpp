#include "Game.h"
#include <SFML/Graphics.hpp>
#include "../hero/Hero.h"
#include "../main/mainMenu.h"
#include <cmath>
#include "../door/door.h"

typedef struct drct{
    std::string left = "left";
    std::string right = "right";
    std::string up = "up";
    std::string down = "down";
}Directions;

const int W = 37;
const int H = 19;
const int mltp = 50;

const int pass = 1;
const int room = 4;
const int wall = 0;
const int hero_maze = 5;
const int room_door = 3;
const int end_door = 6;
const int silver_key = 2;
const int gold_key = 10;

const int HEIGHT = 37;
const int WIDTH = 19;
const int MAX_PORT_DISTANCE = 800;

int spellCounter = 0;
bool spellStart = false;

typedef struct key{
    int x;
    int y;
}key_info;

key_info silver;
key_info gold;

bool isWin = false;

door door1(0,0);
door door2(0,0);

int** maze;

sf::RenderWindow gameWindow;
sf::Font sameFont;
sf::Font digitsFont;
sf::Sprite exit_spell;
sf::Text yesLbl;
sf::Sprite hero;
sf::Texture hero_texture;
sf::Image hero_Img;
sf::Sprite keySprite;
Hero mainHero(0,0,0,0,0);
std::string wall_path;
sf::Rect<float> silver_Rect;
sf::Rect<float> gold_Rect;
sf::Text okText;

const std::string keyPos[] = {"0/1","1/1"};
bool silverFound = false;
bool goldenFound = false;

void printKeysData() {
    sf::Text key;
    if (silverFound)
        key.setString(keyPos[1]);
    else
        key.setString(keyPos[0]);
    key.setCharacterSize(30);
    digitsFont.loadFromFile("C:/maze/font/font3.ttf");
    key.setFont(digitsFont);
    key.setPosition(1710, 10);
    gameWindow.draw(key);
    if (goldenFound)
        key.setString(keyPos[1]);
    else
        key.setString(keyPos[0]);
    key.setCharacterSize(30);
    key.setPosition(1780, 10);
    gameWindow.draw(key);
    sf::Image keyImg;
    keyImg.loadFromFile("C:/maze/img/utility/key2.png");
    sf::Texture keyTexture;
    keyTexture.loadFromImage(keyImg);
    keySprite.setTexture(keyTexture);
    keySprite.setPosition(1710,45);
    gameWindow.draw(keySprite);
    keyImg.loadFromFile("C:/maze/img/utility/key.png");
    keyTexture.loadFromImage(keyImg);
    keySprite.setTexture(keyTexture);
    keySprite.setPosition(1780,45);
    gameWindow.draw(keySprite);
}

std::string chooseWallImg() {
    srand(time(nullptr));
    std::string path = "C:/maze/img/walls/";
    int num = rand()%13+1;
    path += std::to_string(num) + ".png";
    return path;
}

bool deadEnd(int x, int y, int** main_maze, int height, int width){
    int a = 0;
    if(x != 1){
        if(main_maze[y][x-2] == pass||
                main_maze[y][x-2] == room)
            a+=1;
    }
    else a+=1;
    if(y != 1){
        if(main_maze[y-2][x] == pass||
                main_maze[y-2][x] == room)
            a+=1;
    }
    else a+=1;
    if(x != width-2){
        if(main_maze[y][x+2] == pass||
                main_maze[y][x+2] == room)
            a+=1;
    }
    else a+=1;
    if(y != height-2){
        if(main_maze[y+2][x] == pass||
                main_maze[y+2][x] == room)
            a+=1;
    }
    else a+=1;
    if(a == 4)
        return true;
    else
        return false;
}

void pickUpKey() {
    auto x = (float)mainHero.getX();
    auto y = (float)mainHero.getY();
    sf::Vector2f hero_vector(x,y);
    if (!silverFound && Game::isHover(silver_Rect, hero_vector)) {
        maze[silver.x][silver.y] = pass;
        silverFound = true;
    }
    if (!goldenFound && Game::isHover(gold_Rect, hero_vector)) {
        maze[gold.x][gold.y] = pass;
        goldenFound = true;
    }
}

void mazemake(int** main_maze, int height, int width){
    int x, y, c, a;
    bool b;
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            main_maze[i][j] = wall;

    int rheight = 3, rwidth = 5;
    rheight--;rwidth--;
    int room_num = 2;
    bool swap = true;
    int gold_key_room = rand()%2;
    for(int l = 0; l < room_num; l++){
        b = true;
        while(b){
            do{
                if(rwidth%4 == 0)
                    x = 2*(rand()%(width/2))+1;
                else
                    x = 2*(rand()%(width/2))+2;
                if(rheight%4 == 0)
                    y = 2*(rand()%(height/2))+1;
                else
                    y = 2*(rand()%(height/2))+2;
            }
            while(x < (rwidth+2) || x > (width-rwidth-2) ||
                  y < (rheight+2) || y > (height-rheight-2));

            b = false;
            for(int i = (y-rheight-2); i < (y+rheight+2); i++)
                for(int j = (x-rwidth-2); j < (x+rwidth+2); j++)
                    if(main_maze[i][j] == room)
                        b = true;

            if(b)
                continue;

            int temp_x = rand()%rheight + (y - rheight/2);
            int temp_y = rand()%rwidth + (x - rwidth/2);


            for(int i = (y-rheight/2); i < (y+rheight/2+1); i++)
                for(int j = (x-rwidth/2); j < (x+rwidth/2+1); j++)
                    main_maze[i][j] = room;

            if (gold_key_room == l) {
                main_maze[temp_x][temp_y] = gold_key;
                gold.x = temp_x; gold.y = temp_y;
                sf::Vector2f temp = {(float)temp_x-1,(float)temp_y-1};
                sf::Vector2f size = {3,3};
                gold_Rect = sf::Rect<float>(temp,size);
            }

            c = rand()%4;
            if(c == 0) {
                main_maze[y+rheight/2+1][x-rwidth/2+2*(rand()%(rwidth/2+1))] = room_door;
            }
            if(c == 1) {
                main_maze[y - rheight / 2 - 1][x - rwidth / 2 + 2 * (rand() % (rwidth / 2 + 1))] = room_door;
            }
            if(c == 2) {
                main_maze[y - rheight / 2 + 2 * (rand() % (rheight / 2 + 1))][x + rwidth / 2 + 1] = room_door;
            }
            if(c == 3) {
                main_maze[y - rheight / 2 + 2 * (rand() % (rheight / 2 + 1))][x - rwidth / 2 - 1] = room_door;
            }
            if(swap){
                rheight += rwidth;
                rwidth = rheight - rwidth;
                rheight -= rwidth;
            }
        }
    }

    int doors = 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (main_maze[i][j] == room_door) {
                if (doors > 1) {
                    door1.i = i;
                    door1.j = j;
                } else {
                    door2.i = i;
                    door2.j = j;
                }
                doors--;
            }
        }
    }

    x = 3; y = 3; a = 0;
    while(a < 10000){
        main_maze[y][x] = pass; a++;
        while(true){
            c = rand()%4;
            switch(c){
                case 0: if(y != 1)
                    if(main_maze[y-2][x] == wall){
                        main_maze[y-1][x] = pass;
                        main_maze[y-2][x] = pass;
                        y-=2;
                    }
                case 1: if(y != height-2)
                    if(main_maze[y+2][x] == wall){
                        main_maze[y+1][x] = pass;
                        main_maze[y+2][x] = pass;
                        y+=2;
                    }
                case 2: if(x != 1)
                    if(main_maze[y][x-2] == wall){
                        main_maze[y][x-1] = pass;
                        main_maze[y][x-2] = pass;
                        x-=2;
                    }
                case 3: if(x != width-2)
                    if(main_maze[y][x+2] == wall){
                        main_maze[y][x+1] = pass;
                        main_maze[y][x+2] = pass;
                        x+=2;
                    }
                default:
                    break;
            }
            if(deadEnd(x,y,main_maze,height,width))
                break;
        }

        if(deadEnd(x,y,main_maze,height,width))
            do{
                x = 2*(rand()%((width-1)/2))+1;
                y = 2*(rand()%((height-1)/2))+1;
            } while(main_maze[y][x] != pass);
    }
    bool notPlaced = true;
    while(notPlaced) {
        x = rand()%11+9;
        y = rand()%16+1;
        notPlaced = maze[x][y] != pass;
    }
    main_maze[x][y] = silver_key;
    silver.x = x; silver.y = y;
    sf::Vector2f temp = {(float)x-1,(float)y-1};
    sf::Vector2f size = {3,3};
    silver_Rect = sf::Rect<float>(temp,size);
    main_maze[0][width/2] = pass;
    main_maze[0][width/2-2] = pass;
    main_maze[0][width/2-1] = hero_maze;
    main_maze[height-1][width/2-1] = end_door;
    main_maze[height-1][width/2-2] = end_door;
    main_maze[height-1][width/2] = end_door;
}

std::string getHeroImgPath(int direction) {
    std::string hero_path = "C:/maze/img/chars/";
    hero_path += "char";
    if ( mainHero.getCharNumber() != 7 && mainHero.getCharNumber() != 8) {
        hero_path += std::to_string(mainHero.getCharNumber());
        hero_path += ".png";
    } else {
        Directions drcts;
        hero_path += std::to_string(mainHero.getCharNumber());
        hero_path += "/";
        switch (direction) {
            case 0:
                hero_path += drcts.right;
                break;
            case 1:
                hero_path += drcts.left;
                break;
            case 2:
                hero_path += drcts.up;
                break;
            case 3:
                hero_path += drcts.down;
                break;
            default:
                break;
        }
        hero_path += ".png";
    }
    return hero_path;
}

void printHero(int i, int j, int direction = 0, int difference = 0, int dimension = 0) {
    if (mainHero.getOldX() != mainHero.getX() || mainHero.getOldY() != mainHero.getY()) {
        hero_Img.loadFromFile(getHeroImgPath(direction));
        hero_texture.loadFromImage(hero_Img);
        hero.setTexture(hero_texture);
        if (dimension == 1)
            hero.setPosition((float)(i * mltp - difference), (float)j * mltp);
        if (dimension == 2)
            hero.setPosition((float)(i * mltp + difference), (float)j * mltp);
        if (dimension == 3)
            hero.setPosition((float)i * mltp, (float)(j * mltp - difference));
        if (dimension == 4)
            hero.setPosition((float)i * mltp, (float)(j * mltp + difference));
        gameWindow.draw(hero);
        if (difference == 10) {
            mainHero.setX(i);
            mainHero.setY(j);
            mainHero.setOldX(i);
            mainHero.setOldY(j);
        }
    } else {
        hero_Img.loadFromFile(getHeroImgPath(direction));
        hero_texture.loadFromImage(hero_Img);
        hero.setTexture(hero_texture);
        hero.setPosition((float)i * mltp, (float)j * mltp);
        mainHero.setX(i);
        mainHero.setY(j);
        mainHero.setOldX(i);
        mainHero.setOldY(j);
        gameWindow.draw(hero);
    }
}

std::string chooseDoorDirection(int i, int j) {
    if (door1.i == i && door1.j == j) {
        if (!door1.isOpen) {
            if (maze[i - 1][j] == room)
                return "C:/maze/img/doors/left.png";
            if (maze[i + 1][j] == room)
                return "C:/maze/img/doors/right.png";
            if (maze[i][j + 1] == room)
                return "C:/maze/img/doors/up.png";
            if (maze[i][j - 1] == room)
                return "C:/maze/img/doors/down.png";
        } else {
            if (maze[i - 1][j] == room)
                return "C:/maze/img/doors/up.png";
            if (maze[i + 1][j] == room)
                return "C:/maze/img/doors/down.png";
            if (maze[i][j + 1] == room)
                return "C:/maze/img/doors/left.png";
            if (maze[i][j - 1] == room)
                return "C:/maze/img/doors/right.png";
        }
    } else if (door2.i == i && door2.j == j){
        if (!door2.isOpen) {
            if (maze[i - 1][j] == room)
                return "C:/maze/img/doors/left.png";
            if (maze[i + 1][j] == room)
                return "C:/maze/img/doors/right.png";
            if (maze[i][j + 1] == room)
                return "C:/maze/img/doors/up.png";
            if (maze[i][j - 1] == room)
                return "C:/maze/img/doors/down.png";
        } else {
            if (maze[i - 1][j] == room)
                return "C:/maze/img/doors/up.png";
            if (maze[i + 1][j] == room)
                return "C:/maze/img/doors/down.png";
            if (maze[i][j + 1] == room)
                return "C:/maze/img/doors/left.png";
            if (maze[i][j - 1] == room)
                return "C:/maze/img/doors/right.png";
        }
    }
}

void printMaze(int** &main_maze, int height, int width, int direction, bool explosion = false) {
    sf::Texture wallTexture;
    wallTexture.loadFromFile(wall_path);
    sf::Texture passTexture;
    passTexture.loadFromFile("C:/maze/img/utility/pass.png");
    sf::Image door_image;
    sf::Texture door_Texture;
    sf::Sprite mazeBlock;
    int difference = 0;
    int diff_dimension;
    if (mainHero.getOldX() != mainHero.getX() || mainHero.getOldY() != mainHero.getY()) {
        if (mainHero.getOldX() < mainHero.getX()) {
            difference = mainHero.getX() - mainHero.getOldX();
            diff_dimension = 1;
        } else if (mainHero.getOldX() > mainHero.getX()){
            difference = mainHero.getOldX() - mainHero.getX();
            diff_dimension = 2;
        } else if (mainHero.getOldY() < mainHero.getY()) {
            difference = mainHero.getY() - mainHero.getOldY();
            diff_dimension = 3;
        } else if (mainHero.getOldY() > mainHero.getY()){
            difference = mainHero.getOldY() - mainHero.getY();
            diff_dimension = 4;
        }
        difference = difference * 50 - 10;
    }
    do {
        int hero_i;
        int hero_j;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (main_maze[i][j] == silver_key || main_maze[i][j] == gold_key) {
                    mazeBlock.setTexture(passTexture);
                    mazeBlock.setPosition((float)i * mltp, (float)j * mltp);
                    gameWindow.draw(mazeBlock);
                    if (main_maze[i][j] == silver_key) {
                        door_image.loadFromFile("C:/maze/img/utility/key2.png");
                    } else {
                        door_image.loadFromFile("C:/maze/img/utility/key.png");
                    }
                    door_Texture.loadFromImage(door_image);
                    mazeBlock.setTexture(door_Texture);
                }
                if (main_maze[i][j] == room_door || main_maze[i][j] == end_door) {
                    mazeBlock.setTexture(passTexture);
                    mazeBlock.setPosition((float)i * mltp, (float)j * mltp);
                    gameWindow.draw(mazeBlock);
                    if (main_maze[i][j] == room_door)
                        door_image.loadFromFile(chooseDoorDirection(i,j));
                    else
                        door_image.loadFromFile("C:/maze/img/doors/end_door.png");
                    door_Texture.loadFromImage(door_image);
                    mazeBlock.setTexture(door_Texture);
                }
                if (main_maze[i][j] == pass || main_maze[i][j] == room) {
                    mazeBlock.setTexture(passTexture);
                }
                if (main_maze[i][j] == wall) {
                    mazeBlock.setTexture(wallTexture);
                }
                mazeBlock.setPosition((float)i * mltp, (float)j * mltp);
                gameWindow.draw(mazeBlock);
                if (main_maze[i][j] == hero_maze) {
                    hero_i = i;
                    hero_j = j;
                    mazeBlock.setTexture(passTexture);
                    mazeBlock.setPosition((float)i * mltp, (float)j * mltp);
                    gameWindow.draw(mazeBlock);
                }
            }
        }
        if (mainHero.getOldX() != mainHero.getX() || mainHero.getOldY() != mainHero.getY()) {
            printHero(hero_i, hero_j, direction,difference,diff_dimension);
        } else {
            printHero(hero_i, hero_j, direction);
        }
        sf::RenderTexture tex;
        tex.create(W * mltp, H * mltp);
        {
            sf::RectangleShape globalRect(sf::Vector2f{W * mltp, H * mltp});
            globalRect.setFillColor(sf::Color::Black);
            globalRect.setPosition(0, 0);
            sf::CircleShape circle(150);
            double x = mainHero.getX() * mltp - mltp * 2.5; double y = mainHero.getY() * mltp - mltp * 2.5;
            if (diff_dimension == 1) {
                x = hero_i * mltp - difference - mltp * 2.5;
                y = hero_j * mltp - mltp * 2.5;
            }
            if (diff_dimension == 2) {
                x = hero_i * mltp + difference - mltp * 2.5;
                y = hero_j * mltp - mltp * 2.5;
            }
            if (diff_dimension == 3) {
                x = hero_i * mltp - mltp * 2.5;
                y = hero_j * mltp - difference - mltp * 2.5;
            }
            if (diff_dimension == 4) {
                x = hero_i * mltp - mltp * 2.5;
                y = hero_j * mltp + difference - mltp * 2.5;
            }
            circle.setFillColor(sf::Color::Transparent);
            circle.setPosition((float)x,(float)y);
            tex.draw(globalRect, sf::BlendNone);
            tex.draw(circle, sf::BlendNone);
            tex.display();
        }
        sf::Sprite eye(tex.getTexture());
        gameWindow.draw(eye);
        if (!explosion) {
            printKeysData();
            gameWindow.display();
        }
        difference-= 10;
        sf::Time time = sf::milliseconds(23);
        sleep(time);
    } while (difference > 0);
}

void print2Eyes(int** main_maze, int height, int width, int direction, float visionX, float visionY) {
    sf::Texture wallTexture;
    wallTexture.loadFromFile(wall_path);
    sf::Texture passTexture;
    passTexture.loadFromFile("C:/maze/img/utility/pass.png");
    sf::Sprite mazeBlock;
    int hero_i;
    int hero_j;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (main_maze[i][j] == pass || main_maze[i][j] == room) {
                mazeBlock.setTexture(passTexture);
            }
            if (main_maze[i][j] == wall) {
                mazeBlock.setTexture(wallTexture);
            }
            mazeBlock.setPosition((float)i * mltp, (float)j * mltp);
            gameWindow.draw(mazeBlock);
            if (main_maze[i][j] == hero_maze) {
                hero_i = i;
                hero_j = j;
                mazeBlock.setTexture(passTexture);
                mazeBlock.setPosition((float)i * mltp, (float)j * mltp);
                gameWindow.draw(mazeBlock);
            }
        }
    }
    printHero(hero_i, hero_j, direction);
    sf::RenderTexture tex;
    tex.create(W * mltp, H * mltp);
    {
        sf::RectangleShape globalRect(sf::Vector2f{W * mltp, H * mltp});
        globalRect.setFillColor(sf::Color::Black);
        globalRect.setPosition(0, 0);
        sf::CircleShape circle(150);
        sf::CircleShape visionCircle(400);
        visionCircle.setFillColor(sf::Color::Transparent);
        visionCircle.setPosition(visionX-200*2,visionY-200*2);
        double x = (double)mainHero.getX() * mltp - mltp * 2.5; double y = (double)mainHero.getY() * mltp - mltp * 2.5;
        circle.setFillColor(sf::Color::Transparent);
        circle.setPosition((float)x,(float)y);
        tex.draw(globalRect, sf::BlendNone);
        tex.draw(circle, sf::BlendNone);
        tex.draw(visionCircle, sf::BlendNone);
        tex.display();
    }
    sf::Sprite eye(tex.getTexture());
    gameWindow.draw(eye);
    gameWindow.display();
}

void Game::print() {
    gameWindow.create(sf::VideoMode(W * mltp, H * mltp), "NIGHT STALKER !", sf::Style::Titlebar | sf::Style::Close);
    gameWindow.setFramerateLimit(60);
    gameWindow.setVerticalSyncEnabled(true);
    gameWindow.setPosition({20,20});
    mainMenu::putIcoInWindow(&gameWindow);
    srand(time(nullptr));
    maze = new int*[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        maze[i] = new int[WIDTH];
    }
    mazemake(maze, HEIGHT, WIDTH);
    printMaze(maze, HEIGHT, WIDTH,0);
    Game::game(maze, WIDTH);
}

void Game::prerun(int num) {
    mainHero.setCharNumber(num);
    wall_path = chooseWallImg();
    spellCounter = 0;
    door1.isOpen = false;
    door2.isOpen = false;
    silverFound = false;
    goldenFound = false;
    Game::print();
}

bool Game::isHover(sf::FloatRect sprite, sf::Vector2f mp){
    if(sprite.contains(mp)) {
        return true;
    } else {
        return false;
    }
}

bool checkWinCondition() {
    sf::Vector2f temp2 = {HEIGHT - 1, (float)(WIDTH)/2 - 3};
    sf::Vector2f temp3 = {1,3};
    sf::Rect<float> rect1 = {temp2, temp3};
    sf::Vector2f currPos = {static_cast<float>(mainHero.getX()),static_cast<float>(mainHero.getY())};
    if (Game::isHover(rect1,currPos)) {
        if (goldenFound) {
            return true;
        }
        return false;
    } else {
        return false;
    }
}

void printExitBtn(sf::RenderWindow *window, int exit = 0, sf::Sprite *sprite = &exit_spell) {
    sf::Image questionImg;
    if (exit == 0) {
        questionImg.loadFromFile("C:/maze/img/utility/close.png");
    } else {
        questionImg.loadFromFile("C:/maze/img/utility/about.png");
    }
    sf::Texture questionTexture;
    questionTexture.loadFromImage(questionImg);
    if (exit == 0) {
        exit_spell.setTexture(questionTexture);
        exit_spell.setScale(0.5,0.5);
        exit_spell.setPosition(370, 10);
    } else {
        sprite->setTexture(questionTexture);
        sprite->setScale(0.5,0.5);
        sprite->setPosition(343,10);
    }
    if (exit == 0) {
        window->draw(exit_spell);
    } else {
        window->draw(*sprite);
    }
}

void printSpellConfirmation(sf::RenderWindow *window, const std::string& text) {
    sf::Text exitAsk;
    exitAsk.setString(text);
    exitAsk.setFont(sameFont);
    exitAsk.setCharacterSize(45);
    exitAsk.setPosition(70, 45);
    window->draw(exitAsk);
}

void printYes(sf::RenderWindow *window) {
    yesLbl.setString("YES");
    yesLbl.setFont(sameFont);
    yesLbl.setCharacterSize(45);
    yesLbl.setPosition(180, 145);
    window->draw(yesLbl);
}

void printExplosion(int newX, int newY) {
    sf::Image gif_img;
    sf::Texture gif_texture;
    sf::Sprite gif_sprite;
    sf::Time time = sf::milliseconds(45);

    int i = 0; std::string path; std::string mask = ".png";
    while (i < 15) {
        path = "C:/maze/img/gif/";
        path += std::to_string(i);
        path+= mask;
        gif_img.loadFromFile(path);
        gif_texture.loadFromImage(gif_img);
        gif_sprite.setTexture(gif_texture);
        gif_sprite.setPosition((float)newX * mltp, (float)newY*mltp);
        printMaze(maze, HEIGHT, WIDTH, 0,true);
        gameWindow.draw(gif_sprite);
        gameWindow.display();
        sleep(time);
        i++;
    }
}

bool checkNextWall(int newX, int newY, int direction, bool forDoor = false) {
    if(!forDoor) {
        switch (direction) {
            case 0:
                return (newX + 1 > 0 && newX + 1 < HEIGHT &&
                        (maze[newX + 1][newY] == pass || maze[newX + 1][newY] == room));
            case 1:
                return (newX - 1 > 0 && newX - 1 < HEIGHT &&
                        (maze[newX - 1][newY] == pass || maze[newX - 1][newY] == room));
            case 2:
                return (newY - 1 > 0 && newY - 1 < WIDTH &&
                        (maze[newX][newY - 1] == pass || maze[newX][newY - 1] == room));
            case 3:
                return (newY + 1 > 0 && newY + 1 < HEIGHT &&
                        (maze[newX][newY + 1] == pass || maze[newX][newY + 1] == room));
            default:
                return false;
        }
    } else {
        switch (direction) {
            case 0:
                return (newX + 1 > 0 && newX + 1 < HEIGHT && maze[newX + 1][newY] == room);
            case 1:
                return (newX - 1 > 0 && newX - 1 < HEIGHT && maze[newX - 1][newY] == room);
            case 2:
                return (newY - 1 > 0 && newY - 1 < WIDTH && maze[newX][newY - 1] == room);
            case 3:
                return (newY + 1 > 0 && newY + 1 < HEIGHT && maze[newX][newY + 1] == room);
            default:
                return false;
        }
    }
}

void printBeatleSpell(int x, int y) {
    sf::Time visionTime = sf::milliseconds(3000);
    print2Eyes(maze, HEIGHT, WIDTH,0, (float)x,(float)y);
    sleep(visionTime);
    spellCounter = 1;
    spellStart = false;
}

void doBeatleSpell() {
    if (!spellStart) {
        spellStart = true;
    }
    sf::Event event{};
    while (spellCounter < 1) {
        if (gameWindow.waitEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    printBeatleSpell(sf::Mouse::getPosition(gameWindow).x,
                                     sf::Mouse::getPosition(gameWindow).y);
                }
            }
        }
    }
}

void openDoor(int** &main_maze, int doorI, int doorJ) {
    if (door1.i == doorI && door1.j == doorJ) {
        door1.isOpen = true;
    } else {
        door2.isOpen = true;
    }
    main_maze[doorI][doorJ] = pass;
}

sf::Vector2i findNearestDoor(int i, int j) {
    int n = 0;
    sf::Vector2i result;
    do{
        n++;
        for (int k=0; k<n; k++) {
            if (maze[i][j] == room_door) {
                result.x = i;
                result.y = j;
                return result;
            }
            i--;
        }
        for (int k=0; k<n; k++) {
            if (maze[i][j] == room_door) {
                result.x = i;
                result.y = j;
                return result;
            }
            j++;
        }
        n++;
        for (int k=0; k<n; k++) {
            if (maze[i][j] == room_door) {
                result.x = i;
                result.y = j;
                return result;
            }
            i++;
        }
        for (int k=0; k<n; k++) {
            if (maze[i][j] == room_door) {
                result.x = i;
                result.y = j;
                return result;
            }
            j--;
        }
    }
    while (true);
}

void doTankSpell(int** &main_maze) {
    if (!spellStart) {
        spellStart = true;
    }
    sf::Event event{};
    int direction = 0;
    while (spellCounter < 1) {
        int newX = mainHero.getX();
        int newY = mainHero.getY();
        do {
            if (gameWindow.waitEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Right) {
                        newX += 1;
                        direction = 0;
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        newX -= 1;
                        direction = 1;
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        newY -= 1;
                        direction = 2;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        newY += 1;
                        direction = 3;
                    }
                }
            }
            if ((newX > -1 && newY > -1) && ((main_maze[newX][newY] == wall || main_maze[newX][newY] == room_door) && checkNextWall(newX, newY, direction))) {
                printExplosion(newX, newY);
                gameWindow.display();
                main_maze[newX][newY] = pass;
                spellCounter++;
                spellStart = false;
            }
        } while (event.key.code != sf::Keyboard::Right && event.key.code != sf::Keyboard::Left && event.key.code != sf::Keyboard::Up
                 && event.key.code != sf::Keyboard::Down && (newX > -1 && newY > -1) && ((main_maze[newX][newY] == wall || main_maze[newX][newY] == room_door)
                 && checkNextWall(newX,newY, direction)));
    }
}

sf::Vector2i findFreePlace(sf::Vector2f mousePos, int** &main_maze) {
    int mouseI = (int)(mousePos.x)/mltp;
    int mouseJ = (int)(mousePos.y)/mltp;
    sf::Vector2i result(mainHero.getX(),mainHero.getY());
    if (maze[mouseI][mouseJ] == pass) {
        result.x = mouseI;
        result.y = mouseJ;
        return result;
    } else {
        int n = 0;
        int i = mouseI;
        int j = mouseJ;
        do{
            n++;
            for (int k=0; k<n; k++) {
                if (maze[i][j] == pass || maze[i][j] == room) {
                    result.x = i;
                    result.y = j;
                    return result;
                }
                i--;
            }
            for (int k=0; k<n; k++) {
                if (maze[i][j] == pass || maze[i][j] == room) {
                    result.x = i;
                    result.y = j;
                    return result;
                }
                j++;
            }
            n++;
            for (int k=0; k<n; k++) {
                if (maze[i][j] == pass || maze[i][j] == room) {
                    result.x = i;
                    result.y = j;
                    return result;
                }
                i++;
            }
            for (int k=0; k<n; k++) {
                if (maze[i][j] == pass || maze[i][j] == room) {
                    result.x = i;
                    result.y = j;
                    return result;
                }
                j--;
            }
        }
        while (true);
    }
}

void porting(float mouseX, float mouseY, int** &main_maze) {
    sf::Vector2f mousePos(mouseX, mouseY);
    double x = mainHero.getX() * mltp;
    double y = mainHero.getY() * mltp;
    sf::Vector2f temp2 = {(HEIGHT - 3)*50,  ((float)(WIDTH) / 2 - 6)*50};
    sf::Vector2f temp3 = {150, 300};
    sf::Rect<float> rect1 = {temp2, temp3};
    sf::Vector2f heroPos((float) x, (float) y);
    if (abs(heroPos.x - mousePos.x) < MAX_PORT_DISTANCE) {
        if (!Game::isHover(rect1, mousePos)) {
            if (abs(heroPos.y - mousePos.y) < MAX_PORT_DISTANCE) {
                sf::Vector2i tpCoords = findFreePlace(mousePos,main_maze);
                main_maze[mainHero.getX()][mainHero.getY()] = pass;
                mainHero.setX(tpCoords.x);
                mainHero.setY(tpCoords.y);
                mainHero.setOldX(tpCoords.x);
                mainHero.setOldY(tpCoords.y);
                main_maze[tpCoords.x][tpCoords.y] = hero_maze;
                if (main_maze[tpCoords.x-1][tpCoords.y-1] == room || main_maze[tpCoords.x-1][tpCoords.y] == room
                || main_maze[tpCoords.x][tpCoords.y-1] == room || main_maze[tpCoords.x+1][tpCoords.y-1] == room
                || main_maze[tpCoords.x-1][tpCoords.y+1] == room || main_maze[tpCoords.x+1][tpCoords.y+1] == room
                || main_maze[tpCoords.x+1][tpCoords.y] == room || main_maze[tpCoords.x][tpCoords.y+1] == room) {
                    sf::Vector2i doorPos = findNearestDoor(tpCoords.x, tpCoords.y);
                    openDoor(main_maze,doorPos.x, doorPos.y);
                }
                spellCounter = 1;
                spellStart = false;
            }
        }
    }
}

void doRestSpell(int** &main_maze) {
    if (!spellStart) {
        spellStart = true;
    }
    sf::Event event{};
    while (spellCounter < 1) {
        if (gameWindow.waitEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    porting((float)sf::Mouse::getPosition(gameWindow).x,
                            (float)sf::Mouse::getPosition(gameWindow).y,
                            main_maze);
                }
            }
        }
    }
}

void doSpecialSpell(int** &main_maze) {
    int hero_num = mainHero.getCharNumber();
    switch(hero_num) {
        case 7:
            doTankSpell(main_maze);
            break;
        case 8:
            doBeatleSpell();
            break;
        default:
            doRestSpell(main_maze);
            break;
    }
}

void printSpellConfirm(const std::string& text) {
    sf::RenderWindow spellWindow;
    spellWindow.create(sf::VideoMode(400,210), "Quick notification", sf::Style::None);
    mainMenu::printExitBgSprite(&spellWindow);
    printSpellConfirmation(&spellWindow, text);
    printExitBtn(&spellWindow);
    sf::Sprite about;
    printExitBtn(&spellWindow, 1, &about);
    printYes(&spellWindow);
    spellWindow.display();
    while (spellWindow.isOpen()) {
        sf::Event event{};
        while ( spellWindow.pollEvent(event) ) {
            if (event.type == sf::Event::MouseButtonPressed)   {
                if ( event.mouseButton.button == sf::Mouse::Left ) {
                    sf::Vector2f mp;
                    mp.x = (float)sf::Mouse::getPosition(spellWindow).x;
                    mp.y = (float)sf::Mouse::getPosition(spellWindow).y;
                    if ( Game::isHover(exit_spell.getGlobalBounds(), mp )) {
                        spellWindow.close();
                    }
                    if (Game::isHover(about.getGlobalBounds(), mp)) {
                        mainMenu::info();
                    }
                    if (Game::isHover(yesLbl.getGlobalBounds(), mp)){
                        spellWindow.close();
                        if (spellCounter == 0) {
                            if (!spellStart) {
                                spellStart = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool checkDoorState(int x, int y, door temp_door) {
    return maze[x][y] == room_door && x == temp_door.i && y == temp_door.j && silverFound;
}

void Game::game(int** &main_maze, int width) {
    int x = 0;
    int y = width/2 - 1;
    int direction = 0;
    sameFont.loadFromFile("C:/maze/font/font.ttf");
    while(gameWindow.isOpen()) {
        sf::Event event{};
        int newX = x;
        int newY = y;
        while (gameWindow.pollEvent(event)){
            sf::Vector2f mp;
            if(event.type == sf::Event::Closed) {
                gameWindow.close();
                mainMenu::start();
            }
            if(event.type == sf::Event::KeyPressed) {
                newX = mainHero.getX();
                newY = mainHero.getY();
                if(event.key.code == sf::Keyboard::Right) {
                    newX+= 1;
                    direction = 0;
                }
                if (event.key.code == sf::Keyboard::Left) {
                    newX-= 1;
                    direction = 1;
                }
                if(event.key.code == sf::Keyboard::Up) {
                    newY-= 1;
                    direction = 2;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    newY+= 1;
                    direction = 3;
                }
                if (event.key.code == sf::Keyboard::R) {
                    if (spellCounter == 0) {
                        printSpellConfirm("Click Yes to use\n your char spell");
                    } else {
                        printSpellConfirm("Your spell is \n already done");
                    }
                }
            }
        }
        if ((newX > -1 && newY > -1) && (newX < HEIGHT && newY < WIDTH) && main_maze[newX][newY] == end_door && !isWin) {
            main_maze[x][y] = pass;
            main_maze[newX][newY] = hero_maze;
            mainHero.setOldX(x);
            mainHero.setOldY(y);
            x = newX;
            y = newY;
            mainHero.setX(x);
            mainHero.setY(y);
            isWin = true;
            if (checkWinCondition()) {
                Game::win();
            }
        } else if ((newX > -1 && newY > -1) && (newX < HEIGHT && newY < WIDTH) && (main_maze[newX][newY] == pass || main_maze[newX][newY] == room ||
                checkDoorState(newX,newY,door1) || checkDoorState(newX,newY,door2))) {
            main_maze[x][y] = pass;
            main_maze[newX][newY] = hero_maze;
            mainHero.setOldX(x);
            mainHero.setOldY(y);
            x = newX;
            y = newY;
        }
        mainHero.setX(x);
        mainHero.setY(y);
        if (spellStart) {
            doSpecialSpell(main_maze);
            x = mainHero.getX();
            y = mainHero.getY();
        }
        if (!(silverFound && goldenFound))
            pickUpKey();
        printMaze(main_maze, HEIGHT, WIDTH,direction);
    }
}

void printWinBg(sf::RenderWindow *window) {
    sf::Image bg;
    bg.loadFromFile("C:/maze/img/utility/win.png");
    sf::Texture bgTexture;
    bgTexture.loadFromImage(bg);
    sf::Sprite bgSprite(bgTexture);
    window->draw(bgSprite);
}

void showOkBtn(sf::RenderWindow *window) {
    okText.setString("OK");
    okText.setFillColor(sf::Color::White);
    okText.setFont(sameFont);
    okText.setCharacterSize(85);
    okText.setPosition(320, 180);
    window->draw(okText);
}

void Game::win() {
    sf::RenderWindow winWindow;
    winWindow.create(sf::VideoMode(700,300), "You WIN!!!", sf::Style::None);
    printWinBg(&winWindow);
    showOkBtn(&winWindow);
    winWindow.display();
    sf::Time time = sf::milliseconds(1000);
    while (winWindow.isOpen()) {
        sf::Event event{};
        while (winWindow.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    winWindow.close();
                    gameWindow.close();
                    mainMenu::start();
                }
            }
        }
    }
}
