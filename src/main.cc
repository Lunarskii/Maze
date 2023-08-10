#include "Controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    Model* m = &Model::GetInstance();
    Controller controller(&w, m);

    return app.exec();
}
