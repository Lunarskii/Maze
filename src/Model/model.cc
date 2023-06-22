#include "model.h"

void Model::UploadMazeFromFile(std::string file_name)
{
    right_walls_.clear();
    bottom_walls_.clear();

    std::ifstream file(file_name);
    std::string line;

    if (!file.is_open())
    {
        std::cout << "file is not opened" << std::endl; // обработать ошибку
        return;
    }

    std::getline(file, line);
    int x = 0;
    sscanf(line.c_str(), "%d", &x);

    for (int i = 1; std::getline(file, line); ++i)
    {
        if (i <= x)
        {
            PutALine(right_walls_, line);
        }
        else
        {
            PutALine(bottom_walls_, line);
        }
    }

    file.close();
}

void Model::PutALine(std::vector<std::vector<bool>>& vec, std::string& line)
{
    if (!line.empty())
    {
        std::vector<bool> one_line;
        std::istringstream iss(line);
        bool number = 0;

        while (iss >> number)
        {
            one_line.push_back(number);
        }
        vec.push_back(one_line);
    }
}

void Model::GeneratePerfectMaze(unsigned int rows, unsigned int cols)
{
    rows_ = rows;
    cols_ = cols;

    InitializingStartingValues_();
    CreateFirstRow_();
    for (int i = 0; i < rows_ - 1; ++i)
    {
        AssignUniqueSet_();
        AddingRightWalls_(i);
        AddingBottomWalls(i);
        CheckedBottomWalls_(i);
        PreparatingNewLine_(i);
    }
    AddingEndLine_();
    side_line_.clear();
}

void Model::SaveToFile(std::string file_name)
{
    std::ofstream file(file_name);

    if (!file.is_open()) 
    {
        std::cout << "file not created" << std::endl;
        return;
    }

    file << rows_ << " " << cols_;
    WriteDataToFile_(file, right_walls_);
    file << "\n";
    WriteDataToFile_(file, bottom_walls_);
    file.close();
}

void Model::WriteDataToFile_(std::ofstream& file, value_type& vec)
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

void Model::InitializingStartingValues_()
{
    right_walls_.clear();
    bottom_walls_.clear();
    right_walls_.resize(rows_, std::vector<bool>(cols_, 0));
    bottom_walls_.resize(rows_, std::vector<bool>(cols_, 0));
}

void Model::CreateFirstRow_()
{
    side_line_.resize(cols_, 0);
}

void Model::AssignUniqueSet_()
{
    for (int i = 0; i < cols_; ++i)
    {
        if (side_line_[i] == 0)
        {
            side_line_[i] = counter_++;
        }
    }
}

bool Model::RandomBool_() // заменить на inline, если рандом оставлять мой
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(engine));
    // return std::rand() % 2 == 0;
}

void Model::MergeSet_(int mutable_set, int set_number)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (side_line_[i] == mutable_set)
        {
            side_line_[i] = set_number;
        }
    }
}

int Model::GetNumberOfCells_(int set_number)
{
    int count = 0;

    for (int i = 0; i < cols_; ++i)
    {
        if (side_line_[i] == set_number)
        {
            ++count;
        }
    }

    return count;
}

void Model::CheckedBottomWalls_(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (CalculateBottomWalls_(side_line_[i], row) == 0)
        {
            bottom_walls_[row][i] = false;
        }
    }
}

int Model::CalculateBottomWalls_(int element, int row)
{
    int count = 0;

    for (int i = 0; i < cols_; ++i)
    {
        if (side_line_[i] == element && bottom_walls_[row][i] == false)
        {
            ++count;
        }
    }

    return count;
}

void Model::PreparatingNewLine_(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (bottom_walls_[row][i] == true)
        {
            side_line_[i] = 0;
        }
    }
}

void Model::AddingEndLine_()
{
    AssignUniqueSet_();
    AddingRightWalls_(rows_ - 1);
    CheckedEndLine_();
}

void Model::CheckedEndLine_()
{
    for (int i = 0; i < cols_ - 1; ++i)
    {
        if (side_line_[i] != side_line_[i + 1])
        {
            right_walls_[rows_ - 1][i] = false;
            MergeSet_(side_line_[i + 1], side_line_[i]);
        }
        bottom_walls_[rows_ - 1][i] = true;
    }
    bottom_walls_[rows_ - 1][cols_ - 1] = true;
}

void Model::AddingRightWalls_(int row)
{
    for (int i = 0; i < cols_ - 1; ++i)
    {
        if (RandomBool_() == true || side_line_[i] == side_line_[i + 1])
        {
            right_walls_[row][i] = true;
        }
        else
        {
            MergeSet_(side_line_[i + 1], side_line_[i]);
        }
    }
    right_walls_[row][cols_ - 1] = true;
}

void Model::AddingBottomWalls(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (RandomBool_() == true && GetNumberOfCells_(side_line_[i]) > 1)
        {
            bottom_walls_[row][i] = true;
        }
    }
}

std::vector<std::vector<bool>>& Model::GetRightWalls()
{
    return right_walls_;
}

std::vector<std::vector<bool>>& Model::GetBottomWalls()
{
    return bottom_walls_;
}

void Model::printMaze()
{
    std::cout << "right_walls: " << std::endl << std::endl;
    for (int i = 0; i < right_walls_.size(); ++i)
    {
        for (int j = 0; j < right_walls_[i].size(); ++j)
        {
            std::cout << right_walls_[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "bottom_walls: " << std::endl << std::endl;
    for (int i = 0; i < bottom_walls_.size(); ++i)
    {
        for (int j = 0; j < bottom_walls_[i].size(); ++j)
        {
            std::cout << bottom_walls_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

typename Model::Model& Model::GetInstance() 
{
    static Model instance;
    return instance;
}
