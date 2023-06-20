#include "model.h"

void Model::UploadMazeFromFile(std::string file_name)
{
    std::ifstream file(file_name);
    std::string line;

    if (!file.is_open())
    {
        std::cout << "file is not opened" << std::endl;
        return;
    }

    std::getline(file, line);
    int x = 0;
    sscanf(line.c_str(), "%d", &x);

    for (int i = 1; std::getline(file, line); ++i)
    {
        if (i <= x)
        {
            PutALine(right_walls_, line);
        }
        else
        {
            PutALine(bottom_walls_, line);
        }
    }
}

void Model::PutALine(std::vector<std::vector<bool>>& vec, std::string& line)
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

void Model::printMaze()
{
    std::cout << "right_walls: " << std::endl << std::endl;
    for (auto it = right_walls_.begin(); it != right_walls_.end(); ++it)
    {
        for (auto number : *it)
        {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "bottom_walls: " << std::endl << std::endl;
    for (auto it = bottom_walls_.begin(); it != bottom_walls_.end(); ++it)
    {
        for (auto number : *it)
        {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }
}
