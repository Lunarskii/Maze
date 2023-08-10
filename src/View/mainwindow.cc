#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , maze_painter_(new MazePainter(this))
   , cave_painter_(new CavePainter(this))
{
    ui->setupUi(this);
    setAcceptDrops(true);
    HideTabs_();
    updateDisplayWidgets();
    connect(ui->buttonGroupAppMode, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(switchTab(QAbstractButton *)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete maze_painter_;
    delete cave_painter_;
}

void MainWindow::DrawMaze(maze_type* right_walls, maze_type* bottom_walls)
{
    maze_painter_->SetRightWalls(right_walls);
    maze_painter_->SetBottomWalls(bottom_walls);
    maze_painter_->TurnOffClicks();
    maze_painter_->update();
}

void MainWindow::DrawCave(cave_type* cave_data)
{
    cave_painter_->SetCaveData(cave_data);
    cave_painter_->update();
}

void MainWindow::on_pushButtonOpenMaze_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, ("Select Maze"), "../mazes/", "Text Files (*.txt)");

    if (!file_path.isEmpty())
    {
        emit UploadMaze(file_path.toStdString());
    }
}

void MainWindow::on_pushButtonGenerateMaze_clicked()
{
    unsigned int rows = ui->mazeRows->text().toInt();
    unsigned int cols = ui->mazeCols->text().toInt();

    emit GenerateMaze(rows, cols);
}


void MainWindow::on_pushButtonSaveMaze_clicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Save Maze", "../mazes/", "Text Files (*.txt)");
    emit SaveMaze(file_path.toStdString());
}

// После генерации пещеры эволюция неправильно работает
void MainWindow::on_pushButtonOpenCave_clicked() 
{
    QString file_path = QFileDialog::getOpenFileName(this, "Select cave", "./", "Cave files (*.txt)");

    if (!file_path.isEmpty()) 
    {
        int limit_birth = ui->lineEditCaveLifeLim->text().toInt();
        int limit_death = ui->lineEditCaveDeathLim->text().toInt();
        emit UploadCave(file_path.toStdString(), limit_birth, limit_death);
    }
}

void MainWindow::on_pushButtonGenerateCave_clicked() 
{
    int limit_birth = ui->lineEditCaveLifeLim->text().toInt();
    int limit_death = ui->lineEditCaveDeathLim->text().toInt();
    int init_chance = ui->lineEditCaveInitChance->text().toInt();
    int size = ui->lineEditCaveSize->text().toInt();
    emit GenerateCave(limit_birth, limit_death, init_chance, size);
}

void MainWindow::on_pushButtonNextStep_clicked() 
{
    emit NextGeneration();
}

void MainWindow::on_pushButtonStart_clicked() 
{
    if (timer == nullptr) 
    {
        ui->pushButtonStart->setStyleSheet(ui->pushButtonStart->styleSheet().replace("background-color: #D9D9D9","background-color: #509171",Qt::CaseInsensitive));
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [&] 
        {
            on_pushButtonNextStep_clicked();
        });
        timer->start(ui->lineEditCaveDelay->text().toInt());
    }
}

void MainWindow::on_pushButtonStop_clicked() 
{
    if (timer != nullptr) 
    {
        timer->stop();
        ui->pushButtonStart->setStyleSheet(ui->pushButtonStop->styleSheet());
        delete timer;
        timer = nullptr;
    }
}

