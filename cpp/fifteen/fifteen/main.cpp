#include <iostream>
#include "Board.h"
#include <conio.h>

int main()
{
    Board board;
    board.print();

    for (;;) {
        std::cout << std::endl;
        int code = _getch();
        system("cls");
        std::cout << "code - " << code << std::endl;
        board.move(code);
        board.print();
    }
    return 1;
}