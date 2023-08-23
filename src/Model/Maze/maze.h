#ifndef A1_MAZE_MODEL_MAZE_MAZE_H_
#define A1_MAZE_MODEL_MAZE_MAZE_H_

#include "../file_manager.h"
#include "../generator.h"

class Maze
{
public:
    static Maze& GetInstance();
    void UploadMazeFromFile(std::string file_name);
    void GenerateMaze(unsigned int rows, unsigned int cols);
    void SaveMaze(std::string file_name);
    MazeType& GetMaze();

private:
    MazeType maze_;
};


#endif //  A1_MAZE_MODEL_MAZE_MAZE_H_
