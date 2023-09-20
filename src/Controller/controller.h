#ifndef A1_MAZE_CONTROLLER_CONTROLLER_H_
#define A1_MAZE_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"
#include "../View/mainwindow.h"

namespace s21
{

class Controller : public QObject
{
    Q_OBJECT
    
public:
    explicit Controller(MainWindow* v, Model* m);

private:
    Model* model_;
    MainWindow* view_;
};

} // namespace s21

#endif //  A1_MAZE_CONTROLLER_CONTROLLER_H_
