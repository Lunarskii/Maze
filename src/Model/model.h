#ifndef A1_MAZE_MODEL_MODEL_H
#define A1_MAZE_MODEL_MODEL_H

#include <vector>
#include <fstream>
#include <sstream>
#include <random> // BoolRandom()

#include <iostream>

class Model {
public:
    using value_type = std::vector<std::vector<bool>>;

    static Model& GetInstance();
    void UploadMazeFromFile(std::string file_name);
    void PutALine(std::vector<std::vector<bool>>& vec, std::string& line);
    void printMaze();
    value_type& GetRightWalls();
    value_type& GetBottomWalls();

    void GeneratePerfectMaze(unsigned int rows, unsigned int cols);
    void SaveToFile(std::string file_name);

private:
    value_type right_walls_;
    value_type bottom_walls_;
    std::vector<int> side_line_;
    unsigned int rows_;
    unsigned int cols_;
    int counter_{1};

    void WriteDataToFile_(std::ofstream& file, value_type& vec);
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
};


#endif //  A1_MAZE_MODEL_MODEL_H
