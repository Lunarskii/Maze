#ifndef A1_MAZE_MODEL_GENERATOR_H_
#define A1_MAZE_MODEL_GENERATOR_H_

#include <random>
#include <vector>
#include <algorithm>
#include "data_types.h"

namespace s21
{

template <TypesOfEntities T>
class Generator final {};

template <>
class Generator<kMaze> final
{
public:
    MazeType Generate(unsigned int rows, unsigned int cols)
    {
        maze_.rows = rows;
        maze_.cols = cols;
        line_.resize(cols, 0);
        maze_.right_walls.resize(maze_.rows, std::vector<long>(maze_.cols));
        maze_.bottom_walls.resize(maze_.rows, std::vector<long>(maze_.cols));

        for (std::size_t i = 0; i < maze_.rows - 1; ++i)
        {
            AssignUniqueSet_();
            AddRightWalls_(i);
            AddBottomWalls_(i);
            PrepareANewSet_(i);
        }
        AddLastLine_();

        return maze_;
    }

private:
    MazeType maze_;
    std::size_t counter_{ 0 };
    std::vector<int> line_;

    bool RandomBool_()
    {
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_int_distribution<int> dist(0, 1);
        return static_cast<bool>(dist(engine));
        // return std::rand() % 2 == 0;
    }

    void AssignUniqueSet_()
    {
        for (std::size_t i = 0; i < maze_.cols; ++i)
        {
            if (line_[i] == 0)
            {
                line_[i] = ++counter_;
            }
        }
    }

    void PrepareANewSet_(std::size_t row)
    {
        for (std::size_t i = 0; i < maze_.cols; ++i)
        {
            if (maze_.bottom_walls[row][i] == true)
            {
                line_[i] = 0;
            }
        }
    }

    void AddRightWalls_(std::size_t row)
    {
        for (std::size_t i = 0; i < maze_.cols - 1; ++i)
        {
            if (RandomBool_() == true || line_[i] == line_[i + 1])
            {
                maze_.right_walls[row][i] = true;
            }
            else
            {
                MergeSets_(line_[i], line_[i + 1]);
            }
        }
        maze_.right_walls[row][maze_.cols - 1] = true;
    }

    void AddBottomWalls_(std::size_t row)
    {
        for (std::size_t i = 0; i < maze_.cols; ++i)
        {
            if (RandomBool_() == true && GetNumberOfCellsWithoutBottomWall_(line_[i], row) > 1)
            {
                maze_.bottom_walls[row][i] = true;
            }
        }
    }

    void AddLastLine_()
    {
        AssignUniqueSet_();
        AddRightWalls_(maze_.rows - 1);

        for (std::size_t i = 0; i < maze_.cols - 1; ++i)
        {
            if (line_[i] != line_[i + 1])
            {
                maze_.right_walls[maze_.rows - 1][i] = false;
                MergeSets_(line_[i], line_[i + 1]);
            }
            maze_.bottom_walls[maze_.rows - 1][i] = true;
        }
        maze_.bottom_walls[maze_.rows - 1][maze_.cols - 1] = true;
    }

    void MergeSets_(std::size_t first_set, std::size_t second_set)
    {
        for (std::size_t i = 0; i < maze_.cols; ++i)
        {
            if (line_[i] == static_cast<int>(second_set))
            {
                line_[i] = first_set;
            }
        }
    }

    std::size_t GetNumberOfCellsWithoutBottomWall_(std::size_t set_number, std::size_t row)
    {
        std::size_t count = 0;

        for (std::size_t i = 0; i < maze_.cols; ++i)
        {
            if (line_[i] == static_cast<int>(set_number) && maze_.bottom_walls[row][i] == false)
            {
                ++count;
            }
        }

        return count;
    }
};

template <>
class Generator<kCave> final
{
public:
    static CaveType Generate(unsigned int rows, unsigned int cols, unsigned int initial_chance)
    {
        CaveType cave;
        cave.cave_data.resize(rows, std::vector<long>(cols));
        cave.rows = rows;
        cave.cols = cols;
        cave.initial_chance = initial_chance;

        std::vector<long> flat_matrix(rows * cols);
        int alive_cell_count = cave.initial_chance / 100.0 * rows * cols;
        for (int i = 0; i < alive_cell_count; ++i) flat_matrix[i] = Cell::kAliveCell;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(flat_matrix.begin(), flat_matrix.end(), gen);

        int k = 0;
        for (unsigned int i = 0; i < rows; ++i) 
        {
            for (unsigned int j = 0; j < cols; ++j) 
            {
                cave.cave_data[i][j] = flat_matrix[k++];
            }
        }

        return cave;
    }
};

using MazeGenerator = Generator<kMaze>;
using CaveGenerator = Generator<kCave>;

} // namespace s21

#endif  // A1_MAZE_MODEL_GENERATOR_H_
