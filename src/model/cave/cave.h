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
  Cave();
  Cave(Cave& other);
  Cave(int width, int height, struct cellInfo cell_info);
  Cave(const std::string& filename, struct cellInfo cell_info);

  void setLimitBirth(int value);
  void setLimitDeath(int value);
  void setInitialChange(int value);

  int getRows();
  int getCols();
  int isCorrect();
  std::vector<std::vector<int>> getCaveData();

  bool HasNextGeneration();
  void CellularAutomation();

 private:
  bool LoadCaveFromFile(const std::string& filename);
  int CountAliveNeighbors(int row, int col);
  void ShuffleCaveData();

 private:
  std::vector<std::vector<int>> cave_data{};
  struct cellInfo cell_info {};
  int rows{}, cols{};
  bool is_correct{};
};
