#include "model.h"

typename Model::Model& Model::GetInstance()
{
    static Model instance;
    return instance;
}

void Model::UploadMaze(std::string directory)
{
    maze_->UploadMazeFromFile(directory);
    emit MazeReady(&maze_->GetRightWalls(), &maze_->GetBottomWalls());
}

void Model::GenerateMaze(unsigned int rows, unsigned int cols)
{
    maze_->GenerateMaze(rows, cols);
    emit MazeReady(&maze_->GetRightWalls(), &maze_->GetBottomWalls());
}

void Model::SaveMaze(std::string directory)
{
    maze_->SaveToFile(directory);
    emit MazeIsSaved();
}

void Model::UploadCave(std::string directory, int limit_birth, int limit_death)
{
    cave_->setLimitBirth(limit_birth);
    cave_->setLimitDeath(limit_death);
    cave_->UploadCaveFromFile(directory);
    emit CaveReady(&cave_->GetCaveData());
}

void Model::GenerateCave(int limit_birth, int limit_death, int init_chance, int size)
{
    cave_->setLimitBirth(limit_birth);
    cave_->setLimitDeath(limit_death);
    cave_->setInitialChance(init_chance);
    cave_->setSize(size);
    cave_->GenerateRandomCave();
    emit CaveReady(&cave_->GetCaveData());
}

void Model::NextGeneration()
{
    cave_->CellularAutomation();
    emit CaveReady(&cave_->GetCaveData());

    if (!cave_->HasNextGeneration())
    {
        emit GenerationIsFinished();
    }
}
