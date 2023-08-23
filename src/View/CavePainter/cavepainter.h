#ifndef A1_MAZE_VIEW_CAVEPAINTER_CAVEPAINTER_H_
#define A1_MAZE_VIEW_CAVEPAINTER_CAVEPAINTER_H_

#include <QPainter>
#include <QWidget>
#include <QtWidgets>
#include <string>
#include "../../Model/data_types.h"

class CavePainter : public QWidget 
{
public:
    CavePainter(QWidget* parent = nullptr);
    void SetCave(CaveType* cave);

private:
    void paintEvent(QPaintEvent*) override;
    inline bool IsAliveCell_(bool cell);

    CaveType* cave_{ nullptr };
};

#endif  // A1_MAZE_VIEW_CAVEPAINTER_CAVEPAINTER_H_