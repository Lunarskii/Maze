#ifndef A1_MAZE_VIEW_MAZEPAINTER_MAZEPAINTER_H_
#define A1_MAZE_VIEW_MAZEPAINTER_MAZEPAINTER_H_

#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <cmath>

class MazePainter : public QWidget
{
    using maze_type = std::vector<std::vector<bool>>;

public:
    MazePainter(QWidget* parent = nullptr);
    ~MazePainter();

    void SetRightWalls(maze_type* right_walls);
    void SetBottomWalls(maze_type* bottom_walls);
    void TurnOffClicks();

private:
    QPainter *painter;
    maze_type* right_walls_{ nullptr };
    maze_type* bottom_walls_{ nullptr };
    double cell_width {};
    double cell_height {};

    inline bool WallExists_(bool cell);
    void paintEvent(QPaintEvent*) override;
    void PaintMaze_();
    void PaintSquares_();
    void PaintSquare_(QPoint& position);
    void GetCellNumbers_(QPoint& position, int& x, int& y);
    bool ClickInWidget_(QPoint position);
    bool ClickInSameCell_(QPoint& p1, QPoint& p2);

    void mousePressEvent(QMouseEvent* event) override;
    QPoint click_pos_left_;
    QPoint click_pos_right_;
    bool left_btn_pressed_{ false };
    bool right_btn_pressed_{ false };
};

#endif  // A1_MAZE_VIEW_MAZEPAINTER_MAZEPAINTER_H_
