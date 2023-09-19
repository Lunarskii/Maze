#ifndef A1_MAZE_MODEL_MAZE_MAZE_H_
#define A1_MAZE_MODEL_MAZE_MAZE_H_

#include "../file_manager.h"
#include "../generator.h"
#include "path_finder.h"

/**
 * @class Maze
 * @brief Сlass for processing mazes
 */
class Maze {
 public:
  /**
   * @brief Getting an instance of an object (can only be in a single quantity).
   * @return Reference to the object.
   */
  static Maze& GetInstance();

  /**
   * @brief Loads a maze from a text file.
   * @param file_name The path to the file.
   */
  void UploadMazeFromFile(std::string file_name);

  /**
   * @brief Generates a maze based on the given arguments (rows, cols).
   * @param rows Сan have values from 1 to 50.
   * @param cols Сan have values from 1 to 50.
   */
  void GenerateMaze(unsigned int rows, unsigned int cols);

  /**
   * @brief Saves the maze to a file.
   * @param file_name The name of the file where the maze will be saved.
   */
  void SaveMaze(std::string file_name);

  /**
   * @brief Returns the vector of points that make up the route from the first
   * point to the second.
   * @param from The point where the path starts from.
   * @param to The point where the path ends.
   * @return Vector of points that make up the route from the first point to the
   * second.
   */
  std::vector<Point> FindPath(Point from, Point to);

  /**
   * @brief Returns a reference to the MazeType.
   * @return Reference to the MazeType.
   */
  MazeType& GetMaze();

 private:
  MazeType maze_;
};

#endif  //  A1_MAZE_MODEL_MAZE_MAZE_H_
