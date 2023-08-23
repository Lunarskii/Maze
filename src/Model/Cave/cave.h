#ifndef A1_MAZE_MODEL_CAVE_CAVE_H_
#define A1_MAZE_MODEL_CAVE_CAVE_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "../file_manager.h"
#include "../generator.h"

class Cave {
public:
    static Cave& GetInstance();

    void setLimitBirth(int value);
    void setLimitDeath(int value);
    void setInitialChance(int value);
    void setSize(int value);

    CaveType& GetCave();

    bool HasNextGeneration();
    void CellularAutomation();
    void UploadCaveFromFile(const std::string& file_name);
    void GenerateCave();

private:
    int CountAliveNeighbors(int row, int col);

private:
    CaveType cave_;
};

#endif  // A1_MAZE_MODEL_CAVE_CAVE_H_

