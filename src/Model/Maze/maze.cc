#include "maze.h"

typename Maze::Maze& Maze::GetInstance() 
{
    static Maze instance;
    return instance;
}

// не хватает проверки на размер лабика
void Maze::UploadMazeFromFile(std::string file_name)
{
    right_walls_.clear();
    bottom_walls_.clear();

    std::ifstream file(file_name);
    std::string line;

    if (!file.is_open())
    {
        throw std::exception();
        // std::cout << "file is not opened" << std::endl; // обработать исключение
    }

    std::getline(file, line);
    int x = 0;
    sscanf(line.c_str(), "%d", &x);

    for (int i = 1; std::getline(file, line); ++i)
    {
        if (i <= x)
        {
            PutALine_(right_walls_, line);
        }
        else
        {
            PutALine_(bottom_walls_, line);
        }
    }

    file.close();
}

void Maze::PutALine_(maze_type& vec, std::string& line)
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

void Maze::GeneratePerfectMaze(unsigned int rows, unsigned int cols)
{
    if (rows < MIN_WIDGET_SIZE || rows > MAX_WIDGET_SIZE || cols < MIN_WIDGET_SIZE || cols > MAX_WIDGET_SIZE)
    {
        throw std::exception(); // обработать исключение
    }

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

void Maze::SaveToFile(std::string file_name)
{
    std::ofstream file(file_name);

    if (!file.is_open()) 
    {
        throw std::exception(); // обработать исключение
        // std::cout << "file not created" << std::endl;
        // return;
    }

    file << rows_ << " " << cols_;
    WriteDataToFile_(file, right_walls_);
    file << "\n";
    WriteDataToFile_(file, bottom_walls_);
    file.close();
}

void Maze::WriteDataToFile_(std::ofstream& file, maze_type& vec)
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

void Maze::InitializingStartingValues_()
{
    right_walls_.clear();
    bottom_walls_.clear();
    right_walls_.resize(rows_, std::vector<bool>(cols_, 0));
    bottom_walls_.resize(rows_, std::vector<bool>(cols_, 0));
}

void Maze::CreateFirstRow_()
{
    side_line_.resize(cols_, 0);
}

void Maze::AssignUniqueSet_()
{
    for (int i = 0; i < cols_; ++i)
    {
        if (side_line_[i] == 0)
        {
            side_line_[i] = counter_++;
        }
    }
}

bool Maze::RandomBool_() // заменить на inline, если рандом оставлять мой
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(engine));
    // return std::rand() % 2 == 0;
}

void Maze::MergeSet_(int mutable_set, int set_number)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (side_line_[i] == mutable_set)
        {
            side_line_[i] = set_number;
        }
    }
}

int Maze::GetNumberOfCells_(int set_number)
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

void Maze::CheckedBottomWalls_(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (CalculateBottomWalls_(side_line_[i], row) == 0)
        {
            bottom_walls_[row][i] = false;
        }
    }
}

int Maze::CalculateBottomWalls_(int element, int row)
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

void Maze::PreparatingNewLine_(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (bottom_walls_[row][i] == true)
        {
            side_line_[i] = 0;
        }
    }
}

void Maze::AddingEndLine_()
{
    AssignUniqueSet_();
    AddingRightWalls_(rows_ - 1);
    CheckedEndLine_();
}

void Maze::CheckedEndLine_()
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

void Maze::AddingRightWalls_(int row)
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

void Maze::AddingBottomWalls(int row)
{
    for (int i = 0; i < cols_; ++i)
    {
        if (RandomBool_() == true && GetNumberOfCells_(side_line_[i]) > 1)
        {
            bottom_walls_[row][i] = true;
        }
    }
}

std::vector<std::vector<bool>>& Maze::GetRightWalls()
{
    return right_walls_;
}

std::vector<std::vector<bool>>& Maze::GetBottomWalls()
{
    return bottom_walls_;
}

void Maze::printMaze()
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
