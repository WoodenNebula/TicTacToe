#include <iostream>
#include "..\header\tictactoe.h"

int main(void){
    char restart;
    Tictactoe* T;
    do 
    {
        T = new Tictactoe();
    
        T->StartGame();

        std::cout << "Wanna play again? Y or N" << std::endl;
        std::cin >> restart;
        T->~Tictactoe();
    } while (restart == 'y' || restart == 'Y');

    return EXIT_SUCCESS;
}