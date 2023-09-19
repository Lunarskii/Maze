#include "mainwindow.h"

void MainWindow::InitView_()
{
    connect(ui_->buttonGroupAppMode, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(SwitchApplicationTab_(QAbstractButton *)));
    
    connect(maze_painter_, &MazePainter::FindPath, this, [&](Point from, Point to)
    {
        emit FindPath(from, to);
    });
    connect(ui_->generateMazeButton, &QPushButton::clicked, this, &MainWindow::EmitGenerateMaze_);
    connect(ui_->saveMazeButton, &QPushButton::clicked, this, &MainWindow::EmitSaveMaze_);
    connect(ui_->openMazeButton, &QPushButton::clicked, this, &MainWindow::EmitUploadMaze_);

    connect(ui_->pushButtonNextStep, &QPushButton::clicked, this, [&]()
    {
        int limit_birth = ui_->caveBirthLimit->value();
        int limit_death = ui_->caveDeathLimit->value();
        emit NextGeneration(limit_birth, limit_death);
    });
    connect(ui_->pushButtonOpenCave, &QPushButton::clicked, this, &MainWindow::EmitUploadCave_);
    connect(ui_->pushButtonStart, &QPushButton::clicked, this, &MainWindow::CaveStartGeneration_);
    connect(ui_->pushButtonGenerateCave, &QPushButton::clicked, this, &MainWindow::EmitGenerateCave_);
}
