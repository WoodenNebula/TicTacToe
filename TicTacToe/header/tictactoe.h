#pragma once

#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <thread>
#include <limits>


class Tictactoe {
public:
    /* Option to toggle Computer's move delay on or off */
    bool computerMoveDelay;

public:
    /* Constructor: */
    Tictactoe();

    /* Constructor: 
    *** Can toggle Computer Move Delay from arguement*/
    Tictactoe(const bool computerMoveDelay);

    /*Destructor*/
    ~Tictactoe();

    /* Calls all the required functions to keep the game running */
    void StartGame();


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

    //Possible States of a position
    enum PositionState {
        A_Normal = -1, A_User = 0, A_Computer = 1
    };

    //Possible Errors regarding position of the Board while user passes their choice
    enum PositionERROR {
        noERROR = 0, posOutofBound = 404, posOccupied = 405, badInput = 406
    };

    //Number of Players; 0 = EvE; 1 = PvE; 2 = PvP;
    enum NumPlayers {
        zeroPlayer = 0, onePlayer, twoPlayer
    };


/* Member variables */
private:

    //Symbols for filling the position with
    Symbols m_symbols;

    //position : availability
    std::map <int, PositionState> m_position;

    //User BufferPosition to change the symbol in the position on board
    uint32_t m_bufferPosition = 0;

    //Place Holder for random position eliminator
    std::map<int, const bool> m_positionTracker = { { 1, false}, { 2, false}, { 3, false},
                                             { 4, false}, { 5, false}, { 6, false},
                                             { 7, false}, { 8, false}, { 9, false} };

    //Iterator to the last position in Position Tracker of  that will be used to 
    //retrieve the maxPosition available at any given time for Random Number Generator
    std::map<int, const bool>::iterator m_lastPair;

    //Error Code holder
    PositionERROR posERROR;

    //Winner of the game
    PositionState m_winner;

/* Methods */
private:
    /* Prompts the user if they want Computer's move to be delayed or not */
    void m_promptComputerMoveDelay();

    /* Returns true if three continuous positions are filled with same availability */    
    bool m_IsGameOver();

    /* Display the board at current state */
    void m_GetBoard();

    /* Set User's choice of symbol; Circle or Cross  */
    void m_SetSymbol();

    /* Modify the state of the position user provides;
    normal, userOccupied or computerOccupied */
    PositionERROR m_SetUserPosition();

    /* Prints "Thinking . . . " and Adds Delay of 1.5s*/
    void m_MoveDelay();

    /* Fills a random position with computerSymbol */
    void m_ComputerMove();

    /* Endscreen prompting for replay */
    void m_EndScreen();

};
