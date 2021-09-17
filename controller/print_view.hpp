#ifndef PRINT_VIEW_HPP
#define PRINT_VIEW_HPP

#include "view.hpp"

class PrintView : public View
{
public:
    PrintView() = default;
    void display(const std::vector<std::string>& board) override;
};

#endif  // PRINT_VIEW_HPP
