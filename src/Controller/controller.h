#ifndef A1_MAZE_CONTROLLER_CONTROLLER_H_
#define A1_MAZE_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"
#include "../View/mainwindow.h"

class Controller : public QObject
{
    Q_OBJECT
    
public:
    explicit Controller(MainWindow* v, Model* model);

private:
    Model* model_;
    MainWindow* view_;
};

#endif //  A1_MAZE_CONTROLLER_CONTROLLER_H_
