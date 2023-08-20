#include "mazepainter.h"

MazePainter::MazePainter(QWidget* parent)
    : QWidget(parent)
    , painter(new QPainter) 
{}

MazePainter::~MazePainter()
{
    delete painter;
}

inline bool MazePainter::WallExists_(bool cell)
{
    return cell;
}

void MazePainter::SetRightWalls(maze_type* right_walls)
{
    right_walls_ = right_walls;
    cell_width = static_cast<double>(this->width()) / (*right_walls_)[0].size();
}

void MazePainter::SetBottomWalls(maze_type* bottom_walls)
{
    bottom_walls_ = bottom_walls;
    cell_height = static_cast<double>(this->height()) / right_walls_->size();
}

void MazePainter::TurnOffClicks()
{
    left_btn_pressed_ = false;
    right_btn_pressed_ = false;
}

void MazePainter::paintEvent(QPaintEvent*)
{
    painter->begin(this);

    if (right_walls_ != nullptr && bottom_walls_ != nullptr)
    {
        PaintMaze_();
        PaintSquares_();
    }

    painter->end();
}

void MazePainter::PaintMaze_()
{
    painter->setPen(QPen(Qt::white, 2)); // Цвет стен и толщина стен
    painter->setBrush(Qt::black); // Цвет клеток
    painter->drawRect(this->x(), this->y(), this->width(), this->height());
    
    for (int i = 0; i != right_walls_->size(); ++i)
    {
        for (int j = 0; j != (*right_walls_)[i].size(); ++j)
        {
            if (WallExists_((*right_walls_)[i][j]))
            {
                double x = (j + 1) * cell_width + this->x();
                double y = i * cell_height + this->y();
                painter->drawLine(QPointF(x, y), QPointF(x, y + cell_height));
            }
            if (WallExists_((*bottom_walls_)[i][j]))
            {
                double x = j * cell_width + this->x();
                double y = (i + 1) * cell_height + this->y();
                painter->drawLine(QPointF(x, y), QPointF(x + cell_width, y));
            }
        }
    }
}

void MazePainter::PaintSquares_()
{
    if (left_btn_pressed_)
    {
        painter->setPen(QPen(Qt::red, 1, Qt::DashLine));
        PaintSquare_(click_pos_left_);
    }
    if (right_btn_pressed_)
    {
        painter->setPen(QPen(Qt::yellow, 1, Qt::DashLine));
        PaintSquare_(click_pos_right_);
    }
}

void MazePainter::PaintSquare_(QPoint& position)
{
    int cell_x = 0;
    int cell_y = 0;

    GetCellNumbers_(position, cell_x, cell_y);

    double margin_width = cell_width / 10;
    double margin_height = cell_height / 10;
    double x = (cell_x * cell_width) + margin_width + this->x();
    double y = (cell_y * cell_height) + margin_height + this->y();

    painter->drawRect(x, y, cell_width - margin_width * 2, cell_height - margin_height * 2);
}

void MazePainter::GetCellNumbers_(QPoint& position, int& x, int& y)
{
    x = std::floor((position.x() - this->x()) / cell_width);
    y = std::floor((position.y() - this->y()) / cell_height);
}

bool MazePainter::ClickInWidget_(QPoint position)
{
    return
        position.x() >= this->x()
        && 
        position.x() <= this->x() + this->width()
        && 
        position.y() >= this->y()
        && 
        position.y() <= this->y() + this->height()
    ;
}

bool MazePainter::ClickInSameCell_(QPoint& p1, QPoint& p2)
{
    int cell_x1 = 0, cell_y1 = 0, cell_x2 = 0, cell_y2 = 0;

    GetCellNumbers_(p1, cell_x1, cell_y1);
    GetCellNumbers_(p2, cell_x2, cell_y2);

    return cell_x1 == cell_x2 && cell_y1 == cell_y2;
}

void MazePainter::mousePressEvent(QMouseEvent *event) {
    QPoint pos = event->pos();

    if (!ClickInWidget_(pos))
    {
        return;
    }
    if (event->button() == Qt::LeftButton) 
    {
        if (left_btn_pressed_ == true && ClickInSameCell_(click_pos_left_, pos))
        {
            left_btn_pressed_ = false;
        }
        else
        {
            left_btn_pressed_ = true;
            click_pos_left_ = pos;
        }
    } 
    else if (event->button() == Qt::RightButton) 
    {
        if (right_btn_pressed_ == true && ClickInSameCell_(click_pos_right_, pos))
        {
            right_btn_pressed_ = false;
        }
        else
        {
            right_btn_pressed_ = true;
            click_pos_right_ = pos;
        }
    }
    update();
}
