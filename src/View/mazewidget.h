#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MazeWidget; }
QT_END_NAMESPACE

class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    using value_type = std::vector<std::vector<bool>>;

    MazeWidget(QWidget *parent = nullptr);  
    ~MazeWidget();

signals:
    void SetModel(QString file_name);

private slots:
    void HandleSolution(value_type* right_walls, value_type* bottom_walls);
    void on_uploadMazeModel_clicked();

private:
    Ui::MazeWidget *ui;
    QPainter *painter;
    value_type* right_walls_{nullptr};
    value_type* bottom_walls_{nullptr};

    void PaintMaze_();
    void paintEvent(QPaintEvent*) override;

    // Events
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif // MAZEWIDGET_H
