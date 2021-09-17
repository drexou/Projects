#ifndef CURSES_CONTROLLER_HPP
#define CURSES_CONTROLLER_HPP

#include "controller.hpp"

class CursesController : public Controller
{
public:
    CursesController() = default;

    Command getInput();
};

#endif  // CURSES_CONTROLLER_HPP
