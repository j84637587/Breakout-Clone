#ifndef BRICK_H
#define BRICK_H

#include "Main.h"
#pragma hdrstop

// brick colors, index represent durability
TColor colors[] = {0x000000, 0x581845, 0xFFC300, 0xFF5733, 0xC70039, 0x900C3F, 0x581845};

class Brick
{
public: // User declarations
    // __fastcall TForm1(TComponent *Owner);
    int lv, score;
    TShape *ts;
    Brick();
    Brick(TForm1 *, int, int, int);
    void Brick::Damage();
    ~Brick();
};

Brick::Brick() {}

/**
 * @brief Construct a new Brick:: Brick object
 *
 * @param Form Main TForm
 * @param dx position x
 * @param dy position y
 * @param lv level of the brick(meanwhile health of the brick)
 */
Brick::Brick(TForm1 *Form, int dx = 0, int dy = 0, int lv = 0)
{
    ts = new TShape(Form);
    ts->Parent = Form;
    ts->Shape = stRoundSquare;
    ts->Brush->Color = (TColor)colors[lv]; // clRed
    ts->Height = brick_width;
    ts->Width = brick_width;
    ts->Left = dx;
    ts->Top = dy;
    this->lv = lv;
    this->score = lv;
}

/**
 * @brief brick damaged
 *
 */
void Brick::Damage()
{
    if (lv == 0 || lv == INT_MAX)
        return;
    ts->Brush->Color = (TColor)colors[--lv]; // clRed
}

Brick::~Brick()
{
    delete ts;
}

#endif // BRICK_H