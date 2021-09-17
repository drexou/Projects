#include "curses_controller.hpp"
#include <curses.h>
#include <iostream>
using namespace std;


Command CursesController::getInput()
{
    noecho();
    int input = getch();
    
    if(input == 27)
    {
        input = getch();
        input = getch();
    }

    if(input == 119 || input == 65)
        return Command::Up;
    else if(input == 115 || input == 66)
        return Command::Down;
    else if(input == 97 || input == 68)
        return Command::Left;
    else if(input == 100 || input == 67)
        return Command::Right;
    else
        return Command::Invalid;
}
