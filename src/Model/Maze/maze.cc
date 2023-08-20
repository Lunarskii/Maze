#include "maze.h"

typename Maze::Maze& Maze::GetInstance() 
{
    static Maze instance;
    return instance;
}

void Maze::UploadMazeFromFile(std::string file_name)
{
    FileReader(file_name).Upload(&right_walls_, &bottom_walls_);
}

void Maze::GenerateMaze(unsigned int rows, unsigned int cols)
{
    MazeGenerator generator(rows, cols);
    generator.GenerateMaze();
    right_walls_ = generator.GetRightWalls();
    bottom_walls_ = generator.GetBottomWalls();
    rows_ = generator.GetRows();
    cols_ = generator.GetCols();
}

void Maze::SaveToFile(std::string file_name)
{
    std::ofstream file(file_name);

    if (!file.is_open()) 
    {
        throw std::exception(); // обработать исключение
        // std::cout << "file not created" << std::endl;
        // return;
    }

    file << rows_ << " " << cols_;
    WriteDataToFile_(file, right_walls_);
    file << "\n";
    WriteDataToFile_(file, bottom_walls_);
    file.close();
}

void Maze::WriteDataToFile_(std::ofstream& file, maze_type& vec)
{
    for (const auto& vectors : vec)
    {
        file << "\n";
        for (const auto& data : vectors)
        {
            file << data << " ";
        }
    }
}

std::vector<std::vector<bool>>& Maze::GetRightWalls()
{
    return right_walls_;
}

std::vector<std::vector<bool>>& Maze::GetBottomWalls()
{
    return bottom_walls_;
}
