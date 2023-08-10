#ifndef A1_MAZE_VIEW_MAINWINDOW_H_
#define A1_MAZE_VIEW_MAINWINDOW_H_

#include <QAbstractButton>
#include <QIntValidator>
#include <QMainWindow>
#include <QTabBar>
#include <QPainter>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <chrono>
#include <thread>


#include <iostream>
#include <cmath>

#include "MazePainter/mazepainter.h"
#include "CavePainter/cavepainter.h"
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    using maze_type = std::vector<std::vector<bool>>;
    using cave_type = std::vector<std::vector<bool>>;

    MainWindow(QWidget* parent = nullptr);  
    ~MainWindow();

signals:
    void UploadMaze(std::string file_name);
    void GenerateMaze(unsigned int rows, unsigned int cols);
    void SaveMaze(std::string file_name);
    void UploadCave(std::string file_name, int limit_birth, int limit_death);
    void GenerateCave(int limit_birth, int limit_death, int init_chance, int size);
    void NextGeneration();

public slots:
    void DrawMaze(maze_type* right_walls, maze_type* bottom_walls);
    void DrawCave(cave_type* cave_data);
    void on_pushButtonStop_clicked();
    
private slots:
    // maze process
    void on_pushButtonOpenMaze_clicked();
    void on_pushButtonGenerateMaze_clicked();
    void on_pushButtonSaveMaze_clicked();

    // animation
    void switchTab(QAbstractButton *button);
    void HideTabs_();
    void updateDisplayWidgets();
    void on_pushButtonAuto_clicked();
    void on_pushButtonLoadMaze_clicked();
    void on_pushButtonGenerateMaze_small_clicked();

    // cave process
    void on_pushButtonNextStep_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonOpenCave_clicked();
    void on_pushButtonGenerateCave_clicked();

private:
    Ui::MainWindow *ui;
    MazePainter* maze_painter_{ nullptr };
    CavePainter* cave_painter_{ nullptr };
    QTimer *timer{ nullptr };

    // Events
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif  // A1_MAZE_VIEW_MAINWINDOW_H_

