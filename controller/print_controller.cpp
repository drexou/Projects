#include "print_controller.hpp"
#include <iostream>
#include <string>
using namespace std;

Command PrintController::getInput()
{
    char input;
    cin >> input;
    if(input == 'a')
        return Command::Left;
    else if(input == 'd')
        return Command::Right;
    else if(input == 'w')
        return Command::Up;
    else if(input == 's')
        return Command::Down;
    else
        return Command::Invalid;
}
