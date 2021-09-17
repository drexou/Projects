#include "file_view.hpp"
#include <fstream>
#include <iostream>
using namespace std;

FileView::FileView(const std::string& filename)
    : name{filename}
{}

void FileView::display(const std::vector<std::string>& board)
{
    ofstream boardFile;
    boardFile.open(name, fstream::app);
    unsigned width = board[1].length();
    unsigned height = board.size();
    
    for(unsigned j=0; j<height; j++)
    {
        for(unsigned i=0; i<width; i++)
        {
            boardFile << board[j][i];
        }
        boardFile << '\n';
    }
    boardFile.close();
}
