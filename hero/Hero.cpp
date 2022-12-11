//---------------------------------------------------------------------------
#include "Hero.h"
//---------------------------------------------------------------------------
Hero::Hero(int x, int y, int oldX, int oldY, int number)
{
    this->x = x;
    this->y = y;
    this->oldX = oldX;
    this->oldY = oldY;
    this->char_number = number;
}

int Hero::getX()
{
    return this->x;
}
int Hero::getY()
{
    return this->y;
}
int Hero::getCharNumber()
{
    return this->char_number;
}
void Hero::setX(int x)
{
    this->x = x;
}
void Hero::setY(int y)
{
    this->y = y;
}
void Hero::setCharNumber(int number)
{
    this->char_number = number;
}
int Hero::getOldX()
{
    return this->oldX;
}
int Hero::getOldY()
{
    return this->oldY;
}
void Hero::setOldX(int x)
{
    this->oldX = x;
}
void Hero::setOldY(int y)
{
    this->oldY = y;
}
