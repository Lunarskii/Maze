#include "cave.h"

Cave::Cave() = default;

Cave::Cave(const std::string& filename, struct cellInfo cell_info) {
  setLimitBirth(cell_info.limit_birth);
  setLimitDeath(cell_info.limit_death);
  setInitialChange(cell_info.initial_chance);
  is_correct = LoadCaveFromFile(filename);
}

Cave::Cave(int width, int height, struct cellInfo cell_info) {
  if (width > 500 || width < 1) width = 100;
  if (height > 500 || height < 1) height = 100;

  is_correct = true;
  rows = width;
  cols = height;
  cave_data.resize(rows, std::vector<int>(cols));

  int cell_count = cell_info.initial_chance / 100.0 * (rows * cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (cell_count > 0) {
        cave_data[i][j] = ALIVECELL;
        cell_count--;
      }
      else cave_data[i][j] = DEATHCELL;
    }
  }

  ShuffleCaveData();
}

void Cave::ShuffleCaveData() {
  std::vector<int> flatMatrix;
  for (const auto& row : cave_data) {
    flatMatrix.insert(flatMatrix.end(), row.begin(), row.end());
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(flatMatrix.begin(), flatMatrix.end(), gen);

  for (auto& row : cave_data) {
    for (auto& value : row) {
      value = flatMatrix.front();
      flatMatrix.erase(flatMatrix.begin());
    }
  }
}

Cave::Cave(Cave& other) {
  cave_data = other.getCaveData();
  cell_info = other.cell_info;
  rows = other.rows;
  cols = other.cols;
  is_correct = other.is_correct;
}

void Cave::setLimitBirth(int value) {
  if (value >= 0 && value <= 7)
    cell_info.limit_birth = value;
  else
    cell_info.limit_birth = 0;
}

void Cave::setLimitDeath(int value) {
  if (value >= 0 && value <= 7)
    cell_info.limit_death = value;
  else
    cell_info.limit_death = 0;
}

void Cave::setInitialChange(int value) {
  if (value >= 0 && value <= 100)
    cell_info.initial_chance = value;
  else
    cell_info.initial_chance = 0;
}

bool Cave::LoadCaveFromFile(const std::string& filename) {
  is_correct = true;

  if (filename.empty()) return false;

  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    return false;
  }

  file >> rows >> cols;

  if (rows < 1 || cols < 1 || rows > 50 || cols > 50) {
    file.close();
    return false;
  }

  cave_data.resize(rows, std::vector<int>(cols));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      file >> cave_data[i][j];
    }
  }

  file.close();
  return is_correct;
}

int Cave::getRows() { return rows; }

int Cave::getCols() { return cols; }

int Cave::isCorrect() { return is_correct; }

std::vector<std::vector<int>> Cave::getCaveData() { return cave_data; }

bool Cave::HasNextGeneration() {
    Cave cave_copy(*this);
    cave_copy.CellularAutomation();

    bool is_equal = cave_data == cave_copy.cave_data;
    return !is_equal;
}

void Cave::CellularAutomation() {
  Cave cave_copy(*this);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (cave_data[i][j] == ALIVECELL) {
        if (CountAliveNeighbors(i, j) < cell_info.limit_death)
          cave_copy.cave_data[i][j] = DEATHCELL;
      } else if (cave_data[i][j] == DEATHCELL) {
        if (CountAliveNeighbors(i, j) > cell_info.limit_birth)
          cave_copy.cave_data[i][j] = ALIVECELL;
      }
    }
  }

  cave_data = cave_copy.cave_data;
}

int Cave::CountAliveNeighbors(int i, int j) {
  int live_neighbors = 0;
  for (int row = i - 1; row <= i + 1; ++row) {
    for (int col = j - 1; col <= j + 1; ++col) {
      if (row == i && col == j) continue;
      if (row < 0 || col < 0 || row >= rows || col >= cols ||
          cave_data[row][col] == ALIVECELL)
        live_neighbors++;
    }
  }
  return live_neighbors;
}
