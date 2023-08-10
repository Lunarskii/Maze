#ifndef A1_MAZE_MODEL_MODEL_H
#define A1_MAZE_MODEL_MODEL_H

#include "Maze/maze.h"
#include "Cave/cave.h"
#include <QObject>

class Model : public QObject
{
    Q_OBJECT

public:
    using maze_type = Maze::maze_type;
    using cave_type = Maze::maze_type; // изменить типы данных
    static Model& GetInstance();

signals:
    void MazeReady(maze_type* right_walls, maze_type* bottom_walls);
    void MazeIsSaved();
    void CaveReady(cave_type* cave_data);
    void GenerationIsFinished();

public slots:
    void UploadMaze(std::string directory);
    void GenerateMaze(unsigned int rows, unsigned int cols);
    void SaveMaze(std::string directory);
    void UploadCave(std::string directory, int limit_birth, int limit_death);
    void GenerateCave(int limit_birth, int limit_death, int init_chance, int size);
    void NextGeneration();
    
private:
    Maze* maze_ { &Maze::GetInstance() };
    Cave* cave_ { &Cave::GetInstance() };
};

#endif //  A1_MAZE_MODEL_MODEL_H

