#ifndef A1_MAZE_MODEL_CAVE_CAVE_H_
#define A1_MAZE_MODEL_CAVE_CAVE_H_

#define MIN_WIDGET_SIZE 1
#define MAX_WIDGET_SIZE 50

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

#define DEATHCELL 0
#define ALIVECELL 1

struct cellInfo {
  int limit_birth{};
  int limit_death{};
  int initial_chance{};
};

class Cave {
public:
    static Cave& GetInstance();

    void setLimitBirth(int value);
    void setLimitDeath(int value);
    void setInitialChance(int value);

    int isCorrect();
    std::vector<std::vector<bool>>& GetCaveData();

    bool HasNextGeneration();
    void CellularAutomation();
    void UploadCaveFromFile(const std::string& filename);
    void ShuffleCaveData();

private:
    int CountAliveNeighbors(int row, int col);

private:
    std::vector<std::vector<bool>> cave_data_ {};
    struct cellInfo cell_info {};
    int rows {}, cols {};
    bool is_correct {};
};

#endif  // A1_MAZE_MODEL_CAVE_CAVE_H_

