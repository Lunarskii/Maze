#include "cavepainter.h"

CavePainter::CavePainter(QWidget* parent) 
    : QWidget(parent)
{}

void CavePainter::SetCaveData(std::vector<std::vector<bool>>* cave_data)
{
    cave_data_ = cave_data;
}

inline bool CavePainter::IsAliveCell_(bool cell)
{
    return cell;
}

void CavePainter::paintEvent(QPaintEvent*) 
{
    if (cave_data_ != nullptr)
    {
        QPainter painter(this);
        
        unsigned int rows = cave_data_->size();
        unsigned int cols = (*cave_data_)[0].size();
        double cell_width = this->width() / cols;
        double cell_height = this->height() / rows;

        for (int row = 0; row < rows; ++row) 
        {
            for (int col = 0; col < cols; ++col) 
            {
                if (IsAliveCell_((*cave_data_)[row][col])) 
                {
                    painter.fillRect(col * cell_width, row * cell_height, cell_width, cell_height, Qt::black);
                } 
                else if (!IsAliveCell_((*cave_data_)[row][col])) 
                {
                    painter.fillRect(col * cell_width, row * cell_height, cell_width, cell_height, Qt::white);
                }
            }
        }

        painter.end();
    }
}