#ifndef BOARD_HPP
#define BOARD_HPP

#include "view.hpp"

#include <string>
#include <vector>

class Board final
{
public:
    Board(unsigned height, unsigned width);
    ~Board() = default;
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    unsigned getHeight() const;
    unsigned getWidth() const;

    void setView(View* newView);

    void draw(unsigned y, unsigned x,
              const std::vector<std::string>& sprite);

    void display();

    void erase();

private:
    unsigned height;
    unsigned width;
    std::vector<std::string> board;
    View* view;
};

#endif  // BOARD_HPP
