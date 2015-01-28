#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CompressorThread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CompressorThread *compressorThread;

private slots:
    void compressionSuccess();
    void compressionFailed();

    void on_bdFile_selectionChanged();

    void on_bdPath_selectionChanged();

    void on_bdFileButton_released();

    void on_bdPathButton_released();

    void on_bdConvertButton_released();

    void on_dbFile_selectionChanged();

    void on_dbPath_selectionChanged();

    void on_dbFileButton_released();

    void on_dbPathButton_released();

    void on_dbConvertButton_released();

private:
    Ui::MainWindow *ui;
    QString getFilePath(int mode);
    QString getFolderPath(int mode);

    int qLineMaxLength = 200;
};

#endif // MAINWINDOW_H
