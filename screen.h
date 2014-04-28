#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <game.h>
#include <player.h>
#include <curses.h>

class Screen
{
public:
    Screen() { initscr(); }

    void gameStatus();
    void renderGameBoard(Game::GameBoard* gameBoard);
    void gamePrompt(int prompt, Player* player);
};

#endif // SCREEN_H_INCLUDED
