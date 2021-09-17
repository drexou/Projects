#ifndef PRINT_CONTROLLER_HPP
#define PRINT_CONTROLLER_HPP

#include "controller.hpp"

class PrintController : public Controller
{
public:
    PrintController() = default;

    Command getInput();
};

#endif  // PRINT_CONTROLLER_HPP
