#pragma once

#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <vector>

struct Availability {
    int normal = -1;
    int computer = 1;
    int user = 0;
};

struct Symbols {
    //Default Symbol to fill the position with
    std::string normal;
    //User Symbol to fill the position with
    std::string user;
    //Symbol that the computer fills the position with
    std::string computer;
};


class Tictactoe {
private:
    //Available States of a position
    Availability m_ava;

    //Symbols for filling the position with
    Symbols m_symbols;

    //position : availability
    std::map <char, int> m_position;

    //User BufferPosition to change the symbol
    char m_bufferPosition = 0;

    //Place Holder for random position eliminator for bot
    std::map<char, int> m_PositionSeeds{
        {'1', 0}, {'2', 0}, {'3', 0},
        {'4', 0}, {'5', 0}, {'6', 0},
        {'7', 0}, {'8', 0}, {'9', 0}};

    //Winner of the game
    int m_winner;


private:
    /* Returns true if three continuous positions are filled with same availability */    
    bool m_IsGameOver();

    /* Display the board at current state */
    void m_GetBoard();

    /* Set User's choice of symbol; Circle or Cross  */
    void m_SetSymbol();

    /* Modify the state of the position user provides;
    normal, userOccupied or computerOccupied */
    void m_SetUserPosition();

    /* Fills a random position with cumputerSymbol */
    void m_ComputerMove();

    /* Just calls functions until the game is over */
    void m_Continue();

    /* Endscreen prompting for replay */
    void m_EndScreen();

public:
    /*Constructor:
    Creates an empty board and
    asks user for their symbol of choice */
    Tictactoe();

    /*Destructor*/
    ~Tictactoe();

    /* Calls all the required functions to keep the game running */
    void StartGame();

};
