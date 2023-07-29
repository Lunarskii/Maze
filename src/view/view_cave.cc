#include "mainwindow.h"

// После генерации пещеры эволюция неправильно работает

void MainWindow::on_pushButtonOpenCave_clicked() {
  QString filepath = QFileDialog::getOpenFileName(this, ("Select cave"), "./",
                                                  "Cave files (*.txt)");

  if (!filepath.isEmpty()) {
    cave = new Cave(filepath.toStdString(), {0, 0, 0});
    cave->setLimitBirth(ui->lineEditCaveLifeLim->text().toInt());
    cave->setLimitDeath(ui->lineEditCaveDeathLim->text().toInt());

    cave_painter = new CavePainter(this, cave);
    updateDisplayWidgets();
  }
}

void MainWindow::on_pushButtonGenerateCave_clicked() {
  cellInfo cellInfo = {ui->lineEditCaveLifeLim->text().toInt(),
                       ui->lineEditCaveDeathLim->text().toInt(),
                       ui->lineEditCaveInitChance->text().toInt()};

  int size = ui->lineEditCaveSize->text().toInt();
  cave = new Cave(size, size, cellInfo);
  cave_painter = new CavePainter(this, cave);

  updateDisplayWidgets();
}

void MainWindow::on_pushButtonNextStep_clicked() {
  if (cave->HasNextGeneration()) {
    cave->CellularAutomation();
    cave_painter->update();
  }
}

void MainWindow::on_pushButtonStart_clicked() {
  if (!generate_status) {
    ui->pushButtonStart->setStyleSheet(ui->pushButtonStart->styleSheet().replace("background-color: #D9D9D9","background-color: #509171",Qt::CaseInsensitive));
    generate_status = true;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&] {
        if (cave->HasNextGeneration()) {
          cave->CellularAutomation();
          cave_painter->update();
        } else {
          ui->pushButtonStart->setStyleSheet(ui->pushButtonStop->styleSheet());
          timer->stop();
          delete timer;
          timer = nullptr;
          generate_status = false;
        }
    });
    timer->start(ui->lineEditCaveDelay->text().toInt());
  }
}

void MainWindow::on_pushButtonStop_clicked() {
  if (generate_status) {
    timer->stop();
    delete timer;
    timer = nullptr;
    generate_status = false;
  }
  ui->pushButtonStart->setStyleSheet(ui->pushButtonStop->styleSheet());
}

void MainWindow::on_lineEditCaveLifeLim_textChanged(const QString &arg1) {
  updateCellInfo(arg1.toInt(), true);
}

void MainWindow::on_lineEditCaveDeathLim_textChanged(const QString &arg1) {
  updateCellInfo(arg1.toInt(), false);
}

void MainWindow::on_lineEditCaveInitChance_textChanged(const QString &arg1)
{
  int initial_change = arg1.toInt();

  if (initial_change < 0) initial_change = 0;
  else if (initial_change > 100) initial_change = 100;

  ui->lineEditCaveInitChance->setText(QString::number(initial_change));
  cave->setInitialChange(initial_change);
}

void MainWindow::on_lineEditCaveSize_textChanged(const QString &arg1) {
  int value = arg1.toInt();
  if (value < 0) value = 1;
  if (value > 500) value = 500;

  ui->lineEditCaveSize->setText(QString::number(value));
  ui->labelCaveSize->setText(QString::number(value));
}

void MainWindow::updateCellInfo(int arg, bool is_life) {
  if (arg < 0) {
    arg = 0;
  } else if (arg > 7) {
    arg = 7;
  }

  if (is_life) {
    ui->lineEditCaveLifeLim->setText(QString::number(arg));
    cave->setLimitBirth(arg);
  } else {
    ui->lineEditCaveDeathLim->setText(QString::number(arg));
    cave->setLimitDeath(arg);
  }
}