#include "Tictactoe.h"

#include "Tictactoe.h"


Tictactoe::Tictactoe()
    :m_position(
        { {'1', m_ava.normal},{'2', m_ava.normal},{'3', m_ava.normal},
            {'4', m_ava.normal},{'5', m_ava.normal},{'6', m_ava.normal},
            {'7', m_ava.normal},{'8', m_ava.normal},{'9', m_ava.normal} })
{
    SetSymbol();
}

void Tictactoe::SetSymbol()
{
    bool isCross;
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
}

void Tictactoe::StartGame()
{
    GetBoard();
    SetUserPosition();
}

void Tictactoe::GetBoard()
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

void Tictactoe::SetUserPosition()
{
    char position;
    std::cout << "Your Turn: " << std::endl;
    std::cin >> position;
    m_position[position] = m_ava.user;

    //Check if the game is finished or not
    if(!m_isGameOver())
        m_ComputerMove(position);
        


}


void Tictactoe::m_ComputerMove(char  userPosition)
{
    if (m_position['5'] == m_ava.normal)
        m_position['5'] = m_ava.computer;

    for (auto& [pos, availab] : m_position)
        std::cout << "[" << pos << "]" << " : " << availab << std::endl;

    if (m_position[userPosition + '1'] == m_ava.normal)
        m_position[userPosition + '1'] = m_ava.computer;
    //else /*Tictactoe::m_ComputerMove(userPosition + '1');*/
}

bool Tictactoe::m_isGameOver()
{
    return true;
}
