#include "cavepainter.h"

CavePainter::CavePainter(QWidget* parent, Cave* cave) : QWidget(parent) {
  resize(500, 500);
  move(20, 20);
  if (cave != nullptr) {
    this->cave = cave;
  } else {
    this->cave = new Cave("", {0, 0, 0});
  }
}

void CavePainter::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);

  if (!cave->isCorrect()) return;

  int rows = cave->getRows();
  int cols = cave->getCols();
  if (rows == 0 || cols == 0) return;

  double cell_width = width() / cols;
  double cell_height = height() / rows;
  auto cave_data = cave->getCaveData();

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (cave_data[row][col] == ALIVECELL) {
        painter.fillRect(col * cell_height, row * cell_width, cell_width, cell_height, Qt::black);
      } else if (cave_data[row][col] == DEATHCELL) {
        painter.fillRect(col * cell_height, row * cell_width, cell_width, cell_height, Qt::white);
      }
    }
  }
}
