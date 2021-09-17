#include "controller.hpp"

std::string cmdToString(Command cmd)
{
    if(cmd == Command::Left)
        return "left";
    else if(cmd == Command::Right)
        return "right";
    else if(cmd == Command::Up)
        return "up";
    else if(cmd == Command::Down)
        return "down";
    else
        return "invalid";
    
}
