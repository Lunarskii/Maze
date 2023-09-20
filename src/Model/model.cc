#include "model.h"

namespace s21
{

typename Model::Model& Model::GetInstance()
{
    static Model instance;
    return instance;
}

void Model::UploadMaze(std::string file_name)
{
    try
    {      
        maze_->UploadMazeFromFile(file_name);
        emit MazeReady(&maze_->GetMaze());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Model::GenerateMaze(unsigned int rows, unsigned int cols)
{
    try
    {
        maze_->GenerateMaze(rows, cols);
        emit MazeReady(&maze_->GetMaze());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Model::SaveMaze(std::string file_name)
{
    try
    {
        maze_->SaveMaze(file_name);
        emit MazeIsSaved();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Model::FindPath(Point from, Point to)
{
    emit PathReady(maze_->FindPath(from, to));
}

void Model::UploadCave(std::string file_name, int limit_birth, int limit_death)
{
    try
    {
        cave_->SetLimitBirth(limit_birth);
        cave_->SetLimitDeath(limit_death);
        cave_->UploadCaveFromFile(file_name);
        emit CaveReady(&cave_->GetCave());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Model::GenerateCave(int init_chance, unsigned int rows, unsigned int cols)
{
    try
    {
        cave_->SetInitialChance(init_chance);
        cave_->SetRows(rows);
        cave_->SetCols(cols);
        cave_->GenerateCave();
        emit CaveReady(&cave_->GetCave());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Model::NextGeneration(int limit_birth, int limit_death)
{
    cave_->SetLimitBirth(limit_birth);
    cave_->SetLimitDeath(limit_death);
    cave_->CellularAutomation();
    emit CaveReady(&cave_->GetCave());

    if (!cave_->HasNextGeneration())
    {
        emit GenerationIsFinished();
    }
}

} // namespace s21
