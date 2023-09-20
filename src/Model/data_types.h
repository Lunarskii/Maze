#ifndef A1_MAZE_MODEL_DATA_TYPES_H_
#define A1_MAZE_MODEL_DATA_TYPES_H_

#include <vector>

namespace s21
{

struct Point final 
{
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y){};
};

struct SidePoint final 
{
    int x;
    int y;
    long value;
};

enum TypesOfEntities
{
    kMaze = 1,
    kCave = 2
};

enum class Limits
{
    kMinOfRows = 0,
    kMinOfCols = 0,
    kMaxOfRows = 50,
    kMaxOfCols = 50,
};

enum Cell
{
    kAliveCell = 1,
    kDeathCell = 0
};

template <TypesOfEntities T>
struct BasicType final
{};

template <>
struct BasicType<kMaze> final
{
    using data_type = std::vector<std::vector<long>>;
    data_type right_walls;
    data_type bottom_walls;
    std::size_t rows{};
    std::size_t cols{};

    bool IsValid() const
    {
        if (right_walls.empty() || bottom_walls.empty())
        {
            return false;
        } 
        else if (rows > static_cast<std::size_t>(Limits::kMaxOfRows) || cols > static_cast<std::size_t>(Limits::kMaxOfCols))
        {
            return false;
        }

        for (auto i : right_walls)
        {
            for (auto j : i)
            {
                if (j < 0 || j > 1)
                {
                    return false;
                }
            }
        }

        for (auto i : bottom_walls)
        {
            for (auto j : i)
            {
                if (j < 0 || j > 1)
                {
                    return false;
                }
            }
        }

        return true;
    }

    void Clear()
    {
        right_walls.clear();
        bottom_walls.clear();
        rows = 0;
        cols = 0;
    }
};

template <>
struct BasicType<kCave> final
{
    using data_type = std::vector<std::vector<long>>;
    data_type cave_data;
    std::size_t rows{};
    std::size_t cols{};
    unsigned int limit_birth{};
    unsigned int limit_death{};
    unsigned int initial_chance{};

    bool IsValid() const
    {
        if (cave_data.empty())
        {
            return false;
        }
        else if (rows > static_cast<std::size_t>(Limits::kMaxOfRows) || cols > static_cast<std::size_t>(Limits::kMaxOfCols))
        {
            return false;
        }

        for (auto i : cave_data)
        {
            for (auto j : i)
            {
                if (j < 0 || j > 1)
                {
                    return false;
                }
            }
        }

        return true;
    }

    void Clear()
    {
        cave_data.clear();
        rows = 0;
        cols = 0;
    }
};

using MazeType = BasicType<kMaze>;
using CaveType = BasicType<kCave>;

} // namespace s21

#endif  // A1_MAZE_MODEL_DATA_TYPES_H_
