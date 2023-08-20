#ifndef A1_MAZE_FILEREADER_FILEREADER_H_
#define A1_MAZE_FILEREADER_FILEREADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class FileReader
{
public:
    FileReader(std::string file_name);
    ~FileReader();
    void Upload(std::vector<std::vector<bool>>* first = nullptr, std::vector<std::vector<bool>>* second = nullptr);
private:
    void PutALine_(std::vector<std::vector<bool>>& vec, std::string& line);

    std::ifstream* file_;
    unsigned int rows_;
    unsigned int cols_;
};

#endif  // A1_MAZE_FILEREADER_FILEREADER_H_
