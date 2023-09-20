#include "Controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    s21::MainWindow w;
    s21::Model* m = &s21::Model::GetInstance();
    s21::Controller controller(&w, m);
    return app.exec();
}
