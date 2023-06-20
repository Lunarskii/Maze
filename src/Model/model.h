#ifndef PROJECT_MODEL_H
#define PROJECT_MODEL_H

#include <vector>
#include <fstream>
#include <sstream>

#include <iostream>

#include "../matrix/logic/s21_matrix.h"

class Model {
public:
    Model() = default;
    void UploadMazeFromFile(std::string file_name);
    void PutALine(std::vector<std::vector<bool>>& vec, std::string& line);
    void printMaze();
private:
    std::vector<std::vector<bool>> right_walls_;
    std::vector<std::vector<bool>> bottom_walls_;
};


#endif //  PROJECT_MODEL_H
