#include "Tictactoe.h"

#include "Tictactoe.h"


Tictactoe::Tictactoe()
    :m_position(
        { {'1', m_ava.normal},{'2', m_ava.normal},{'3', m_ava.normal},
            {'4', m_ava.normal},{'5', m_ava.normal},{'6', m_ava.normal},
            {'7', m_ava.normal},{'8', m_ava.normal},{'9', m_ava.normal} })
{
    std::cout << "Starting Game" << std::endl;
    m_SetSymbol();
    //setting the seed for random num generator
    srand((unsigned)time(NULL));
}

Tictactoe::~Tictactoe() = default;

void Tictactoe::m_SetSymbol()
{
    bool isCross;
    system("cls");
    std::cout << "Wanna play Circle(0) or Cross(1)?" << std::endl;
    std::cin >> isCross;

    m_symbols.normal = " -- ";
    if (isCross) {
        m_symbols.user = " X ";
        m_symbols.computer = " O ";
    }
    else if (!isCross) {
        m_symbols.user = " O ";
        m_symbols.computer = " X ";
    }
    std::cout << "\n Set user symbol to \"" << m_symbols.user << "\"" << std::endl;
    system("pause");
}

void Tictactoe::StartGame()
{
    while (!m_IsGameOver())
    {
        m_Continue();
    }
    m_EndScreen();
}

void Tictactoe::m_Continue()
{
    m_GetBoard();
    m_SetUserPosition();
    m_ComputerMove();
    m_GetBoard();
}

void Tictactoe::m_EndScreen()
{
    if (m_winner == 0)
        std::cout << "\nCongratulation!!! You won!!!" << std::endl;
    else
        std::cout << "\nYou played good, better luck next time." << std::endl;

    std::cout << "Game Over" << std::endl;
}

void Tictactoe::m_GetBoard()
{
    int i = 1;
    system("cls");
    for (const auto& [position, availability] : m_position)
    {
        if (availability == m_ava.normal)
            std::cout << i << m_symbols.normal << "\t\t";

        else if (availability == m_ava.user) {
            std::cout << m_symbols.user << "\t\t";
        }

        else if (availability == m_ava.computer) {
            std::cout << m_symbols.computer << "\t\t";
        }

        if (position % 3 == 0)
            std::cout << "\n\n";
        i++;
    }
}

void Tictactoe::m_SetUserPosition()
{
    std::cout << "Your Turn: " << std::endl;
    std::cin >> m_bufferPosition;
    m_position[m_bufferPosition] = m_ava.user;

    m_PositionSeeds.erase(m_bufferPosition);
}


void Tictactoe::m_ComputerMove()
{
    char randomPos = (char)(49 + rand() % m_PositionSeeds.size());
    //Attack the middle
    if (m_position['5'] == m_ava.normal)
        m_position['5'] = m_ava.computer;
    //Random position
    else if (m_position[randomPos] == m_ava.normal)
        m_position[randomPos] = m_ava.computer;
    else m_ComputerMove();
}

bool Tictactoe::m_IsGameOver()
{
    //For 1
    if(m_position['1'] != m_ava.normal)
    {
        if (m_position['1'] == m_position['2'] && m_position['1'] == m_position['3'])
        {
            m_winner = m_position['1'];
            return true;
        }
        else if (m_position['1'] == m_position['5'] && m_position['1'] == m_position['9'])
        {
            m_winner = m_position['1'];
            return true;
        }
        else if (m_position['1'] == m_position['4'] && m_position['1'] == m_position['7'])
        {
            m_winner = m_position['1'];
            return true;
        }
    }

    //For 2
    if(m_position['2'] != m_ava.normal)
    {
        if (m_position['2'] == m_position['5'] && m_position['2'] == m_position['8'])
        {
            m_winner = m_position['2'];
            return true;
        }
    }
    //For 3
    if (m_position['3'] != m_ava.normal)
    {
        if (m_position['3'] == m_position['6'] && m_position['3'] == m_position['9'])
        {
            m_winner = m_position['3'];
            return true;
        }
        else if (m_position['3'] == m_position['5'] && m_position['3'] == m_position['7'])
        {
            m_winner = m_position['3'];
            return true;
        }
    }

    //For 4
    if(m_position['4'] != m_ava.normal)
    {
        if (m_position['4'] == m_position['5'] && m_position['4'] == m_position['6'])
        {
            m_winner = m_position['4'];
            return true;
        }
    }
    return false;
}
