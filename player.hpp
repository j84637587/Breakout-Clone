#ifndef PLAYER_H
#define PLAYER_H

#include "Main.h"
#pragma hdrstop

class Player
{
private: // User declarations
public:  // User declarations
    int min_x, max_x;
    TShape *ts;
    Player();
    Player(TForm1 *, int, int, int, int);
    ~Player();
    void Player::Frame(bool);
};

Player::Player() {}

/**
 * @brief Construct a new Player:: Player object
 *
 * @param Form Main TForm
 * @param px position x
 * @param py position y
 * @param min_x minimum x can reach
 * @param max_x maximum x can reach
 */
Player::Player(TForm1 *Form, int px, int py, int min_x, int max_x)
{
    this->min_x = min_x;
    this->max_x = max_x;
    ts = new TShape(Form);
    ts->Parent = Form;
    ts->Brush->Color = (TColor)random(0xffffff); // clRed
    ts->Height = player_height;
    ts->Width = player_width;
    ts->Top = py;
    ts->Left = px;
}

Player::~Player()
{
    delete ts;
}

/**
 * @brief What to do every frame
 *
 * @param isLeft
 */
void Player::Frame(bool isLeft)
{
    if (!isLeft && ts->Left + ts->Width + 5 <= max_x)
        ts->Left += 5;
    else if (isLeft && ts->Left - 5 >= min_x)
        ts->Left -= 5;
}

#endif // PLAYER_H