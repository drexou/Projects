#ifndef FILE_VIEW_HPP
#define FILE_VIEW_HPP

#include "view.hpp"

class FileView : public View
{
public:
    FileView(const std::string& filename);
    void display(const std::vector<std::string>& board) override;

private:
    std::string name;
};

#endif  // FILE_VIEW_HPP
