#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  cave = new Cave();
  initForm();

  connect(ui->buttonGroupAppMode, SIGNAL(buttonClicked(QAbstractButton *)),this, SLOT(switchTab(QAbstractButton *)));
}

MainWindow::~MainWindow() { delete ui; }

