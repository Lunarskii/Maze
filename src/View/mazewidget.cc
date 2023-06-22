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
    painter->begin(this);

    painter->setPen(QPen(Qt::black, 2)); // Цвет стен и толщина стен
    painter->setBrush(Qt::white); // Цвет клеток
    painter->drawRect(ui->mazeWidget->x(), ui->mazeWidget->y(), ui->mazeWidget->width(), ui->mazeWidget->height());


    if (right_walls_ != nullptr)
    {
        PaintMaze_();
    }


    painter->end();
}

void MazeWidget::PaintMaze_()
{
    double cell_width = static_cast<double>(ui->mazeWidget->width()) / (*right_walls_)[0].size();
    double cell_height = static_cast<double>(ui->mazeWidget->height()) / right_walls_->size();

    for (int i = 0; i != right_walls_->size(); ++i)
    {
        for (int j = 0; j != (*right_walls_)[i].size(); ++j)
        {
            if ((*right_walls_)[i][j] == 1)
            {
                double x = (j + 1) * cell_width + ui->mazeWidget->x();
                double y = i * cell_height + ui->mazeWidget->y();
                painter->drawLine(QPointF(x, y), QPointF(x, y + cell_height));
            }
        }
    }

    for (int i = 0; i != bottom_walls_->size(); ++i)
    {
        for (int j = 0; j != (*bottom_walls_)[i].size(); ++j)
        {
            if ((*bottom_walls_)[i][j] == 1)
            {
                double x = j * cell_width + ui->mazeWidget->x();
                double y = (i + 1) * cell_height + ui->mazeWidget->y();
                painter->drawLine(QPointF(x, y), QPointF(x + cell_width, y));
            }
        }
    }
}

void MazeWidget::on_uploadMazeModel_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, ("Select Maze"), "../mazes/", "Text Files (*.txt)");

    if (file_path != "")
    {
        emit SetModel(file_path);
    }
}

void MazeWidget::on_generateMaze_clicked()
{
    int rows = ui->rows_line->text().toInt();
    int cols = ui->cols_line->text().toInt();
    emit SetDimension(rows, cols);
}


void MazeWidget::on_pushButton_clicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Save Maze", "../mazes/", "Text Files (*.txt)");
    emit SaveMazeToFile(file_path);
}

