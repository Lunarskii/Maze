#ifndef A1_MAZE_VIEW_MAZEPAINTER_MAZEPAINTER_H_
#define A1_MAZE_VIEW_MAZEPAINTER_MAZEPAINTER_H_

#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <cmath>
#include "../../Model/data_types.h"

namespace s21
{

class MazePainter : public QWidget
{
    Q_OBJECT

public:
    MazePainter(QWidget* parent = nullptr);
    ~MazePainter();

    void SetMaze(MazeType* maze);
    void SetPath(std::vector<Point> path);
    void TurnOffClicks();

signals:
    void FindPath(Point from, Point to);

private:
    QPainter *painter;
    MazeType* maze_{ nullptr };
    std::vector<Point> path_;
    double cell_width_{};
    double cell_height_{};

    inline bool WallExists_(long cell);
    void paintEvent(QPaintEvent*) override;
    void PaintMaze_();
    void PaintSquares_();
    void PaintSquare_(QPoint& position);
    void PaintPath_();
    void GetCellNumbers_(QPoint& position, int& x, int& y);
    bool ClickInSameCell_(QPoint& p1, QPoint& p2);

    void mousePressEvent(QMouseEvent* event) override;
    QPoint click_pos_left_;
    QPoint click_pos_right_;
    bool left_btn_pressed_{ false };
    bool right_btn_pressed_{ false };
};

} // namespace s21

#endif  // A1_MAZE_VIEW_MAZEPAINTER_MAZEPAINTER_H_
