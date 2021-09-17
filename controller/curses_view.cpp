#include "curses_view.hpp"
#include <curses.h>
#include <iostream>
using namespace std;

CursesView::CursesView()
{
    initscr();
    noecho();
}

CursesView::~CursesView()
{
    endwin();
}

void CursesView::display(const std::vector<std::string>& board)
{

    unsigned width = board[1].length();
    unsigned height = board.size();

    for(int j=0; j<(int)height; j++)
    {
        move(j,0);
        for(int i=0; i<(int)width; i++)
            addch(board[j][i]);
    }
    refresh();
}
