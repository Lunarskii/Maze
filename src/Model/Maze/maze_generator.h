#ifndef A1_MAZE_MODEL_MAZE_MAZE_GENERATOR_H_
#define A1_MAZE_MODEL_MAZE_MAZE_GENERATOR_H_

#include <vector>
#include <random>

class MazeGenerator
{
public:
    MazeGenerator(unsigned int rows, unsigned int cols);
    void GenerateMaze();
    std::vector<std::vector<bool>> GetRightWalls();
    std::vector<std::vector<bool>> GetBottomWalls();
    unsigned int GetRows();
    unsigned int GetCols();

private:
    bool RandomBool_();
    void AssignUniqueSet_();
    void PrepareANewSet_(int row);
    void AddRightWalls_(int row);
    void AddBottomWalls_(int row);
    void AddLastLine_();
    void MergeSets_(unsigned int first_set, unsigned int second_set);
    unsigned int GetNumberOfCellsWithoutBottomWall_(unsigned int set_number, unsigned int row);

    unsigned int rows_;
    unsigned int cols_;
    unsigned int counter_{ 0 };
    std::vector<int> line_;
    std::vector<std::vector<bool>> right_walls_;
    std::vector<std::vector<bool>> bottom_walls_;
};

#endif  // A1_MAZE_MODEL_MAZE_MAZE_GENERATOR_H_
