#pragma once

#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <vector>
#include <thread>

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
    //Number of Players; 0 = EvE; 1 = PvE; 2 = PvP;
    uint32_t m_numPlayers;

    //Available States of a position
    Availability m_availability;

    //Symbols for filling the position with
    Symbols m_symbols;

    //position : availability
    std::map <int, int> m_position;

    //User BufferPosition to change the symbol in the position on board
    int m_bufferPosition = 0;

    //Place Holder for random position eliminator
    std::map<int, int> m_PositionTracker = { { 1, 0 }, { 2, 0 }, { 3, 0 },
                                             { 4, 0 }, { 5, 0 }, { 6, 0 },
                                             { 7, 0 }, { 8, 0 }, { 9, 0 } };

    //Pointer of the last position that is used to 
    //retrieve the maxPosition available at any given time for Random Number Generator
    std::map<int, int>::iterator m_lastPair;

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

    /* Prints "Thinking . . . " and Adds Delay of 1.5s*/
    void m_MoveDelay();

    /* Fills a random position with computerSymbol */
    void m_ComputerMove();

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
