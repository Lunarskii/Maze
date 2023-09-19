#include "path_finder.h"

PathFinder::PathFinder(const MazeType& maze, Point from, Point to)
    : maze_(maze)
    , from_(from)
    , to_(to)
    , wave_number_{0}
    , empty_value_{10000}
{
    old_wave_ = { from };
    length_map_.resize(maze_.rows, std::vector<int>(maze_.cols));
    for (auto& i : length_map_)
    {
        for (auto& j : i)
        {
            j = empty_value_;
        }
    }
    length_map_[from_.x][from_.y] = wave_number_;
}

std::vector<Point> PathFinder::FindPath()
{
    if (!maze_.IsValid() || !IsValidPoints_(from_, to_))
    {
        return {};
    }
    while (!old_wave_.empty() && !StepWave_()) {}

    return MakePath_();
}

bool PathFinder::IsValidPoints_(Point from, Point to)
{
    return !(from.x >= static_cast<int>(maze_.rows) || from.y >= static_cast<int>(maze_.cols) || to.x >= static_cast<int>(maze_.rows) || to.y >= static_cast<int>(maze_.cols));
}

bool PathFinder::StepWave_()
{
    ++wave_number_;

    for (auto [row, col] : old_wave_)
    {
        for (auto [x, y, value] : GetVectorOfMoves_(row, col))
        {
            if (value == 0)
            {
                if (length_map_[x][y] == empty_value_)
                {
                    wave_.emplace_back(x, y);
                    length_map_[x][y] = wave_number_;
                }

                if (x == to_.x && y == to_.y)
                {
                    return true;
                }
            }
        }
    }
    old_wave_ = std::move(wave_);

    return false;
}

std::vector<Point> PathFinder::MakePath_()
{
    std::vector<Point> path{to_};
    int x_size = length_map_[0].size();
    int y_size = length_map_.size();
    auto& [row, col] = to_;

    while (length_map_[row][col] != 0)
    {
        if (col - 1 >= 0 && length_map_[row][col - 1] == length_map_[row][col] - 1 && maze_.right_walls[row][col - 1] == 0)
        {
            --col;
        }
        else if (col <= x_size - 1 && length_map_[row][col + 1] == length_map_[row][col] - 1 && maze_.right_walls[row][col] == 0)
        {
            ++col;
        }
        else if (row - 1 >= 0 && length_map_[row - 1][col] == length_map_[row][col] - 1 && maze_.bottom_walls[row - 1][col] == 0)
        {
            --row;
        }
        else if (row <= y_size - 1 && length_map_[row + 1][col] == length_map_[row][col] - 1 && maze_.bottom_walls[row][col] == 0)
        {
            ++row;
        }
        else
        {
            return {};
        }
        path.emplace_back(to_);
    }

    return path;
}

std::vector<SidePoint> PathFinder::GetVectorOfMoves_(int row, int col)
{   
    std::vector<SidePoint> points;

    if (row > 0)
    {
        points.emplace_back(SidePoint{row - 1, col, maze_.bottom_walls[row - 1][col]});
    }
    if (col > 0)
    {
        points.emplace_back(SidePoint{row, col - 1, maze_.right_walls[row][col - 1]});
    }
    points.emplace_back(SidePoint{row + 1, col, maze_.bottom_walls[row][col]});
    points.emplace_back(SidePoint{row, col + 1, maze_.right_walls[row][col]});

    return points;
}
