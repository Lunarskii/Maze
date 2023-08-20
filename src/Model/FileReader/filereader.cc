#include "filereader.h"

#include <iostream>

FileReader::FileReader(std::string file_name)
    : file_(new std::ifstream(file_name))
{
    if (!file_->is_open())
    {
        throw std::exception(); // "The file cannot be opened"
    }

    *file_ >> rows_ >> cols_;

    if (rows_ < 0 || rows_ > 50 || cols_ < 0 || cols_ > 50)
    {
        throw std::exception(); // "The size of the object is exceeded"
    }
}

FileReader::~FileReader()
{
    file_->close();
}

void FileReader::Upload(std::vector<std::vector<bool>>* first, std::vector<std::vector<bool>>* second)
{
    std::string line;

    if (first != nullptr) first->clear();
    if (second != nullptr) second->clear();
    std::getline(*file_, line);
    for (int i = 1; std::getline(*file_, line); ++i)
    {
        if (i <= rows_)
        {
            PutALine_(*first, line);
        }
        else if (second != nullptr)
        {
            PutALine_(*second, line);
        }
    }
}

void FileReader::PutALine_(std::vector<std::vector<bool>>& vec, std::string& line)
{
    if (!line.empty())
    {
        std::vector<bool> one_line;
        std::istringstream iss(line);
        bool number = 0;

        while (iss >> number)
        {
            one_line.push_back(number);
        }
        vec.push_back(one_line);
    }
}
