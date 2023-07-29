#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QIntValidator>
#include <QMainWindow>
#include <QTabBar>
#include <chrono>
#include <thread>

#include "./ui_mainwindow.h"
#include "../model/cave/cavepainter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

// animation
 private slots:
    void switchTab(QAbstractButton *button);
    void on_pushButtonAuto_clicked();
    void on_pushButtonLoadMaze_clicked();
    void on_pushButtonGenerateMaze_small_clicked();
private:
    void initForm();
    void updateDisplayWidgets();

// cave process
private slots:
  void on_pushButtonOpenCave_clicked();
  void on_pushButtonGenerateCave_clicked();

  void on_pushButtonNextStep_clicked();
  void on_pushButtonStart_clicked();
  void on_pushButtonStop_clicked();

  void on_lineEditCaveLifeLim_textChanged(const QString &arg1);
  void on_lineEditCaveDeathLim_textChanged(const QString &arg1);
  void on_lineEditCaveInitChance_textChanged(const QString &arg1);

  void on_lineEditCaveSize_textChanged(const QString &arg1);
private:
    void updateCellInfo(int arg, bool is_life);

 private:
  Ui::MainWindow *ui;
  CavePainter *cave_painter;
  Cave *cave;

  QTimer *timer;
  bool generate_status;
};
#endif  // MAINWINDOW_H
