#include "print_view.hpp"
#include <string.h>
#include <iostream>
using namespace std;

void PrintView::display(const std::vector<std::string>& board)
{
    for(std::string str : board)
        cout << str << endl;
}
