#include "cave.h"

typename Cave::Cave& Cave::GetInstance() {
  static Cave instance;
  return instance;
}

void Cave::GenerateCave() {
  cave_ = CaveGenerator::Generate(cave_.rows, cave_.cols, cave_.initial_chance);
}

void Cave::SetLimitBirth(int value) {
  cave_.limit_birth = (value >= 0 && value <= 7) ? value : 0;
}

void Cave::SetLimitDeath(int value) {
  cave_.limit_death = (value >= 0 && value <= 7) ? value : 0;
}

void Cave::SetInitialChance(int value) {
  cave_.initial_chance = (value >= 0 && value <= 100) ? value : 0;
}

void Cave::SetCols(int cols) {
  cave_.cols = (cols >= 0 && cols <= 50) ? cols : 0;
}

void Cave::SetRows(int rows) {
  cave_.rows = (rows >= 0 && rows <= 50) ? rows : 0;
}

void Cave::UploadCaveFromFile(const std::string& file_name) {
  cave_ = CaveFileManager::Upload(file_name);

  if (!cave_.IsValid()) {
    throw std::exception();
  }
}

CaveType& Cave::GetCave() { return cave_; }

bool Cave::HasNextGeneration() {
  for (std::size_t i = 0; i < cave_.rows; ++i) {
    for (std::size_t j = 0; j < cave_.cols; ++j) {
      if (cave_.cave_data[i][j] == Cell::kAliveCell &&
          CountAliveNeighbors(i, j) < static_cast<int>(cave_.limit_death))
        return true;
      else if (cave_.cave_data[i][j] == Cell::kDeathCell &&
               CountAliveNeighbors(i, j) > static_cast<int>(cave_.limit_birth))
        return true;
    }
  }
  return false;
}

void Cave::CellularAutomation() {
  Cave cave_copy(*this);

  for (std::size_t i = 0; i < cave_.rows; ++i) {
    for (std::size_t j = 0; j < cave_.cols; ++j) {
      if (cave_.cave_data[i][j] == Cell::kAliveCell) {
        if (CountAliveNeighbors(i, j) < static_cast<int>(cave_.limit_death))
          cave_copy.cave_.cave_data[i][j] = Cell::kDeathCell;
      } else if (cave_.cave_data[i][j] == Cell::kDeathCell) {
        if (CountAliveNeighbors(i, j) > static_cast<int>(cave_.limit_birth))
          cave_copy.cave_.cave_data[i][j] = Cell::kAliveCell;
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
      if (row < 0 || col < 0 || row >= static_cast<int>(cave_.rows) ||
          col >= static_cast<int>(cave_.cols) ||
          cave_.cave_data[row][col] == Cell::kAliveCell)
        live_neighbors++;
    }
  }
  return live_neighbors;
}
