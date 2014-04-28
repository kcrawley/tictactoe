#include <iostream>
#include <game.h>
#include <player.h>

int Player::playerGamePiece(int input)
{
    char selectedChar, unselectedChar;

    switch (input)
    {
        case 120:
        case 88:
            selectedChar = 'X';
            unselectedChar = 'O';
            break;
        case 111:
        case 79:
            selectedChar = 'O';
            unselectedChar = 'X';
            break;
        default:
            return 0;
    }

    this->playerOne.playerChar = (this->playerOne.active) ? selectedChar : unselectedChar;
    this->playerTwo.playerChar = (this->playerTwo.active) ? selectedChar : unselectedChar;

    return 1;
}

void Player::switchActivePlayers()
{
    if (this->playerOne.active)
    {
        this->playerOne.active = false;
        this->playerTwo.active = true;
    }
    else
    {
        this->playerOne.active = true;
        this->playerTwo.active = false;
    }
}

int Player::setNextMove(int input)
{
    int row, col;
    switch (input)
    {
        case 49:
            row = 0;
            col = 0;
            break;
        case 50:
            row = 0;
            col = 1;
            break;
        case 51:
            row = 0;
            col = 2;
            break;
        case 52:
            row = 1;
            col = 0;
            break;
        case 53:
            row = 1;
            col = 1;
            break;
        case 54:
            row = 1;
            col = 2;
            break;
        case 55:
            row = 2;
            col = 0;
            break;
        case 56:
            row = 2;
            col = 1;
            break;
        case 57:
            row = 2;
            col = 2;
            break;
        default:
            return 0;
    }

    if (this->playerOne.active)
    {
        this->playerOne.nextMove[0] = row;
        this->playerOne.nextMove[1] = col;
    }
    else
    {
        this->playerTwo.nextMove[0] = row;
        this->playerTwo.nextMove[1] = col;
    }

    return 1;
}
