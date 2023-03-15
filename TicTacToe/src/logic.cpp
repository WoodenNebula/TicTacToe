#include "tictactoe.h"

void Tictactoe::StartGame()
{
    char restart;
     Tictactoe* T;
    do
    {
        T = new Tictactoe();

        T->m_ContinueGame();

        std::cout << "Wanna play again? Y or N" << std::endl;
        std::cin >> restart;
        T->~Tictactoe();
    } while (restart == 'y' || restart == 'Y');
}

void Tictactoe::m_ContinueGame()
{

    m_SetSymbol();
    m_GetBoard();
    while (true)
    {
        //Validate the position user gave
        do
        {
            posERROR = m_UserMove();
        } while (!m_ValidateUserMove());

        m_GetBoard();
        if (m_IsGameOver())
            break;
        if (computerMoveDelay)
            m_MoveDelay();
        m_ComputerMove();
        m_GetBoard();
        if (m_IsGameOver()) 
            break;
    }
    m_EndScreen();
}

/// <summary>
/// Checks if the game us over or not by comparing the symbols at the positions
/// </summary>
/// <returns>bool</returns>
bool Tictactoe::m_IsGameOver()
{
    //For Draw
    if (m_position.cend() == find_if(m_position.cbegin(), m_position.cend(),
        [&](const std::string& val) -> bool { if (val == m_symbols.normal) return true; }))
    {
        return true;
    }

//Win or Lose
    //Vertical Check
    for (int x = 0; x < 3; ++x)
    {
        if (m_position.at(x) == m_position.at(x + 3) && m_position.at(x) == m_position.at(x + 3*2))
        {
            m_winner = m_position.at(x);
            return true;
        }
    }
    //Horizontal Check
    for (int y = 0; y < 7; y+=3)
    {
        if (m_position.at(y) == m_position.at(y + 1) && m_position.at(y) == m_position.at(y + 2))
        {
            m_winner = m_position.at(y);
            return true;
        }
    }
//Diagonal Checks
    if (m_position.at(0) != m_symbols.normal)
    {
        if (m_position.at(0) == m_position.at(0 + (1 + 3*1)) && m_position.at(0) == m_position.at(0 + (2 + 3*2)))
        {
            m_winner = m_position.at(0);
            return true;
        }
    }

    if (m_position.at(3) != m_symbols.normal)
    {
        if (m_position.at(3) == m_position.at(3 + (-1 + 3*1)) && m_position.at(3) == m_position.at(3 + (-2 + 3*2)))
        {
            m_winner = m_position.at(3);
            return true;
        }
    }

    return false;
}