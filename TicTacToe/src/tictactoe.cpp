#include "Tictactoe.h"

///
/// To avoid errors from std::cin
///
void ignoreBadInputLines()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

Tictactoe::Tictactoe()
    :m_winner(m_symbols.normal), posERROR(PossibleERRORS::noERROR),
    m_position(
        { " ", " ", " ",
         " ", " ", " ",
         " ", " ", " " })
{
    std::cout << "Starting Game" << std::endl;

    //Setting the seed for random num generator
    const auto clock = std::chrono::high_resolution_clock::now();
    srand(static_cast<uint32_t>(clock.time_since_epoch().count()));

    m_PromptComputerMoveDelay();
}

Tictactoe::Tictactoe(const bool computerMoveDelayToggle)
    :m_position(
        {" ", " ", " ",
         " ", " ", " ",
         " ", " ", " "}),
    m_winner(), 
    computerMoveDelay(computerMoveDelayToggle),
    posERROR(PossibleERRORS::noERROR)
{
    std::cout << "Starting Game" << std::endl;

    //Setting the seed for random num generator
    const auto clock = std::chrono::high_resolution_clock::now();
    srand(static_cast<uint32_t>(clock.time_since_epoch().count()));
}

Tictactoe::~Tictactoe() = default;

/// <summary>
/// Asks the user if they want the computer's move to be delayed
/// </summary>
void Tictactoe::m_PromptComputerMoveDelay()
{
    std::cout << "Would you like Computer's move to be delayed?\n('1' for DELAY, '0' for NO delay)" << std::endl;
    std::cin >> computerMoveDelay;
    while (!std::cin.good())
    {
        ignoreBadInputLines();
        std::cerr << "[ERROR]: Bad input!\n Give the appropriate input:" << std::endl;
        std::cin >> computerMoveDelay;
    }
}

/// <summary>
/// Asks the user what they want to play and sets the symbol accordingly
/// </summary>
void Tictactoe::m_SetSymbol()
{
    bool usrChoice;
    system("cls");
    std::cout << "Wanna play Circle(0) or Cross(1)?" << std::endl;
    std::cin >> usrChoice;
    while (!std::cin.good())
    {
        ignoreBadInputLines();
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

/// <summary>
/// Print current board/slots in the console
/// </summary>
void Tictactoe::m_GetBoard()
{
    int i = 1;
    system("cls");
    for (const auto& slot: m_position)
    {
        std::cout << slot << "\t\t";
        
        //Switch rows after three symbols
        if (i % 3 == 0)
            std::cout << "\n\n";
        i++;
    }
}

void Tictactoe::m_EndScreen()
{
    if (m_winner == m_symbols.user)
        std::cout << "\nCongratulation!!! You won!!!" << std::endl;
    else if (m_winner == m_symbols.computer)
        std::cout << "\nYou played good, better luck next time." << std::endl;
    else
        std::cout << "\nGG. That was a tough game." << std::endl;

    std::cout << "Game Over" << std::endl;
}


Tictactoe::PossibleERRORS Tictactoe::m_UserMove()
{
    system("cls");
    m_GetBoard();
    std::cout << "Your Turn: " << std::endl;
    if (std::cin >> m_bufferPosition)
    {
        if (m_bufferPosition > 0 && m_bufferPosition <= 9)
        {
            if (m_position.at(m_bufferPosition - 1) == m_symbols.normal)
            {
                m_position.at(m_bufferPosition - 1) = m_symbols.user;
                return PossibleERRORS::noERROR;
            }
            else return PossibleERRORS::posOccupied;
        }
        else return PossibleERRORS::posOutOfBound;
    }
    else return PossibleERRORS::badInput;
}


bool Tictactoe::m_ValidateUserMove()
{
    if (PossibleERRORS::posOccupied == posERROR)
    {
        std::cerr << "[ERROR]: THAT POSITION IS OCCUPIED!" << std::endl;
        system("pause");
        return false;
    }
    else if (PossibleERRORS::posOutOfBound == posERROR)
    {
        std::cerr << "[ERROR]: THAT POSITION DOESNOT EXIST!" << std::endl;
        system("pause");
        return false;
    }
    else if (PossibleERRORS::badInput == posERROR)
    {
        std::cin.clear();
        ignoreBadInputLines();
        std::cerr << "[ERROR]: ENTER AN ACTUAL POSITION!" << std::endl;
        system("pause");
        return false;
    }
    return true;
}

/// <summary>
/// Adds delay and "Thinking..."
/// </summary>
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
    if (m_position.at(4) == m_symbols.normal)
        m_position.at(4) = m_symbols.computer;

    else
    {
        auto freeSlot = find_if(m_position.cbegin(), m_position.cend(),
            [&](const std::string& val) -> bool { if (val == m_symbols.normal) return true; });

        for (int i = 0; i < 8; ++i)
        {
            if (m_position.at(i) != m_symbols.normal)
                continue;
            //branchCompMove(i);

        }
        /* Computer Move Logic HERE */
    }
}
