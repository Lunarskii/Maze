#include "controller.h"

void Controller::SetFileName_(const QString& file_name)
{
    model_->UploadMazeFromFile(file_name.toStdString());
    emit SolutionForMazeReady(&model_->GetRightWalls(), &model_->GetBottomWalls());
}
