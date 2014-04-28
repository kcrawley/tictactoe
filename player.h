#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <game.h>

class Player
{
private:
    struct PlayerState
    {
        bool active = false;
        int playerType;
        int nextMove[2] = { 0, 0 };
        char playerChar;
    };
    struct winningPlayer
    {
        char playerChar;
    };
public:
    PlayerState playerOne;
    PlayerState playerTwo;
    winningPlayer winner;

    int playerGamePiece(int input);
    int setNextMove(int input);
    void switchActivePlayers();
};

#endif // PLAYER_H_INCLUDED
