#include "cave.h"

typename Cave::Cave& Cave::GetInstance()
{
  static Cave instance;
  return instance;
}

void Cave::GenerateCave() {
    cave_ = CaveGenerator::Generate(cave_.rows, cave_.cols, cave_.initial_chance);
}

void Cave::setLimitBirth(int value) 
{
    cave_.limit_birth = (value >= 0 && value <= 7) ? value : 0;
}

void Cave::setLimitDeath(int value) 
{
    cave_.limit_death = (value >= 0 && value <= 7) ? value : 0;
}

void Cave::setInitialChance(int value) 
{
    cave_.initial_chance = (value >= 0 && value <= 100) ? value : 0;
}

void Cave::setSize(int value) 
{
    cave_.rows = cave_.cols = value;
}

void Cave::UploadCaveFromFile(const std::string& file_name) 
{
    cave_ = CaveFileManager::Upload(file_name);

    if (!cave_.IsValid())
    {
        throw std::exception();
    }
}

CaveType& Cave::GetCave() { return cave_; }

bool Cave::HasNextGeneration() 
{
    for (int i = 0; i < cave_.rows; ++i) {
        for (int j = 0; j < cave_.cols; ++j) {
            if (cave_.cave_data[i][j] == ALIVECELL && CountAliveNeighbors(i, j) < cave_.limit_death) return true;
            else if (cave_.cave_data[i][j] == DEATHCELL && CountAliveNeighbors(i, j) > cave_.limit_birth) return true;
        }
    }
    return false;
}

void Cave::CellularAutomation() 
{
    Cave cave_copy(*this);

    for (int i = 0; i < cave_.rows; ++i) 
    {
        for (int j = 0; j < cave_.cols; ++j) 
        {
            if (cave_.cave_data[i][j] == ALIVECELL) 
            {
                if (CountAliveNeighbors(i, j) < cave_.limit_death)
                cave_copy.cave_.cave_data[i][j] = DEATHCELL;
            } 
            else if (cave_.cave_data[i][j] == DEATHCELL) 
            {
                if (CountAliveNeighbors(i, j) > cave_.limit_birth)
                cave_copy.cave_.cave_data[i][j] = ALIVECELL;
            }
        }
    }

    cave_.cave_data = cave_copy.cave_.cave_data;
}

int Cave::CountAliveNeighbors(int i, int j) {
  int live_neighbors = 0;
  for (int row = i - 1; row <= i + 1; ++row) {
    for (int col = j - 1; col <= j + 1; ++col) {
      if (row == i && col == j) continue;
      if (row < 0 || col < 0 || row >= cave_.rows || col >= cave_.cols ||
          cave_.cave_data[row][col] == ALIVECELL)
        live_neighbors++;
    }
  }
  return live_neighbors;
}
