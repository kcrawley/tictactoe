#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include <game.h>

class AI
{
private:
    struct aiState
    {
        char aiChar;
        char oppChar;
    };
public:
    aiState aiInstance;

    void setAiChar(char c) { aiInstance.aiChar = c; }
    void setOpposingChar(char c) { aiInstance.oppChar = c; }
    bool attemptWinningMove(Game* game, Game::GameBoard* gameBoard);
    bool attemptBlockingMove(Game* game, Game::GameBoard* gameBoard);
    bool attemptStandardMove(Game::GameBoard* gameBoard);
    bool attemptGameDraw(Game* game, Game::GameBoard* gameBoard);
};

#endif // AI_H_INCLUDED
