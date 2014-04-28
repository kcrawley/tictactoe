#include <iostream>
#include <stdlib.h>
#include <game.h>
#include <ai.h>
#include <player.h>
#include <screen.h>
#include <curses.h>
#include <time.h>

void Game::run()
{
    this->initialize();
    this->executionLoop();
}

void Game::initialize()
{
    srand(time(NULL)); // sets up random seed
    this->initGameBoard();
}

void Game::initGameBoard()
{
    int num = 0;
    char map[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            gameBoard.board[i][j] = map[num++];
        }
    };
}

void Game::executionLoop()
{
    Player player;
    GameState state;
    Screen screen;

    while (state.controller < 10)
    {
        // checks to see if theres a winner
        if (isWinning(true))
        {
            // passing stuff between objects is bad form, but i'm tired and want to get this done
            player.winner.playerChar = gameBoard.winner;
            state.renderer = true;
            state.controller = 9;
        }

        // sends game board to the screen
        if (state.renderer) {
            screen.renderGameBoard(&gameBoard);
            state.renderer = false;
        }

        // sets up render events based on current game state
        this->determineUserPrompt(&state);

        // sends prompt query event to the screen
        screen.gamePrompt(state.renderObject, &player);

        if (state.controller != 4) // 4 is AI, we don't need user input there
        {
            this->handleUserInput(getch(), &state, &player); // handles user input
        }
        else
        {
            this->executeAI(&state, &player);
        }

    }
}

void Game::handleUserInput(int input, GameState* state, Player* player)
{
    if (state->controller == 1) // executes new game handler
    {
        this->newGame(&input, state, player);
        return;
    }

    if (state->controller == 2)
    {
        if (player->playerGamePiece(input)) { // executes player choose game piece handler
            state->controller = 3;
        };
        return;
    }

    if (state->controller == 3)
    {
        if (player->setNextMove(input) && this->storeAndValidateNextMove(state, player)) // executes choose a move
        {
            this->placeNextMove(state);
            player->switchActivePlayers();

            state->renderer = true;
            state->controller = 4;
        }
    }

    if (state->controller == 8 || state->controller == 9) // game over or draw condition
    {
        if (input == 89 || input == 121)
        {
            this->initGameBoard(); // resets game board
            state->renderer = true;
            state->controller = 0;
        }
        else
        {
            state->controller = 10; // good bye
        }
    }

    return;
}

void Game::determineUserPrompt(GameState *state)
{
    if (state->controller == 0) // new game, prompt user to select game mode
    {
        state->controller = 1;
        state->renderObject = 1;
    }

    if (state->controller == 2) // get user game pieces
    {
        state->renderObject = 2;
    }

    if (state->controller == 3) // get users next move
    {
        state->renderObject = 3;
    }

    if (state->controller == 4) // the computer is thinking...
    {
        state->renderObject = 4;
    }

    if (state->controller == 8) // draw
    {
        state->renderObject = 8;
    }

    if (state->controller == 9) // game is over, play again?
    {
        state->renderObject = 9;
    }
}

/**
 * NEW GAME
 * Determines 1P or 2P game, sets up the players, and determine who makes the first move.
 */
void Game::newGame(int* input, GameState* state, Player* player)
{
    // resets players
    player->playerOne.active = false;
    player->playerTwo.active = false;

    switch (*input) // validates input and sets up our players
    {
        case 48:
            state->gameType = 0; // NPC vs NPC (todo)
            break;
        case 49:
            state->gameType = 1; // P1 vs NPC
            break;
        case 50:
            state->gameType = 2; // P1 vs P2 (todo)
            break;
        default:
            return;
    }

    state->activePlayer = 1 + rand() % 2; // roll who gets first play

    if (state->gameType == 0) { // 0 player game (todo)

    }
    else if (state->gameType == 1) // 1 player game
    {
        player->playerOne.playerType = 0; // sets playerOne to live
        player->playerTwo.playerType = 1; // sets playerTwo to NPC

        if (state->activePlayer == 1)
        { // player 1 won the first play roll
            player->playerOne.active = true;
            state->controller = 2; // interactively get game piece
        } else { // player 2 (computer) won the first play roll
            // since computer won the roll, we set up the players
            player->playerTwo.active = true;
            player->playerTwo.playerChar = (rand() % 100 > 50) ? 'X' : 'O';
            player->playerOne.playerChar = (player->playerTwo.playerChar == 'X') ? 'O' : 'X';
            state->controller = 4; // computers move
        }
    }
    else // 2 player game (todo)
    {

    }
}

int Game::storeAndValidateNextMove(GameState* state, Player* player)
{
    if (player->playerOne.active)
    {
        state->nextMoveChar = player->playerOne.playerChar;
        state->nextMovePointer[0] = player->playerOne.nextMove[0];
        state->nextMovePointer[1] = player->playerOne.nextMove[1];
    }
    else
    {
        state->nextMoveChar = player->playerTwo.playerChar;
        state->nextMovePointer[0] = player->playerTwo.nextMove[0];
        state->nextMovePointer[1] = player->playerTwo.nextMove[1];
    }

    char selectedSlot = this->gameBoard.board[state->nextMovePointer[0]][state->nextMovePointer[1]];

    if (selectedSlot == 'X' || selectedSlot == 'O') {
        return 0;
    }

    return 1;
}

bool Game::isWinning(bool setGameBoardWinner)
{
    for (int i=0; i < 8; ++i)
    {
        if (gameBoard.board[winPos[i][0][0]][winPos[i][0][1]] == gameBoard.board[winPos[i][1][0]][winPos[i][1][1]] &&
            gameBoard.board[winPos[i][0][0]][winPos[i][0][1]] == gameBoard.board[winPos[i][2][0]][winPos[i][2][1]])
            {
                if (setGameBoardWinner)
                {
                    gameBoard.winner = gameBoard.board[winPos[i][0][0]][winPos[i][0][1]];
                }
                return true;
            }
    }

    return false;
}

void Game::placeNextMove(GameState *state)
{
    gameBoard.board[state->nextMovePointer[0]][state->nextMovePointer[1]] = state->nextMoveChar;
}

void Game::executeAI(GameState* state, Player* player)
{
    AI ai;
    ai.setAiChar(player->playerTwo.playerChar);
    ai.setOpposingChar(player->playerOne.playerChar);
    if (ai.attemptGameDraw(this, &gameBoard) == false)
    {
        // draw detected
        state->controller = 8;
    }
    else if (ai.attemptWinningMove(this, &gameBoard))
    {
        // ai seems to have won, this game is over.
    }
    else if (ai.attemptBlockingMove(this, &gameBoard))
    {
        state->renderer = true; // set the board to refresh
        state->controller = 3;
    }
    else if (ai.attemptStandardMove(&gameBoard))
    {
        state->renderer = true; // set the board to refresh
        state->controller = 3;
    }

    player->switchActivePlayers();
}


