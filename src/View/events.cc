#include "mazewidget.h"

void MazeWidget::dragEnterEvent(QDragEnterEvent *event) 
{
    if (event->mimeData()->hasUrls()) event->acceptProposedAction();
}

void MazeWidget::dropEvent(QDropEvent *event) 
{
    const QMimeData *mime_data = event->mimeData();

    if (mime_data->hasUrls()) {
        QList<QUrl> url_list = mime_data->urls();
        QString file_path = url_list[0].toLocalFile();

        emit SetModel(file_path);

        event->acceptProposedAction();
    }
}