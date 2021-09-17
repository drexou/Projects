#ifndef CURSES_VIEW_HPP
#define CURSES_VIEW_HPP

#include "view.hpp"

class CursesView : public View
{
public:
    CursesView();
    ~CursesView();
    void display(const std::vector<std::string>& board) override;

private:
    // TODO: Add members (if any) here.
    
};

#endif  // CURSES_VIEW_HPP
