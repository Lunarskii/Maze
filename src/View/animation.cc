#include "mainwindow.h"

void MainWindow::HideTabs_() 
{
    ui->tabWidgetMazeNCave->tabBar()->hide();
    ui->tabWidgetGenNLoad->tabBar()->hide();
    ui->tabWidgetItCave->tabBar()->hide();
    ui->tabWidgetDisplay->tabBar()->hide();
    ui->tabWidgetCaveLoad->tabBar()->hide();
}

void MainWindow::updateDisplayWidgets() 
{
    ui->tabWidgetDisplay->clear();
    ui->tabWidgetDisplay->addTab(maze_painter_, "Maze");
    ui->tabWidgetDisplay->addTab(cave_painter_, "Cave");
}

void MainWindow::switchTab(QAbstractButton *button) 
{
    int index = (ui->pushButtonCave == button) ? 1 : 0;

    if (ui->tabWidgetMazeNCave->currentIndex() != index) 
    {
        ui->tabWidgetMazeNCave->setCurrentIndex((ui->tabWidgetMazeNCave->currentIndex() + 1) % 2);
        ui->tabWidgetDisplay->setCurrentIndex((ui->tabWidgetDisplay->currentIndex() + 1) % 2);
        QString temp = ui->pushButtonCave->styleSheet();
        ui->pushButtonCave->setStyleSheet(ui->pushButtonMaze->styleSheet());
        ui->pushButtonMaze->setStyleSheet(temp);
    }
}

void MainWindow::on_pushButtonAuto_clicked() 
{
    QString temp = ui->pushButtonAuto->text();
    ui->pushButtonAuto->setText(ui->pushButtonStepByStep->text());
    ui->pushButtonStepByStep->setText(temp);
    ui->tabWidgetItCave->setCurrentIndex((ui->tabWidgetItCave->currentIndex() + 1) % 2);
}

void MainWindow::on_pushButtonLoadMaze_clicked() 
{
    QString temp = ui->pushButtonLoadMaze->text();
    ui->pushButtonLoadMaze->setText(ui->pushButtonGenerateMaze_big->text());
    ui->pushButtonGenerateMaze_big->setText(temp);
    ui->tabWidgetGenNLoad->setCurrentIndex((ui->tabWidgetGenNLoad->currentIndex() + 1) % 2);
    ui->mazeRows->setEnabled(!ui->mazeRows->isEnabled());
    ui->mazeCols->setEnabled(!ui->mazeCols->isEnabled());
}

void MainWindow::on_pushButtonGenerateMaze_small_clicked() 
{
    QString temp = ui->pushButtonGenerateMaze_small->text();
    ui->pushButtonGenerateMaze_small->setText(ui->pushButtonLoadFileMaze_big->text());
    ui->pushButtonLoadFileMaze_big->setText(temp);
    ui->tabWidgetCaveLoad->setCurrentIndex((ui->tabWidgetCaveLoad->currentIndex() + 1) % 2);
}