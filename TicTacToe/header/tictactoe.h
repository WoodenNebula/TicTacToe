#ifndef tictactoe
#define tictactoe

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <limits>
#include <algorithm>

void ignoreBadInputLines();

class Tictactoe {
public:
    /* Option to toggle Computer's move delay on or off */
    bool computerMoveDelay;

public:
    Tictactoe();

    /* Constructor: 
    *** Can toggle Computer Move Delay from arguement*/
    Tictactoe(const bool computerMoveDelay);

    /*Destructor*/
    ~Tictactoe();

    static void StartGame();

private:

    //Symbols that will fill the position in board
    struct Symbols {
        //Default Symbol to fill the position with
        const std::string normal = " -- ";
        //User Symbol to fill the position with
        std::string user;
        //Symbol that the computer fills the position with
        std::string computer;
    };

    //Number of Players; 0 = EvE; 1 = PvE; 2 = PvP;
    enum NumPlayers {
        zeroPlayer = 0, onePlayer, twoPlayer
    };

    //Possible Errors regarding position of the Board while user passes their choice
    enum PossibleERRORS {
        noERROR = 0, posOutOfBound = 404, posOccupied = 405, badInput = 406
    };



/* Methods */
private:
    /* Proceed the game to continue */
    void m_ContinueGame();

    /* Prompts the user if they want Computer's move to be delayed or not */
    void m_PromptComputerMoveDelay();

    bool m_IsGameOver();

    /* Display the board at current state */
    void m_GetBoard();

    /* Set User's choice of symbol; Circle or Cross  */
    void m_SetSymbol();

    /// <summary>
    /// Modify the state of the position user provides normal, userOccupied or computerOccupied
    /// </summary>
    /// <returns>enum PossibleERRORS</returns>
    PossibleERRORS m_UserMove();

    /// <summary>
    /// Resolves the error from m_UserMove() if any 
    /// </summary>
    /// <return> true if reolution of error succeeds</return>
    bool m_ValidateUserMove();

    /* Prints "Thinking . . . " and Adds Delay of 1.5s*/
    void m_MoveDelay();

    /* Fills a random position with computerSymbol */
    void m_ComputerMove();

    /* Endscreen prompting for replay */
    void m_EndScreen();


/* Member variables */
private:
    Symbols m_symbols;

    //Board state
    std::vector<std::string> m_position;

    //Place Holder for random position eliminator
    std::vector<std::string> m_positionTracker;

    //User BufferPosition to change the symbol in the position on board
    uint32_t m_bufferPosition = 0;

    //Error Code holder
    PossibleERRORS posERROR;

    //Winner of the game
    std::string m_winner;
};

#endif // tictactoe