#include <iostream>
#include <stdlib.h>
#include <screen.h>
#include <curses.h>

void Screen::renderGameBoard(Game::GameBoard* gameBoard)
{
    move(3,5);
    printw("\t %c | %c | %c\n",gameBoard->board[0][0],gameBoard->board[0][1],gameBoard->board[0][2]);
    printw("\t---+---+---\n");
    printw("\t %c | %c | %c\n",gameBoard->board[1][0],gameBoard->board[1][1],gameBoard->board[1][2]);
    printw("\t---+---+---\n");
    printw("\t %c | %c | %c\n",gameBoard->board[2][0],gameBoard->board[2][1],gameBoard->board[2][2]);
    refresh();
}

void Screen::gamePrompt(int prompt, Player* player)
{
    std::string output;

    switch (prompt)
    {
        case 1:
            output = "Please select the number of players (1 or 2): ";
            break;
        case 2:
            output = (player->playerOne.active) ? "Player 1" : "Player 2";
            output += ", please choose your game piece (X or O): ";
            break;
        case 3:
            output = (player->playerOne.active) ? "Player 1" : "Player 2";
            output += ", please select where you want to make your move (1-9): ";
            break;
        case 4:
            output = "Please wait while the computer makes their move...";
            break;
        case 8:
            output = "The game is a draw. Try again? (Y or N): ";
            break;
        case 9:
            if (player->playerOne.playerChar == player->winner.playerChar) {
                output = "You won! Play again? (Y or N): ";
            } else {
                output = "Player 2 defeated you. Try again? (Y or N): ";
            }
            break;
        default:
            output = "An unknown error has occurred";
    }

    if (prompt) {
        move(10,0);
        clrtobot();
        printw("%s", output.c_str());
        refresh();
    }
}

/** EOF: screen.cpp @ author: kcmastrpc@gmail.com **/
