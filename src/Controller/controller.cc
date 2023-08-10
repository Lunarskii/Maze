#include "controller.h"

Controller::Controller(MainWindow* v, Model* model)
    : model_(model)
    , view_(v)
{
    view_->show();
    view_->setWindowTitle("Maze");

    connect(view_, &MainWindow::UploadMaze, model_, &Model::UploadMaze);
    connect(view_, &MainWindow::GenerateMaze, model_, &Model::GenerateMaze);
    connect(view_, &MainWindow::SaveMaze, model_, &Model::SaveMaze);
    connect(model_, &Model::MazeReady, view_, &MainWindow::DrawMaze);

    connect(view_, &MainWindow::UploadCave, model_, &Model::UploadCave);
    connect(view_, &MainWindow::GenerateCave, model_, &Model::GenerateCave);
    connect(view_, &MainWindow::NextGeneration, model_, &Model::NextGeneration);
    connect(model_, &Model::CaveReady, view_, &MainWindow::DrawCave);
    connect(model_, &Model::GenerationIsFinished, view_, &MainWindow::on_pushButtonStop_clicked);
}
