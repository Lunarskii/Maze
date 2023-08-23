#include "cavepainter.h"

CavePainter::CavePainter(QWidget* parent) 
    : QWidget(parent)
{}

void CavePainter::SetCave(CaveType* cave)
{
    cave_ = cave;
}

inline bool CavePainter::IsAliveCell_(bool cell)
{
    return cell;
}

void CavePainter::paintEvent(QPaintEvent*) 
{
    if (cave_ != nullptr)
    {
        QPainter painter(this);
        double cell_width = this->width() / cave_->cols;
        double cell_height = this->height() / cave_->rows;

        for (int row = 0; row < cave_->rows; ++row) 
        {
            for (int col = 0; col < cave_->cols; ++col) 
            {
                if (IsAliveCell_((cave_->cave_data)[row][col])) 
                {
                    painter.fillRect(col * cell_width, row * cell_height, cell_width, cell_height, Qt::black);
                } 
                else if (!IsAliveCell_((cave_->cave_data)[row][col])) 
                {
                    painter.fillRect(col * cell_width, row * cell_height, cell_width, cell_height, Qt::white);
                }
            }
        }

        painter.end();
    }
}