#pragma once

#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>

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

    //positin : availability
    std::map <char, int> m_position;




private:
    void m_ComputerMove(char);

    bool m_isGameOver();

public:
    /*Constructor:
    Creates an empty board and
    asks user for their symbol of choice */
    Tictactoe();

    /* Calls all the required functions to keep the game running */
    void StartGame();

    /* Display the board at current state */
    void GetBoard();

    /* Set User's choice of symbol; Circle or Cross  */
    void SetSymbol();

    /* Modify the state of the position; normal, userOccupied or computerOccupied */
    void SetUserPosition();
};
