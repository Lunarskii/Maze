#ifndef CAVEPAINTER_H
#define CAVEPAINTER_H

#include <QPainter>
#include <QWidget>
#include <QtWidgets>
#include <string>

#include "cave.h"

class CavePainter : public QWidget {
 public:
  CavePainter(QWidget* parent = nullptr, Cave* cave = nullptr);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  Cave* cave;
};

#endif  // CAVEPAINTER_H
