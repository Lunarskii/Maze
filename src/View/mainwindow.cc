#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui_(new Ui::MainWindow)
   , maze_painter_(new MazePainter(this))
   , cave_painter_(new CavePainter(this))
{
    ui_->setupUi(this);
    setAcceptDrops(true);
    HideTabs_();
    UpdateDisplayWidgets_();
    InitView_();
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete maze_painter_;
    delete cave_painter_;
}

void MainWindow::DrawMaze(MazeType* maze)
{
    maze_painter_->SetMaze(maze);
    maze_painter_->TurnOffClicks();
    maze_painter_->update();
}

void MainWindow::DrawPath(std::vector<Point> path)
{
    maze_painter_->SetPath(path);
    maze_painter_->update();
}

void MainWindow::DrawCave(CaveType* cave)
{
    cave_painter_->SetCave(cave);
    cave_painter_->update();
}

void MainWindow::EmitUploadMaze_()
{
    QString file_path = QFileDialog::getOpenFileName(this, ("Select Maze"), "../mazes/", "Text Files (*.txt)");

    if (!file_path.isEmpty())
    {
        emit UploadMaze(file_path.toStdString());
    }
}

void MainWindow::EmitGenerateMaze_()
{
    unsigned int rows = ui_->mazeRows->text().toInt();
    unsigned int cols = ui_->mazeCols->text().toInt();

    emit GenerateMaze(rows, cols);
}


void MainWindow::EmitSaveMaze_()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Save Maze", "../mazes/", "Text Files (*.txt)");

    if (!file_path.isEmpty())
    {
        emit SaveMaze(file_path.toStdString());
    }
}

// После генерации пещеры эволюция неправильно работает
void MainWindow::EmitUploadCave_() 
{
    QString file_path = QFileDialog::getOpenFileName(this, "Select cave", "./", "Cave files (*.txt)");

    if (!file_path.isEmpty()) 
    {
        int limit_birth = ui_->caveBirthLimit->value();
        int limit_death = ui_->caveDeathLimit->value();
        emit UploadCave(file_path.toStdString(), limit_birth, limit_death);
    }
}

void MainWindow::EmitGenerateCave_()
{
    int limit_birth = ui_->caveBirthLimit->value();
    int limit_death = ui_->caveDeathLimit->value();
    int init_chance = ui_->caveStartInit->value();

    // int init_chance = ui->lineEditCaveInitChance->text().toInt();
    // int size = ui->lineEditCaveSize->text().toInt();
    // emit GenerateCave(limit_birth, limit_death, init_chance, size);
}

void MainWindow::CaveStartGeneration_() 
{
    if (timer_ == nullptr) 
    {
        ui_->pushButtonStart->setStyleSheet(ui_->pushButtonStart->styleSheet().replace("background-color: #D9D9D9","background-color: #509171",Qt::CaseInsensitive));
        timer_ = new QTimer(this);
        connect(timer_, &QTimer::timeout, this, [&] 
        {
            emit NextGeneration();
        });
        timer_->start(ui_->caveDelay->value());
    }
}

void MainWindow::CaveStopGeneration_() 
{
    if (timer_ != nullptr) 
    {
        timer_->stop();
        ui_->pushButtonStart->setStyleSheet(ui_->pushButtonStop->styleSheet());
        delete timer_;
        timer_ = nullptr;
    }
}

