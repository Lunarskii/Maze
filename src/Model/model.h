#ifndef A1_MAZE_MODEL_MODEL_H
#define A1_MAZE_MODEL_MODEL_H

#include "Maze/maze.h"
#include "Cave/cave.h"
#include <QObject>

class Model : public QObject
{
    Q_OBJECT

public:
    static Model& GetInstance();

signals:
    void MazeReady(MazeType* maze);
    void PathReady(std::vector<Point> path);
    void MazeIsSaved();
    void CaveReady(CaveType* cave);
    void GenerationIsFinished();

public slots:
    void UploadMaze(std::string file_name);
    void GenerateMaze(unsigned int rows, unsigned int cols);
    void SaveMaze(std::string file_name);
    void FindPath(Point from, Point to);
    void UploadCave(std::string file_name, int limit_birth, int limit_death);
    void GenerateCave(int init_chance, unsigned int rows, unsigned int cols);
    void NextGeneration(int limit_birth, int limit_death);
    
private:
    Maze* maze_ { &Maze::GetInstance() };
    Cave* cave_ { &Cave::GetInstance() };
};

#endif //  A1_MAZE_MODEL_MODEL_H

