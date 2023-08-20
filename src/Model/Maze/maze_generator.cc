#include "maze_generator.h"

MazeGenerator::MazeGenerator(unsigned int rows, unsigned int cols)
    : rows_(rows)
    , cols_(cols)
{
    if (rows_ < 0 || rows_ > 50 || cols_ < 0 || cols_ > 50)
    {
        throw std::exception(); // обработать исключение
    }

    line_.resize(cols, 0);
    right_walls_.resize(rows_, std::vector<bool>(cols_, 0));
    bottom_walls_.resize(rows_, std::vector<bool>(cols_, 0));
}

void MazeGenerator::GenerateMaze()
{
    for (int i = 0; i < rows_ - 1; ++i)
    {
        AssignUniqueSet_();
        AddRightWalls_(i);
        AddBottomWalls_(i);
        PrepareANewSet_(i);
    }
    AddLastLine_();
}

std::vector<std::vector<bool>> MazeGenerator::GetRightWalls()
{
    return right_walls_;
}

std::vector<std::vector<bool>> MazeGenerator::GetBottomWalls()
{
    return bottom_walls_;
}

unsigned int MazeGenerator::GetRows()
{
    return rows_;
}

unsigned int MazeGenerator::GetCols()
{
    return cols_;
}

void MazeGenerator::AddRightWalls_(int row)
{
    for (int i = 0; i < cols_ - 1; ++i)
    {
        if (RandomBool_() == true || line_[i] == line_[i + 1])
        {
            right_walls_[row][i] = true;
        }
        else
        {
            MergeSets_(line_[i], line_[i + 1]);
        }
    }
    right_walls_[row][cols_ - 1] = true;
}

void MazeGenerator::AddBottomWalls_(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (RandomBool_() == true && GetNumberOfCellsWithoutBottomWall_(line_[i], row) > 1)
        {
            bottom_walls_[row][i] = true;
        }
    }
}

void MazeGenerator::AddLastLine_()
{
    AssignUniqueSet_();
    AddRightWalls_(rows_ - 1);

    for (int i = 0; i < cols_ - 1; ++i)
    {
        if (line_[i] != line_[i + 1])
        {
            right_walls_[rows_ - 1][i] = false;
            MergeSets_(line_[i], line_[i + 1]);
        }
        bottom_walls_[rows_ - 1][i] = true;
    }
    bottom_walls_[rows_ - 1][cols_ - 1] = true;
}

unsigned int MazeGenerator::GetNumberOfCellsWithoutBottomWall_(unsigned int set_number, unsigned int row)
{
    unsigned int count = 0;

    for (int i = 0; i < cols_; ++i)
    {
        if (line_[i] == set_number && bottom_walls_[row][i] == false)
        {
            ++count;
        }
    }

    return count;
}

void MazeGenerator::MergeSets_(unsigned int first_set, unsigned int second_set)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (line_[i] == second_set)
        {
            line_[i] = first_set;
        }
    }
}

void MazeGenerator::AssignUniqueSet_()
{
    for (int i = 0; i < cols_; ++i)
    {
        if (line_[i] == 0)
        {
            line_[i] = ++counter_;
        }
    }
}

void MazeGenerator::PrepareANewSet_(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (bottom_walls_[row][i] == true)
        {
            line_[i] = 0;
        }
    }
}

bool MazeGenerator::RandomBool_() // заменить на inline, если рандом оставлять мой
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(engine));
    // return std::rand() % 2 == 0;
}
