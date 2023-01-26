#include "Tictactoe.h"

#include "Tictactoe.h"

//To avoid errors from std::cin
void inputIgnoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};


Tictactoe::Tictactoe()
    :m_position(
        { {1, A_Normal}, {2, A_Normal}, {3, A_Normal},
          {4, A_Normal}, {5, A_Normal}, {6, A_Normal},
          {7, A_Normal}, {8, A_Normal}, {9, A_Normal} }),
    m_winner(PositionState::A_Computer), posERROR(PositionERROR::noERROR)
{
    std::cout << "Starting Game" << std::endl;

    //Setting the seed for random num generator
    const auto clock = std::chrono::high_resolution_clock::now();
    srand(static_cast<uint32_t>(clock.time_since_epoch().count()));

    m_promptComputerMoveDelay();
}

Tictactoe::Tictactoe(const bool computerMoveDelayToggle)
    :m_position(
        { {1, A_Normal}, {2, A_Normal}, {3, A_Normal},
          {4, A_Normal}, {5, A_Normal}, {6, A_Normal},
          {7, A_Normal}, {8, A_Normal}, {9, A_Normal} }),
    m_winner(PositionState::A_Computer), 
    computerMoveDelay(computerMoveDelayToggle),
    posERROR(PositionERROR::noERROR)
{
    std::cout << "Starting Game" << std::endl;

    //Setting the seed for random num generator
    const auto clock = std::chrono::high_resolution_clock::now();
    srand(static_cast<uint32_t>(clock.time_since_epoch().count()));
}

Tictactoe::~Tictactoe() = default;

void Tictactoe::StartGame()
{
    m_SetSymbol();
    m_GetBoard();
    while (true)
    {
        //Validate the position user gave
        do
        {
            system("cls");
            m_GetBoard();
            posERROR = m_SetUserPosition();
            if (PositionERROR::posOccupied == posERROR)
            {
                std::cerr << "[ERROR]: THAT POSITION IS OCCUPIED!" << std::endl;
                system("pause");
            }
            else if (PositionERROR::posOutofBound == posERROR)
            {
                std::cerr << "[ERROR]: THAT POSITION DOESNOT EXIST!" << std::endl;
                system("pause");
            }
            else if (PositionERROR::badInput == posERROR)
            {
                std::cin.clear();
                inputIgnoreLine();
                std::cerr << "[ERROR]: ENTER AN ACTUAL POSITION!" << std::endl;
                system("pause");
            }
        } while (PositionERROR::noERROR != posERROR);

        m_GetBoard();
        if (m_IsGameOver()) 
            break;
        if(computerMoveDelay)
            m_MoveDelay();
        m_ComputerMove();
        m_GetBoard();
        if (m_IsGameOver()) break;
    }
    m_EndScreen();
}

void Tictactoe::m_promptComputerMoveDelay()
{
    std::cout << "Would you like Computer's move to be delayed?\n('1' for DELAY, '0' for NO delay)" << std::endl;
    std::cin >> computerMoveDelay;
    while (!std::cin.good())
    {
        std::cin.clear();
        inputIgnoreLine();
        std::cerr << "[ERROR]: Bad input!\n Give the appropriate input:" << std::endl;
        std::cin >> computerMoveDelay;
    }
}

void Tictactoe::m_SetSymbol()
{
    bool usrChoice;
    system("cls");
    std::cout << "Wanna play Circle(0) or Cross(1)?" << std::endl;
    std::cin >> usrChoice;
    while (!std::cin.good())
    {
        std::cin.clear();
        inputIgnoreLine();
        std::cerr << "[ERROR]: Bad input!\n Give the appropriate input:" << std::endl;
        std::cin >> usrChoice;
    }

    if (usrChoice) {
        m_symbols.user = " X ";
        m_symbols.computer = " O ";
    }
    else if (!usrChoice) {
        m_symbols.user = " O ";
        m_symbols.computer = " X ";
    }
    std::cout << "\n You Play:  \"" << m_symbols.user << "\"" << std::endl;
    system("pause");
}

void Tictactoe::m_GetBoard()
{
    uint32_t i = 1;
    system("cls");
    for (const auto& [position, posState] : m_position)
    {
        //If unoccupied, put unoccupied symbol there
        if (posState == A_Normal)
            std::cout << i << m_symbols.normal << "\t\t";

        //If occupied by user, put user's symbol there
        else if (posState == A_User) {
            std::cout << m_symbols.user << "\t\t";
        }

        //If occupied by computer, put compute's symbol there
        else if (posState == A_Computer) {
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
    if (m_winner == A_User)
        std::cout << "\nCongratulation!!! You won!!!" << std::endl;
    else if (m_winner == A_Computer)
        std::cout << "\nYou played good, better luck next time." << std::endl;
    else if (m_winner == A_Normal)
        std::cout << "\nGG. That was a tough game." << std::endl;

    std::cout << "Game Over" << std::endl;
}

Tictactoe::PositionERROR Tictactoe::m_SetUserPosition()
{
    std::cout << "Your Turn: " << std::endl;
    if (std::cin >> m_bufferPosition)
    {
        if (m_bufferPosition >= 0 && m_bufferPosition <= 9)
        {
            if (m_position[m_bufferPosition] == A_Normal)
            {
                m_position[m_bufferPosition] = A_User;
                m_positionTracker.erase(m_bufferPosition);
                return PositionERROR::noERROR;
            }
            else {
                return PositionERROR::posOccupied;
            }
        }
        else
        {
            return PositionERROR::posOutofBound;
        }

    }
    else
    {
        return PositionERROR::badInput;
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
    std::this_thread::sleep_for(0.5s);
}

void Tictactoe::m_ComputerMove()
{
    //Attack the middle if available
    if (m_position.at(5) == A_Normal)
        m_position.at(5) = A_Computer;
    else
    {
        do  //Get a Random position between 1 and 9
        {   
            m_lastPair = m_positionTracker.end();
            m_lastPair--;
            m_bufferPosition = 1 + rand() % m_lastPair->first;

        } while (m_position[m_bufferPosition] != A_Normal);

        m_position[m_bufferPosition] = A_Computer;
        m_positionTracker.erase(m_bufferPosition);
    }
}

bool Tictactoe::m_IsGameOver()
{
    //For Draw
    if (m_positionTracker.empty())
    {
        m_winner = A_Computer;
        return true;
    }

    //Win or Lose
    //For 1st Row
    if(m_position.at(1) != A_Normal)
    {
        //Horizontal Check
        if (m_position.at(1) == m_position.at(2) && m_position.at(1) == m_position.at(3))
        {
            m_winner = m_position.at(1);
            return true;
        }
        //Diagonal Check
        else if (m_position.at(1) == m_position.at(5) && m_position.at(1) == m_position[9])
        {
            m_winner = m_position.at(1);
            return true;
        }
        //Vertical Check
        else if (m_position.at(1) == m_position.at(4) && m_position.at(1) == m_position[7])
        {
            m_winner = m_position.at(1);
            return true;
        }
    }

    //For 2nd Column
    if(m_position.at(2) != A_Normal)
    {
        //Vertical Check
        if (m_position.at(2) == m_position.at(5) && m_position.at(2) == m_position[8])
        {
            m_winner = m_position.at(2);
            return true;
        }
    }

    //For 3rd Column
    if (m_position.at(3) != A_Normal)
    {
        //Vertical Check
        if (m_position.at(3) == m_position.at(6) && m_position.at(3) == m_position[9])
        {
            m_winner = m_position.at(3);
            return true;
        }
        //Diagonal Check
        else if (m_position.at(3) == m_position.at(5) && m_position.at(3) == m_position[7])
        {
            m_winner = m_position.at(3);
            return true;
        }
    }

    //For 2nd Row / 4th position
    if(m_position.at(4) != A_Normal)
    {
        //Horizontal Check
        if (m_position.at(4) == m_position.at(5) && m_position.at(4) == m_position.at(6))
        {
            m_winner = m_position.at(4);
            return true;
        }
    }

    //For 3rd Row / 7th Position
    if (m_position.at(7) != A_Normal)
    {
        //Horizontal Check
        if (m_position.at(7) == m_position.at(8) && m_position.at(7) == m_position.at(9))
        {
            m_winner = m_position.at(7);
            return true;
        }
    }

    return false;
}
