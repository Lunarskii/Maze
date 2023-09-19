#include "model.h"

typename Model::Model& Model::GetInstance()
{
    static Model instance;
    return instance;
}

void Model::UploadMaze(std::string file_name)
{
    maze_->UploadMazeFromFile(file_name);
    emit MazeReady(&maze_->GetMaze());
}

void Model::GenerateMaze(unsigned int rows, unsigned int cols)
{
    maze_->GenerateMaze(rows, cols);
    emit MazeReady(&maze_->GetMaze());
}

void Model::SaveMaze(std::string file_name)
{
    maze_->SaveMaze(file_name);
    emit MazeIsSaved();
}

void Model::FindPath(Point from, Point to)
{
    emit PathReady(maze_->FindPath(from, to));
}

void Model::UploadCave(std::string file_name, int limit_birth, int limit_death)
{
    cave_->SetLimitBirth(limit_birth);
    cave_->SetLimitDeath(limit_death);
    cave_->UploadCaveFromFile(file_name);
    emit CaveReady(&cave_->GetCave());
}

void Model::GenerateCave(int limit_birth, int limit_death, int init_chance, unsigned int rows, unsigned int cols)
{
    cave_->SetLimitBirth(limit_birth);
    cave_->SetLimitDeath(limit_death);
    cave_->SetInitialChance(init_chance);
    cave_->SetRows(rows);
    cave_->SetCols(cols);
    cave_->GenerateCave();
    emit CaveReady(&cave_->GetCave());
}

void Model::NextGeneration()
{
    cave_->CellularAutomation();
    emit CaveReady(&cave_->GetCave());

    if (!cave_->HasNextGeneration())
    {
        emit GenerationIsFinished();
    }
}
