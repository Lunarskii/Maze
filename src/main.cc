#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("Maze");
  w.show();
  return a.exec();
}
