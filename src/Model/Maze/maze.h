#ifndef A1_MAZE_MODEL_MAZE_MAZE_H_
#define A1_MAZE_MODEL_MAZE_MAZE_H_

#define MIN_WIDGET_SIZE 1
#define MAX_WIDGET_SIZE 50

#include <vector>
#include <fstream>
#include <sstream>
#include <random> // BoolRandom()
#include "../FileReader/filereader.h"
#include "maze_generator.h"

#include <iostream>

class Maze
{
public:
    using maze_type = std::vector<std::vector<bool>>;

    static Maze& GetInstance();
    void UploadMazeFromFile(std::string file_name);
    void GenerateMaze(unsigned int rows, unsigned int cols);
    void SaveToFile(std::string file_name);
    maze_type& GetRightWalls();
    maze_type& GetBottomWalls();

private:
    maze_type right_walls_;
    maze_type bottom_walls_;
    unsigned int rows_;
    unsigned int cols_;

    void WriteDataToFile_(std::ofstream& file, maze_type& vec);
};


#endif //  A1_MAZE_MODEL_MAZE_MAZE_H_
