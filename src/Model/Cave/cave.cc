#include "cave.h"

typename Cave::Cave& Cave::GetInstance()
{
  static Cave instance;
  return instance;
}

void Cave::GenerateRandomCave() {
  if (cave_data_.size() != rows) {
    cave_data_.resize(rows, std::vector<bool>(cols));
  }

  std::vector<bool> flatMatrix(rows * cols);
  int alive_cell_count = cell_info.initial_chance / 100.0 * rows * cols;
  for (int i = 0; i < alive_cell_count; ++i) flatMatrix[i] = ALIVECELL;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(flatMatrix.begin(), flatMatrix.end(), gen);

  int k = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cave_data_[i][j] = flatMatrix[k++];
    }
  }
}

void Cave::setLimitBirth(int value) 
{
    cell_info.limit_birth = (value >= 0 && value <= 7) ? value : 0;
}

void Cave::setLimitDeath(int value) 
{
    cell_info.limit_death = (value >= 0 && value <= 7) ? value : 0;
}

void Cave::setInitialChance(int value) 
{
    cell_info.initial_chance = (value >= 0 && value <= 100) ? value : 0;
}

void Cave::setSize(int value) {
  rows = cols = value;
}

void Cave::UploadCaveFromFile(const std::string& filename) 
{
    cave_data_.clear();

    std::ifstream file(filename);

    if (!file.is_open()) 
    {
        throw std::exception();
    }

    file >> rows >> cols;

    if (rows < MIN_WIDGET_SIZE || rows > MAX_WIDGET_SIZE || cols < MIN_WIDGET_SIZE || cols > MAX_WIDGET_SIZE) 
    {
        file.close();
        throw std::exception();
    }

    cave_data_.resize(rows, std::vector<bool>(cols));

    int x = 0;
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            file >> x;
            cave_data_[i][j] = x;
        }
    }

    file.close();
}

std::vector<std::vector<bool>>& Cave::GetCaveData() { return cave_data_; }

bool Cave::HasNextGeneration() 
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cave_data_[i][j] == ALIVECELL && CountAliveNeighbors(i, j) < cell_info.limit_death) return true;
            else if (cave_data_[i][j] == DEATHCELL && CountAliveNeighbors(i, j) > cell_info.limit_birth) return true;
        }
    }
    return false;
}

void Cave::CellularAutomation() 
{
    Cave cave_copy(*this);

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            if (cave_data_[i][j] == ALIVECELL) 
            {
                if (CountAliveNeighbors(i, j) < cell_info.limit_death)
                cave_copy.cave_data_[i][j] = DEATHCELL;
            } 
            else if (cave_data_[i][j] == DEATHCELL) 
            {
                if (CountAliveNeighbors(i, j) > cell_info.limit_birth)
                cave_copy.cave_data_[i][j] = ALIVECELL;
            }
        }
    }

    cave_data_ = cave_copy.cave_data_;
}

int Cave::CountAliveNeighbors(int i, int j) {
  int live_neighbors = 0;
  for (int row = i - 1; row <= i + 1; ++row) {
    for (int col = j - 1; col <= j + 1; ++col) {
      if (row == i && col == j) continue;
      if (row < 0 || col < 0 || row >= rows || col >= cols ||
          cave_data_[row][col] == ALIVECELL)
        live_neighbors++;
    }
  }
  return live_neighbors;
}
