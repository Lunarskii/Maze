#include "mainwindow.h"

void MainWindow::dragEnterEvent(QDragEnterEvent *event) 
{
    if (event->mimeData()->hasUrls()) event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event) 
{
    const QMimeData *mime_data = event->mimeData();

    if (mime_data->hasUrls()) {
        QList<QUrl> url_list = mime_data->urls();
        QString file_path = url_list[0].toLocalFile();

        emit UploadMaze(file_path.toStdString());
        event->acceptProposedAction();
    }
}
