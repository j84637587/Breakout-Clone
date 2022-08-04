//---------------------------------------------------------------------------

#include <vcl.h>
#include "game.hpp"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Game *game;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner)
    : TForm(Owner)
{
        randomize();
        this->ClientHeight = win_height;
        this->ClientWidth = win_width;
        this->Top = 100;
        this->Left = 180;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
        delete game;
        game = new Game(Form1, Score, Endlb);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
        exit(0);
}
//---------------------------------------------------------------------------
