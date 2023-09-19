#include "mazepainter.h"

MazePainter::MazePainter(QWidget* parent)
    : QWidget(parent)
    , painter(new QPainter) 
{}

MazePainter::~MazePainter()
{
    delete painter;
}

inline bool MazePainter::WallExists_(long cell)
{
    return cell == 1;
}

void MazePainter::SetMaze(MazeType* maze)
{
    maze_ = maze;
    cell_width_ = static_cast<double>(this->width()) / maze_->cols;
    cell_height_ = static_cast<double>(this->height()) / maze_->rows;
}

void MazePainter::SetPath(std::vector<Point> path)
{
    path_ = path;
}

void MazePainter::TurnOffClicks()
{
    left_btn_pressed_ = false;
    right_btn_pressed_ = false;
}

void MazePainter::paintEvent(QPaintEvent*)
{
    painter->begin(this);

    if (maze_ != nullptr)
    {
        PaintMaze_();
        PaintSquares_();
        PaintPath_();
    }

    painter->end();
}

void MazePainter::PaintMaze_()
{
    painter->setPen(QPen(Qt::white, 2));
    painter->setBrush(Qt::black);
    painter->drawRect(this->x(), this->y(), this->width(), this->height());
    
    for (int i = 0; i < maze_->rows; ++i)
    {
        for (int j = 0; j < maze_->cols; ++j)
        {
            if (WallExists_((maze_->right_walls)[i][j]))
            {
                double x = (j + 1) * cell_width_;
                double y = i * cell_height_;
                painter->drawLine(QPointF(x, y), QPointF(x, y + cell_height_));
            }
            if (WallExists_((maze_->bottom_walls)[i][j]))
            {
                double x = j * cell_width_;
                double y = (i + 1) * cell_height_;
                painter->drawLine(QPointF(x, y), QPointF(x + cell_width_, y));
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

    double margin_width = cell_width_ / 10;
    double margin_height = cell_height_ / 10;
    double x = (cell_x * cell_width_) + margin_width;
    double y = (cell_y * cell_height_) + margin_height;

    painter->drawRect(x, y, cell_width_ - margin_width * 2, cell_height_ - margin_height * 2);
}

void MazePainter::PaintPath_()
{
    if (path_.size() > 1 && left_btn_pressed_ && right_btn_pressed_)
    {
        painter->setPen(QPen(Qt::blue, 1));
        double margin_width = cell_width_ / 2.0;
        double margin_height = cell_height_ / 2.0;


    }
}

void MazePainter::GetCellNumbers_(QPoint& position, int& x, int& y)
{
    x = std::floor(position.x() / cell_width_);
    y = std::floor(position.y() / cell_height_);
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

    if (left_btn_pressed_ && right_btn_pressed_)
    {
        int cell_x_left = 0;
        int cell_y_left = 0;
        int cell_x_right = 0;
        int cell_y_right = 0;

        GetCellNumbers_(click_pos_left_, cell_x_left, cell_y_left);
        GetCellNumbers_(click_pos_right_, cell_x_right, cell_y_right);

        emit FindPath(Point{cell_y_left, cell_x_left}, Point{cell_y_right, cell_x_right});
    }
}
