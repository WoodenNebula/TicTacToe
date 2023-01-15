#include <iostream>
#include "..\header\tictactoe.h"

int main(void){
    char restart;
    do 
    {
        Tictactoe* T;
        T = new Tictactoe();
    
        T->StartGame();

        std::cout << "Wanna play again? Y or N" << std::endl;
        std::cin >> restart;
        T->~Tictactoe();
    } while (restart == 'y' || restart == 'Y');

    system("pause");
    return 0;
}