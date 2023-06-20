#include "mazewidget.h"
#include "./ui_mazewidget.h"

MazeWidget::MazeWidget(QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::MazeWidget)
   , painter(new QPainter)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MazeWidget::~MazeWidget()
{
    delete painter;
    delete ui;
}

void MazeWidget::HandleSolution(value_type* right_walls, value_type* bottom_walls)
{
    right_walls_ = right_walls;
    bottom_walls_ = bottom_walls;
    update();
}

void MazeWidget::paintEvent(QPaintEvent*)
{
    // заменить на дополнительный виджет, чтобы не размещать в окне
    painter->begin(this);

    painter->setPen(Qt::black); // Цвет стен
    painter->setBrush(Qt::white); // Цвет клеток
    painter->drawRect(0, 0, 500, 500); // 0 0 - начальные координаты виджета, надо запихать в отдельный
    // заменить число 500 на константную переменную размера виджета лабиринта


    if (right_walls_ != nullptr)
    {
        PaintMaze_();
    }


    painter->end();
}

void MazeWidget::PaintMaze_()
{
    int cell_width = 500 / right_walls_[0].size();
    int cell_height = 500 / right_walls_->size(); // заменить число 500 на константную переменную размера виджета лабиринта

    for (int i = 0; i != right_walls_->size(); ++i)
    {
        for (int j = 0; j != (*right_walls_)[i].size(); ++j)
        {
            if ((*right_walls_)[i][j] == 1)
            {
                int x = (j + 1) * cell_width;
                int y = i * cell_height;
                painter->drawLine(x, y, x, y + cell_height);
            }
        }
    }

    for (int i = 0; i != bottom_walls_->size(); ++i)
    {
        for (int j = 0; j != (*bottom_walls_)[i].size(); ++j)
        {
            if ((*bottom_walls_)[i][j] == 1)
            {
                int x = j * cell_width;
                int y = (i + 1) * cell_height;
                painter->drawLine(x, y, x + cell_width, y);
            }
        }
    }
}

void MazeWidget::on_uploadMazeModel_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, ("Select Maze"), "../models/", "Text Files (*.txt)");

    if (file_path != "")
    {
        emit SetModel(file_path);
    }
}
