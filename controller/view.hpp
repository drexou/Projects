#ifndef VIEW_HPP
#define VIEW_HPP

#include <string>
#include <vector>

class View
{
public:
    View() = default;
    virtual ~View() = default;
    View(const View&) = delete;
    View& operator=(const View&) = delete;

    virtual void display(const std::vector<std::string>& board) = 0;
};

#endif  // VIEW_HPP
