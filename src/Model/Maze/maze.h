#ifndef A1_MAZE_MODEL_MAZE_MAZE_H_
#define A1_MAZE_MODEL_MAZE_MAZE_H_

#define MIN_WIDGET_SIZE 1
#define MAX_WIDGET_SIZE 50

#include <vector>
#include <fstream>
#include <sstream>
#include <random> // BoolRandom()
#include "generate.h"

#include <iostream>

class Maze
{
public:
    using maze_type = std::vector<std::vector<bool>>;

    static Maze& GetInstance();
    void UploadMazeFromFile(std::string file_name);
    void GeneratePerfectMaze(unsigned int rows, unsigned int cols);
    void SaveToFile(std::string file_name);
    maze_type& GetRightWalls();
    maze_type& GetBottomWalls();

private:
    maze_type right_walls_;
    maze_type bottom_walls_;
    std::vector<int> side_line_;
    unsigned int rows_;
    unsigned int cols_;
    int counter_{1};

    void PutALine_(maze_type& vec, std::string& line);
    void WriteDataToFile_(std::ofstream& file, maze_type& vec);
    void InitializingStartingValues_();
    void CreateFirstRow_();
    void AssignUniqueSet_();
    bool RandomBool_();
    void MergeSet_(int mutable_set, int set_number);
    int GetNumberOfCells_(int set_number);
    void CheckedBottomWalls_(int row);
    int CalculateBottomWalls_(int element, int row);
    void PreparatingNewLine_(int row);
    void AddingEndLine_();
    void CheckedEndLine_();
    void AddingRightWalls_(int row);
    void AddingBottomWalls(int row);



    void printMaze();
};


#endif //  A1_MAZE_MODEL_MAZE_MAZE_H_
