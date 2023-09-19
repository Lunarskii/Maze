#ifndef A1_MAZE_MODEL_MAZE_PATH_FINDER_H_
#define A1_MAZE_MODEL_MAZE_PATH_FINDER_H_

#include <vector>
#include <limits>
#include <algorithm>
#include "../data_types.h"

class PathFinder
{
public:
    PathFinder(const MazeType& maze, Point from, Point to);
    std::vector<Point> FindPath();

private:
    MazeType maze_;
    Point from_;
    Point to_;
    std::vector<std::vector<int>> length_map_;
    std::vector<Point> wave_;
    std::vector<Point> old_wave_;
    int wave_number_;
    int empty_value_;

    bool IsValidPoints_(Point from, Point to);
    bool StepWave_();
    std::vector<Point> MakePath_();
    std::vector<SidePoint> GetVectorOfMoves_(int row, int col);
};

#endif  // A1_MAZE_MODEL_MAZE_PATH_FINDER_H_
