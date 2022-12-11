#ifndef MAIN_HERO_H
#define MAIN_HERO_H
class Hero
{
private:
    int x;
    int y;
    int char_number;
    int oldX;
    int oldY;
public:
    Hero(int x, int y, int oldX, int oldY, int number);
    int getX();
    int getY();
    int getCharNumber();
    void setCharNumber(int number);
    void setX(int x);
    void setY(int y);
    void setOldX(int x);
    void setOldY(int y);
    int getOldX();
    int getOldY();
};
#endif //MAIN_HERO_H
