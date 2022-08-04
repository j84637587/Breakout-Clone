#ifndef BALL_H
#define BALL_H

#include "Main.h"

#pragma hdrstop

const int r = 5;

class Ball
{
private: // User declarations
public:  // User declarations
    int dx, dy;
    int invincible;
    TShape *ts;
    void __fastcall Timer1Timer(TObject *Sender);

    Ball();
    Ball(TForm1 *, int, int, int, int);
    ~Ball();
    int Ball::Collisiondetect(int, int, int);
    int Ball::Collisiondetect(int, int, int, int);
    void Ball::Frame();
};

Ball::Ball() {}

/**
 * @brief Construct a new Ball:: Ball object
 *
 * @param Form Main TForm
 * @param px position x
 * @param py position y
 * @param dx move x per frame
 * @param dy move y per frame
 */
Ball::Ball(TForm1 *Form, int px, int py, int dx = 0, int dy = -3)
{
    // move offset
    this->dx = dx;
    this->dy = dy;

    // graph
    ts = new TShape(Form);
    ts->Shape = stCircle;
    ts->Parent = Form;
    ts->Brush->Color = (TColor)random(0xffffff); // clRed
    ts->Top = py;
    ts->Left = px;
    ts->Height = ball_radious;
    ts->Width = ball_radious;
}

Ball::~Ball()
{
    delete ts;
}

/**
 * @brief What to do every frame
 *
 */
void Ball::Frame()
{
    if (ts->Left + dx > win_width - 50 || ts->Left + dx < ball_radious / 2)
        dx = -dx;
    if (ts->Top + dy > win_height || ts->Top + dy < ball_radious / 2)
        dy = -dy;
    ts->Left += dx;
    ts->Top += dy;
}

/**
 * @brief square collision detection (lazy to make it polymorphism ;) )
 *
 * @param a_px square position x
 * @param a_py square position y
 * @param a_w  square width
 * @return int Returning true if an object is colliding with another object
 */
int Ball::Collisiondetect(int a_px, int a_py, int a_w)
{
    return (a_px + a_w >= ts->Left &&          // r1 right edge past r2 left
            a_px <= ts->Left + ball_radious && // r1 left edge past r2 right
            a_py + a_w >= ts->Top &&           // r1 top edge past r2 bottom
            a_py <= ts->Top + ball_radious);
}

/**
 * @brief
 *
 * @param left
 * @param top
 * @param right
 * @param bottom
 * @return int Returning true if an object is colliding with another object
 */
int Ball::Collisiondetect(int left, int top, int right, int bottom)
{
    return (right >= ts->Left &&               // r1 right edge past r2 left
            left <= ts->Left + ball_radious && // r1 left edge past r2 right
            bottom >= ts->Top &&               // r1 top edge past r2 bottom
            top <= ts->Top + ball_radious);
}

#endif // BALL_H