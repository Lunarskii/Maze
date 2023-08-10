#include "cave.h"

typename Cave::Cave& Cave::GetInstance()
{
  static Cave instance;
  return instance;
}

// Cave::Cave() = default;

// Cave::Cave(const std::string& filename, struct cellInfo cell_info) {
//   setLimitBirth(cell_info.limit_birth);
//   setLimitDeath(cell_info.limit_death);
//   setInitialChance(cell_info.initial_chance);
//   is_correct = LoadCaveFromFile(filename);
// }

// Cave::Cave(int width, int height, struct cellInfo cell_info) {
//   if (width > 500 || width < 1) width = 100;
//   if (height > 500 || height < 1) height = 100;

//   is_correct = true;
//   rows = width;
//   cols = height;
//   cave_data.resize(rows, std::vector<bool>(cols));

//   int cell_count = cell_info.initial_chance / 100.0 * (rows * cols);

//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       if (cell_count > 0) {
//         cave_data[i][j] = ALIVECELL;
//         cell_count--;
//       }
//       else cave_data[i][j] = DEATHCELL;
//     }
//   }

//   ShuffleCaveData();
// }

// Cave::Cave(Cave& other) {
//   cave_data = other.getCaveData();
//   cell_info = other.cell_info;
//   rows = other.rows;
//   cols = other.cols;
//   is_correct = other.is_correct;
// }

void Cave::ShuffleCaveData() {
    std::vector<int> flatMatrix;
    for (const auto& row : cave_data_) 
    {
        flatMatrix.insert(flatMatrix.end(), row.begin(), row.end());
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(flatMatrix.begin(), flatMatrix.end(), gen);

    for (auto& row : cave_data_) 
    {
        for (auto value : row) 
        {
            value = flatMatrix.front();
            flatMatrix.erase(flatMatrix.begin());
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

int Cave::isCorrect() { return is_correct; }

std::vector<std::vector<bool>>& Cave::GetCaveData() { return cave_data_; }

bool Cave::HasNextGeneration() 
{
    Cave cave_copy(*this);
    cave_copy.CellularAutomation();

    bool is_equal = cave_data_ == cave_copy.cave_data_;
    return !is_equal;
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