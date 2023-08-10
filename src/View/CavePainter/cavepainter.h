#ifndef A1_MAZE_VIEW_CAVEPAINTER_CAVEPAINTER_H_
#define A1_MAZE_VIEW_CAVEPAINTER_CAVEPAINTER_H_

#include <QPainter>
#include <QWidget>
#include <QtWidgets>
#include <string>

class CavePainter : public QWidget 
{
public:
    CavePainter(QWidget* parent = nullptr);
    void SetCaveData(std::vector<std::vector<bool>>* cave_data);

private:
    void paintEvent(QPaintEvent*) override;
    inline bool IsAliveCell_(bool cell);

    std::vector<std::vector<bool>>* cave_data_{ nullptr };
};

#endif  // A1_MAZE_VIEW_CAVEPAINTER_CAVEPAINTER_H_