#ifndef A1_MAZE_CONTROLLER_CONTROLLER_H_
#define A1_MAZE_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"
#include "../View/mazewidget.h"

class Controller : public QObject
{
    Q_OBJECT
    
public:
    using value_type = Model::value_type;

    explicit Controller(MazeWidget* v)
        : model_(&Model::GetInstance())
        , view_(v)
    {
        connect(view_, SIGNAL(SetModel(QString)), this, SLOT(SetFileName_(QString)));
    }

signals:
    void SolutionForMazeReady(value_type* right_walls, value_type* bottom_walls);

private slots:
    void SetFileName_(const QString& file_name);

private:
    Model* model_;
    MazeWidget* view_;
};

#endif //  A1_MAZE_CONTROLLER_CONTROLLER_H_
