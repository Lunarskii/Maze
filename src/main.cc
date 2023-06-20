#include "Controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MazeWidget w;
    Controller controller(&w);

    QObject::connect(&controller, SIGNAL(SolutionForMazeReady(value_type*, value_type*)), &w, SLOT(HandleSolution(value_type*, value_type*)));

    w.show();
    return app.exec();
}
