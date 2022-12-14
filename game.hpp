#ifndef GAME_H
#define GAME_H

#include <vcl.h>
#include "ball.hpp"
#include "player.hpp"
#include "brick.hpp"
#include <vector>
#include <Windows.h>
#include <Winuser.h>
#pragma hdrstop

// enum to represent game state
enum State
{
    INGAME,
    GAME_PASS,
    GAME_FAIL,
};

class Game
{
private:                       // User declarations
    int gameState;             // current game state
    std::vector<Ball *> balls; // a vector to store all balls
    int ball_count;
    std::vector<Brick *> bricks; // a vector to store all bricks
    int brick_count;             // current
    int score;                   // score
    Player *player;              // a player object
    Player *player2;             // a player object
    TTimer *engine;              // frame controller(logic at the same time)
    TLabel *Scorelb, *Endlb;     // score label, game ended text label
    TForm1 *Form;
    void __fastcall Timer1Timer(TObject *Sender);

public: // User declarations
    Game();
    Game(TForm1 *, TLabel *, TLabel *);
    void Game::ClearScreen();
    void Game::Logic();
    ~Game();
};

Game::Game() {}

/**
 * @brief Construct a new Game:: Game object
 *
 * @param Form Main TForm
 * @param Scorelb Score label
 * @param Endlb Game end lable
 */
Game::Game(TForm1 *Form, TLabel *Scorelb, TLabel *Endlb)
{
    Brick *c;
    Ball *b;
    ball_count = score = brick_count = 0; // as the word meaning
    this->Scorelb = Scorelb;              // score displayer
    this->Endlb = Endlb;                  // emding lable
    this->Endlb->Caption = "";            // text to show when game ended
    this->Form = Form;                    // main TForm
    gameState = INGAME;                   // game state

    int inv_brick_left = 3; // more than 3 would cause dead logic if no dead check
    int rand;
    // init bricks
    for (int y = brick_vertical_up_offset; y < win_height - brick_vertical_down_offset; y += brick_gape)
    {
        for (int x = brick_horizontal_offset; x < win_width - brick_horizontal_offset - brick_width; x += brick_gape)
        {
            rand = random(11) == 10 && inv_brick_left > 0;
            c = new Brick(Form, x, y, rand > 0 ? INT_MAX : (random(6) + 1)); // 6
            inv_brick_left -= rand;
            bricks.push_back(c);
            if (!rand)
                brick_count++;
        }
    }

    // init player
    player = new Player(Form, win_width / 2 - player_width / 2, win_height - 10, 0, win_width - player_width / 2);
    player2 = NULL;

    // init first ball
    b = new Ball(Form, win_width / 2 - ball_radious / 2, win_height - ball_radious - player_width, 2, -2);
    balls.push_back(b);
    ball_count++;

    // MainLoop
    engine = new TTimer(Form);
    engine->Interval = hz; // 60fps
    engine->OnTimer = Game::Timer1Timer;
}

Game::~Game()
{
    int tmp = balls.size();
    for (int i = 0; i < tmp; i++)
        if (balls[i] != NULL)
            delete balls[i];
    tmp = bricks.size();
    for (int i = 0; i < tmp; i++)
        if (bricks[i] != NULL)
            delete bricks[i];
    delete player;
    if (player2 != NULL)
        delete player2;
    delete engine;
}

/**
 * @brief hide all bricks, balls
 *
 */
void Game::ClearScreen()
{
    int tmp = balls.size();
    for (int i = 0; i < tmp; i++)
        balls[i]->ts->Visible = false;

    tmp = bricks.size();
    for (int i = 0; i < tmp; i++)
        bricks[i]->ts->Visible = false;
}

/**
 * @brief Game frame controller
 *
 * @param Sender doesn't matter
 */
void __fastcall Game::Timer1Timer(TObject *Sender)
{
    if (gameState == GAME_PASS)
    {
        Game::ClearScreen();
        Endlb->Caption = "Good job!!";
        return;
    }
    else if (gameState == GAME_FAIL)
    {
        Game::ClearScreen();
        Endlb->Caption = "Game Over!!";
        return;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        player->Frame(true);
        if (player2 != NULL)
            player2->Frame(false);
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        player->Frame(false);
        if (player2 != NULL)
            player2->Frame(true);
    }
    Game::Logic();
}

/**
 * @brief Game logic controller
 *
 */
void Game::Logic()
{
    int ball_size = balls.size();
    int brick_size = bricks.size();
    int tmp = 0;
    for (int i = 0; i < ball_size; ++i)
    {
        // continue if balls out of bounds
        if (!balls[i]->ts->Visible)
            continue;
        if (balls[i]->Collisiondetect(player->ts->Left, player->ts->Top, player->ts->Left + player_width, player->ts->Top + player_width))
            // if player collision with the ball
            balls[i]->dy = -(balls[i]->dy);
        else if (player2 != NULL && balls[i]->Collisiondetect(player2->ts->Left, player2->ts->Top, player2->ts->Left + player_width, player2->ts->Top + player_width))
            // prevent multiple detect cause ball do nothing with collision
            // if player2 collision with the ball
            balls[i]->dy = -(balls[i]->dy);
        else // else checl brick collision
        {
            // loop over valid bricks
            for (int j = 0; j < brick_size; ++j)
            {
                if (!bricks[j]->ts->Visible)
                    continue;
                if (balls[i]->Collisiondetect(bricks[j]->ts->Left, bricks[j]->ts->Top, brick_width))
                {
                    // if ball collision with the brick
                    bricks[j]->Damage();
                    if (balls[i]->ts->Left <= bricks[j]->ts->Left || balls[i]->ts->Left >= bricks[j]->ts->Left + brick_width)
                        balls[i]->dx *= -1;
                    if (balls[i]->ts->Top <= bricks[j]->ts->Top || balls[i]->ts->Top >= bricks[j]->ts->Top + brick_width)
                        balls[i]->dy *= -1;
                }
                // remove brick which is hp 0
                if (bricks[j]->lv == 0)
                {
                    if (random(11) == 10 && player2 == NULL)
                        // add a player
                        player2 = new Player(Form, win_width - player->ts->Left, player->ts->Top, player->min_x, player->max_x);
                    if (random(6) == 5 || 1)
                    {
                        // add a ball
                        Ball *nBall = new Ball(Form, balls[i]->ts->Left, balls[i]->ts->Top, 2, -2);
                        ball_count++;
                        balls.push_back(nBall);
                    }
                    // update score
                    score += bricks[j]->score;
                    // remove bricks
                    bricks[j]->ts->Visible = false;
                    brick_count--;
                    break;
                }
            }
        }
        balls[i]->Frame();
        // ??????????????????
        if (balls[i]->ts->Top + ball_radious >= win_height)
        {
            balls[i]->ts->Visible = false;
            balls[i]->dx = balls[i]->dy = 0;
            ball_count--;
        }
    }
    Scorelb->Caption = IntToStr(score);

    if (ball_count <= 0)
        // ????????????GameOver
        gameState = GAME_FAIL;
    else if (brick_count <= 0)
        // ????????????GamePass
        gameState = GAME_PASS;
}

#endif // GAME_H