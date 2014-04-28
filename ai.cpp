#include <stdlib.h>
#include <algorithm>
#include <ai.h>
#include <game.h>

/**
 * Plays a winning move, has a ~93% success chance.
 */
bool AI::attemptWinningMove(Game* game, Game::GameBoard* gameBoard)
{
    for (int i=0; i<3; ++i) // outer loop
    {
        for (int j=0; j<3; ++j) // inner loop
        {
            if (gameBoard->board[i][j] != 'X' && gameBoard->board[i][j] != 'O')
            {
                char tempPlaceholder = gameBoard->board[i][j];
                gameBoard->board[i][j] = aiInstance.aiChar;
                if (game->isWinning(false) && (rand() % 100 < 93))
                {
                    return true;
                }
                else
                {
                    gameBoard->board[i][j] = tempPlaceholder;
                }
            }
        }
    }

    return false;
}

/**
 * Attempts to block the opposing player from winning. Has a ~73% success rate.
 */
bool AI::attemptBlockingMove(Game* game, Game::GameBoard* gameBoard)
{
    for (int i=0; i<3; ++i)
    {
        for (int j=0; j<3; ++j)
        {
            if (gameBoard->board[i][j] != 'X' && gameBoard->board[i][j] != 'O')
            {
                char tempPlaceholder = gameBoard->board[i][j];
                gameBoard->board[i][j] = (aiInstance.aiChar == 'X') ? 'O' : 'X';
                if (game->isWinning(false) && (rand() % 100 < 73))
                {
                    gameBoard->board[i][j] = aiInstance.aiChar;
                    return true;
                }
                else
                {
                    gameBoard->board[i][j] = tempPlaceholder;
                }
            }
        }
    }

    return false;
}

bool AI::attemptStandardMove(Game::GameBoard* gameBoard)
{
    bool randPos = true;

    // attempts to play the golden position (center board), 89% chance success
    if (gameBoard->board[1][1] != 'X' && gameBoard->board[1][1] != 'O' && (rand() % 100 < 89))
    {
        gameBoard->board[1][1] = aiInstance.aiChar;
        return true;
    }
    else
    {
        while (randPos)
        {
            int row = rand() % 3;
            int col = rand() % 3;

            if (gameBoard->board[row][col] != 'X' && gameBoard->board[row][col] != 'O')
            {
                gameBoard->board[row][col] = aiInstance.aiChar;
                return true;
            }
        }
    }

    return false;
}

/**
 * Determines if final outcome is a draw (there are no winning positions for either players)
 *
 * author note: this is messy, I need to find a better way to do this...
 */
bool AI::attemptGameDraw(Game *game, Game::GameBoard* gameBoard)
{
    bool draw = true;
    char board[3][3];
    char pOneBoard[3][3];
    char pTwoBoard[3][3];

    // perform the initial copy - this is to restore the board
    for (int i=0; i<3; ++i)
    {
        for (int j=0; j<3; ++j)
        {
            board[i][j] = gameBoard->board[i][j];
        }
    }

    std::copy(&board[0][0], &board[0][0]+9, &pOneBoard[0][0]);
    std::copy(&board[0][0], &board[0][0]+9, &pTwoBoard[0][0]);

    // populate both temporary boards with each players characters
    for (int i=0; i<3; ++i)
    {
        for (int j=0; j<3; ++j)
        {
            if (gameBoard->board[i][j] != 'X' && gameBoard->board[i][j] != 'O')
            {
                pOneBoard[i][j] = aiInstance.aiChar;
                pTwoBoard[i][j] = aiInstance.oppChar;
            }
        }
    }

    // send each board back and check for a winner, if neither board can result in a win, we have a draw
    for (int k=0; (k<2 && draw == true); ++k)
    {
        // perform the initial copy - this is to restore the board
        for (int i=0; i<3; ++i)
        {
            for (int j=0; j<3; ++j)
            {
                gameBoard->board[i][j] = (k == 0) ? pOneBoard[i][j] : pTwoBoard[i][j];
            }
        }

        draw = game->isWinning(false);
    }

    // restore the board
    for (int i=0; i<3; ++i)
    {
        for (int j=0; j<3; ++j)
        {
            gameBoard->board[i][j] = board[i][j];
        }
    }

    return draw; // draw condition
}
