#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <player.h>

class Game
{
private:
    struct GameState
    {
        int controller = 0;
        int nextMovePointer[2];
        char nextMoveChar;
        int activePlayer = 0;
        int winState = 0;
        int gameType = 0;
        bool renderer = true;
        int renderObject = 0;
    };
public:
    int winPos[8][3][2] =
    // horiz wins
    { { {0,0},{0,1},{0,2} },
      { {1,0},{1,1},{1,2} },
      { {2,0},{2,1},{2,2} },
      // vert wins
      { {0,0},{1,0},{2,0} },
      { {0,1},{1,1},{2,1} },
      { {0,2},{1,2},{2,2} },
      // diag wins
      { {0,0},{1,1},{2,2} },
      { {0,2},{1,1},{2,0} }
    };
    struct GameBoard
    {
        char board[3][3];
        char winner;
    };

    GameBoard gameBoard;

    void run();
    void initialize();
    void initGameBoard();
    void executionLoop();
    void handleUserInput(int input, GameState* state, Player* player);
    void determineUserPrompt(GameState* state);
    void newGame(int* input, GameState* state, Player* player);
    int storeAndValidateNextMove(GameState* state, Player* player);
    bool isWinning(bool setGameBoardWinner);
    void placeNextMove(GameState *state);
    void executeAI(GameState* state, Player* player);

    Game() { }
};

#endif // GAME_H_INCLUDED
