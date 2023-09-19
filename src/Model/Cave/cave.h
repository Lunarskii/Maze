#ifndef A1_MAZE_MODEL_CAVE_CAVE_H_
#define A1_MAZE_MODEL_CAVE_CAVE_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../file_manager.h"
#include "../generator.h"

/**
 * @class Cave
 * @brief Сlass for generating, loading from a file, and evolving caves
 */
class Cave {
 public:
  /**
   * @brief Getting an instance of an object (can only be in a single quantity).
   * @return Reference to the object.
   */
  static Cave& GetInstance();

  /**
   * @brief Sets the birth limit for each cell.
   * @param value Сan have values from 0 to 7.
   */
  void SetLimitBirth(int value);

  /**
   * @brief Sets the death limit for each cell.
   * @param value Сan have values from 0 to 7.
   */
  void SetLimitDeath(int value);

  /**
   * @brief Sets the chance of initial initialization for each cell.
   * @param value Сan have values from 0 to 100.
   */
  void SetInitialChance(int value);

  /**
   * @brief Sets the rows of the cave.
   * @param rows Сan have values from 1 to 50.
   */
  void SetRows(int rows);

  /**
   * @brief Sets the columns of the cave.
   * @param cols Сan have values from 1 to 50.
   */
  void SetCols(int cols);

  /**
   * @brief Returns a reference to the CaveType.
   * @return Reference to the CaveType.
   */
  CaveType& GetCave();

  /**
   * @brief Checks for the presence of the next generations at the cave
   * @return True if the cave has at least one generation, otherwise false.
   */
  bool HasNextGeneration();

  /**
   * @brief Performs one iteration of cave evolution.
   */
  void CellularAutomation();

  /**
   * @brief Loads a cave from a text file.
   * @param file_name The path to the file.
   */
  void UploadCaveFromFile(const std::string& file_name);

  /**
   * Generates a cave according to previously set parameters (limit of death,
   * limit of death, init. chance).
   */
  void GenerateCave();

 private:
  /**
   * @brief Counts the number of living cells among 8 neighboring cells.
   * @param row The row of the cell that counts the number of neighbors.
   * @param col The column of the cell that counts the number of neighbors.
   * @return The number of neighbors for a particular cell.
   */
  int CountAliveNeighbors(int row, int col);

 private:
  /**
   * @brief Stores cave cells and their parameters.
   */
  CaveType cave_;
};

#endif  // A1_MAZE_MODEL_CAVE_CAVE_H_
