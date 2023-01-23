#include "Tictactoe.h"

#include "Tictactoe.h"


Tictactoe::Tictactoe()
    :m_position(
        { {1, m_availability.normal}, {2, m_availability.normal}, {3, m_availability.normal},
          {4, m_availability.normal}, {5, m_availability.normal}, {6, m_availability.normal},
          {7, m_availability.normal}, {8, m_availability.normal}, {9, m_availability.normal} })
{
    std::cout << "Starting Game" << std::endl;
    //setting the seed for random num generator
    srand((unsigned)time(0));

    m_SetSymbol();
}

Tictactoe::~Tictactoe() = default;

void Tictactoe::m_SetSymbol()
{
    int usrChoice;
    system("cls");
    std::cout << "Wanna play Circle(0) or Cross(1)? (Anything ><0 is considered a cross)" << std::endl;
    std::cin >> usrChoice;

    bool isCross = static_cast<bool>(usrChoice);

    m_symbols.normal = " -- ";
    if (isCross) {
        m_symbols.user = " X ";
        m_symbols.computer = " O ";
    }
    else if (!isCross) {
        m_symbols.user = " O ";
        m_symbols.computer = " X ";
    }
    std::cout << "\n You Play:  \"" << m_symbols.user << "\"" << std::endl;
    system("pause");
}

void Tictactoe::StartGame()
{
    while (1)
    {
        m_GetBoard();
        m_SetUserPosition();
        m_GetBoard();
        if (m_IsGameOver())
            break;
        m_MoveDelay();
        m_ComputerMove();
    }
    m_EndScreen();
}

void Tictactoe::m_GetBoard()
{
    int i = 1;
    system("cls");
    for (const auto& [position, availability] : m_position)
    {
        //If unoccupied, put unoccupied symbol there
        if (availability == m_availability.normal)
            std::cout << i << m_symbols.normal << "\t\t";

        //If occupied by user, put user's symbol there
        else if (availability == m_availability.user) {
            std::cout << m_symbols.user << "\t\t";
        }

        //If occupied by computer, put compute's symbol there
        else if (availability == m_availability.computer) {
            std::cout << m_symbols.computer << "\t\t";
        }
        
        //Switch rows after three symbols
        if (position % 3 == 0)
            std::cout << "\n\n";
        i++;
    }
}

void Tictactoe::m_EndScreen()
{
    if (m_winner == 0)
        std::cout << "\nCongratulation!!! You won!!!" << std::endl;
    else if (m_winner == 1)
        std::cout << "\nYou played good, better luck next time." << std::endl;
    else if (m_winner == -1)
        std::cout << "\nGG. That was a tough game." << std::endl;

    std::cout << "Game Over" << std::endl;
}

void Tictactoe::m_SetUserPosition()
{
    std::cout << "Your Turn: " << std::endl;
    std::cin >> m_bufferPosition;

    if (m_bufferPosition >= 0 && m_bufferPosition <= 9 )
    {
        if (m_position[m_bufferPosition] == m_availability.normal)
        {
            m_position[m_bufferPosition] = m_availability.user;
            m_PositionTracker.erase(m_bufferPosition);
        }
        else {
            std::cout << "PLACE OCCUPIED" << std::endl;
            exit(101);
        }
    }
    else
    {
        std::cout << "Error, that position doesnot exist" << std::endl;
        exit(102);
    }
}

void Tictactoe::m_MoveDelay()
{
    //"Thinking . . ."
    //Delay the computer's move
    std::cout << "Thinking";
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(0.5s);
    std::cout << " .";
    std::this_thread::sleep_for(0.5s);
    std::cout << " .";
    std::this_thread::sleep_for(0.5s);
    std::cout << " .";
    std::this_thread::sleep_for(1s);
}

void Tictactoe::m_ComputerMove()
{
    //Attack the middle if available
    if (m_position[5] == m_availability.normal)
        m_position[5] = m_availability.computer;
    else
    {
        do  //Get a Random position between 1 and 9
        {
            m_lastPair = m_PositionTracker.end();
            m_lastPair--;
            m_bufferPosition = 1 + rand() % m_lastPair->first;

        } while (m_position[m_bufferPosition] != m_availability.normal);

        m_position[m_bufferPosition] = m_availability.computer;
        m_PositionTracker.erase(m_bufferPosition);
    }
}

bool Tictactoe::m_IsGameOver()
{
    //For Draw
    if (m_PositionTracker.empty())
    {
        m_winner = -1;
        return true;
    }

    //Win or Lose
    //For 1st Row
    if(m_position[1] != m_availability.normal)
    {
        //Horizontal Check
        if (m_position[1] == m_position[2] && m_position[1] == m_position[3])
        {
            m_winner = m_position[1];
            return true;
        }
        //Diagonal Check
        else if (m_position[1] == m_position[5] && m_position[1] == m_position[9])
        {
            m_winner = m_position[1];
            return true;
        }
        //Vertical Check
        else if (m_position[1] == m_position[4] && m_position[1] == m_position[7])
        {
            m_winner = m_position[1];
            return true;
        }
    }

    //For 2nd Column
    if(m_position[2] != m_availability.normal)
    {
        //Vertical Check
        if (m_position[2] == m_position[5] && m_position[2] == m_position[8])
        {
            m_winner = m_position[2];
            return true;
        }
    }

    //For 3rd Column
    if (m_position[3] != m_availability.normal)
    {
        //Vertical Check
        if (m_position[3] == m_position[6] && m_position[3] == m_position[9])
        {
            m_winner = m_position[3];
            return true;
        }
        //Diagonal Check
        else if (m_position[3] == m_position[5] && m_position[3] == m_position[7])
        {
            m_winner = m_position[3];
            return true;
        }
    }

    //For 2nd Row/ 4th position
    if(m_position[4] != m_availability.normal)
    {
        //Horizontal Check
        if (m_position[4] == m_position[5] && m_position[4] == m_position[6])
        {
            m_winner = m_position[4];
            return true;
        }
    }

    return false;
}
