#include "controller.h"

void Controller::SetFileName_(const QString& file_name)
{
    model_->UploadMazeFromFile(file_name.toStdString());
    emit SolutionForMazeReady(&model_->GetRightWalls(), &model_->GetBottomWalls());
}

void Controller::SetDimension_(int rows, int cols)
{
    model_->GeneratePerfectMaze(rows, cols);
    emit SolutionForMazeReady(&model_->GetRightWalls(), &model_->GetBottomWalls());
}

void Controller::SaveMazeToFile_(const QString& file_name)
{
    model_->SaveToFile(file_name.toStdString());
}
