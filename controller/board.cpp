#include "board.hpp"

#include <stdexcept>
using namespace std;
#include <string>

Board::Board(unsigned height, unsigned width)
    : height{height}
    , width{width}
    , board(height, std::string(width, ' '))
    , view{nullptr}
{
}

unsigned Board::getHeight() const { return height; }
unsigned Board::getWidth() const { return width; }

void Board::setView(View* newView)
{
    view = newView;
}

void Board::draw(unsigned y, unsigned x,
                 const std::vector<std::string>& sprite)
{
    for(string str : sprite)
    {
        unsigned len = str.length();
        if(len+x > width)
            throw logic_error{"sprite out of bounds (width)"};
    }
    if(sprite.size()+y > height)
        throw logic_error{"sprite out of bounds (height)"};

    for(unsigned j=0; j<sprite.size(); j++)
    {
        for(unsigned i=0; i<sprite[j].length(); i++)
        {
            board[j+y][i+x] = sprite[j][i];
        }
    }
}

void Board::display()
{
    if(view == nullptr)
        throw logic_error{"No view member"};
    view->display(board);
}

void Board::erase()
{
    for(unsigned j=0; j<height; j++)
    {
        for(unsigned i=0; i<width; i++)
        {
            board[j][i] = ' ';
        }
    }
}
