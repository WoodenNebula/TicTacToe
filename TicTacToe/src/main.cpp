#include <iostream>
#include "..\header\tictactoe.h"

int main(void){
    std::cout << "Hello Tic-Tac-Toe" << std::endl;

    Tictactoe T;
    
    T.StartGame();

    system("pause");
    return 0;
}