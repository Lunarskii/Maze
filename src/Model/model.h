#ifndef A1_MAZE_MODEL_MODEL_H
#define A1_MAZE_MODEL_MODEL_H

#include <vector>
#include <fstream>
#include <sstream>

#include <iostream>

class Model {
public:
    using value_type = std::vector<std::vector<bool>>;

    static Model& GetInstance();
    void UploadMazeFromFile(std::string file_name);
    void PutALine(std::vector<std::vector<bool>>& vec, std::string& line);
    void printMaze();
    value_type& GetRightWalls();
    value_type& GetBottomWalls();
private:
    value_type right_walls_;
    value_type bottom_walls_;
};


#endif //  A1_MAZE_MODEL_MODEL_H
