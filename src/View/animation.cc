#include "mainwindow.h"

namespace s21
{

void MainWindow::HideTabs_() 
{
    ui_->tabWidgetMazeNCave->tabBar()->hide();
    ui_->tabWidgetDisplay->tabBar()->hide();
}

void MainWindow::UpdateDisplayWidgets_()
{
    ui_->tabWidgetDisplay->clear();
    ui_->tabWidgetDisplay->addTab(maze_painter_, "Maze");
    ui_->tabWidgetDisplay->addTab(cave_painter_, "Cave");
}

void MainWindow::SwitchApplicationTab_(QAbstractButton *button)
{
    int index = (ui_->pushButtonCave == button) ? 1 : 0;

    if (ui_->tabWidgetMazeNCave->currentIndex() != index)
    {
        ui_->tabWidgetMazeNCave->setCurrentIndex((ui_->tabWidgetMazeNCave->currentIndex() + 1) % 2);
        ui_->tabWidgetDisplay->setCurrentIndex((ui_->tabWidgetDisplay->currentIndex() + 1) % 2);
        QString temp = ui_->pushButtonCave->styleSheet();
        ui_->pushButtonCave->setStyleSheet(ui_->pushButtonMaze->styleSheet());
        ui_->pushButtonMaze->setStyleSheet(temp);
    }
}

} // namespace s21
