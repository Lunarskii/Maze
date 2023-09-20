#include "maze.h"

namespace s21
{

typename Maze::Maze& Maze::GetInstance() 
{
    static Maze instance;
    return instance;
}

void Maze::UploadMazeFromFile(std::string file_name)
{
    maze_ = MazeFileManager::Upload(file_name);

    if (!maze_.IsValid())
    {
        throw std::runtime_error("The model is not loaded");
    }
}

void Maze::GenerateMaze(unsigned int rows, unsigned int cols)
{
    maze_ = MazeGenerator().Generate(rows, cols);
}

void Maze::SaveMaze(std::string file_name)
{
    MazeFileManager::Save(file_name, maze_);
}

std::vector<Point> Maze::FindPath(Point from, Point to)
{
    return PathFinder(maze_, from, to).FindPath();
}

MazeType& Maze::GetMaze()
{
    return maze_;
}

} // namespace s21
