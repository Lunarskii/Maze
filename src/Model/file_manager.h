#ifndef A1_MAZE_MODEL_FILE_MANAGER_H_
#define A1_MAZE_MODEL_FILE_MANAGER_H_

#include <string>
#include <fstream>
#include <vector>
#include "data_types.h"

namespace s21
{

/**
* @class FileManager
* @brief Template class for saving and downloading caves and mazes from a file.
*/
template <TypesOfEntities T>
class FileManager final {};

template <>
/**
 * @class FileManager<kMaze>
 * @brief Class for working with files (uploading and saving a maze to a file).
 */
class FileManager<kMaze> final
{
public:
    /**
 * @brief Method for loading a maze from a file.
     * @return Returns the maze read from the file.
     * @param file_name Path to the file.
 */
    static MazeType Upload(std::string file_name)
    {
        MazeType maze;
        std::string line;
        std::ifstream file(file_name);

        if (file.is_open())
        {
            file >> maze.rows >> maze.cols;
            maze.right_walls.resize(maze.rows, std::vector<long>(maze.cols));
            maze.bottom_walls.resize(maze.rows, std::vector<long>(maze.cols));
            for (auto& i : maze.right_walls)
            {
                for (auto& j : i)
                {
                    file >> j;
                }
            }
            std::getline(file, line);
            for (auto& i : maze.bottom_walls)
            {
                for (auto& j : i)
                {
                    file >> j;
                }
            }
            file.close();
        }

        return maze;
    }

    /**
* @brief Method for saving the maze to a file.
 * @param file_name Name of the file where the maze will be saved.
 * @param maze Reference to the maze to be saved
*/
    static void Save(std::string file_name, MazeType& maze)
    {
        std::ofstream file(file_name);

        if (file.is_open())
        {
            file << maze.rows << " " << maze.cols;
            WriteDataToFile_(file, maze.right_walls);
            file << "\n";
            WriteDataToFile_(file, maze.bottom_walls);
            file.close();
        }
    }

private:
    static void WriteDataToFile_(std::ofstream& file, std::vector<std::vector<long>>& vec)
    {
        for (const auto& vectors : vec)
        {
            file << "\n";
            for (const auto& data : vectors)
            {
                file << data << " ";
            }
        }
    }
};

/**
 * @class FileManager<kCave>
 * @brief Class for working with files (loading a cave).
 */
template <>
class FileManager<kCave> final
{
public:
    /**
* @brief Method for loading a cave from a file.
 * @return Returns the cave read from the file.
 * @param file_name Path to the file.
*/
    static CaveType Upload(std::string file_name)
    {
        CaveType cave;
        std::ifstream file(file_name);

        if (file.is_open())
        {
            file >> cave.rows >> cave.cols;
            cave.cave_data.resize(cave.rows, std::vector<long>(cave.cols));
            for (auto& i : cave.cave_data)
            {
                for (auto& j : i)
                {
                    file >> j;
                }
            }
            file.close();
        }

        return cave;
    }
};

using MazeFileManager = FileManager<kMaze>;
using CaveFileManager = FileManager<kCave>;

} // namespace s21

#endif  // A1_MAZE_MODEL_FILE_MANAGER_H_
