#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QProgressBar>
#include <QCoreApplication>

#include <SDL.h>
#include <vector>
#include <iostream>

#include "CompressorThread.h"
#include "Picture.h"
#include "FileWriter.h"
#include "Compressor.h"

#undef SDL_main

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("DTConverter"); //ustawienie tytułu głównego okna
    ui->setupUi(this);

    ui->bdFile->setReadOnly(true);
    ui->bdPath->setReadOnly(true);

    ui->dbFile->setReadOnly(true);
    ui->dbPath->setReadOnly(true);

    this->compressorThread = new CompressorThread(this);

    connect(compressorThread, SIGNAL(compressionSuccess()), this, SLOT(compressionSuccess()));
    connect(compressorThread, SIGNAL(compressionFailed()), this, SLOT(compressionFailed()));
}

QString MainWindow::getFilePath(int mode) {

    QString selectedFilePath = QFileDialog::getOpenFileName(this,
        tr("Otwórz obraz"), "", tr((mode == 0) ? "Image Files (*.bmp)" : "Image Files (*.dt)" ));

    if(mode == 0) {
        ui->bdFile->setMaxLength(this->qLineMaxLength);
        ui->bdFile->setText(selectedFilePath);
    } else {
        ui->dbFile->setMaxLength(this->qLineMaxLength);
        ui->dbFile->setText(selectedFilePath);
    }
    return selectedFilePath;
}

QString MainWindow::getFolderPath(int mode) {
    QString selectedFolderPath =  QFileDialog::getExistingDirectory(this, tr("Wskaż folder"),
         "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(mode == 0) {
        ui->bdPath->setMaxLength(this->qLineMaxLength);
        ui->bdPath->setText(selectedFolderPath);
    } else {
        ui->dbPath->setMaxLength(this->qLineMaxLength);
        ui->dbPath->setText(selectedFolderPath);
    }
    return selectedFolderPath ;
}

void MainWindow::on_bdFile_selectionChanged()
{
    if((ui->bdFile->text()).isEmpty()) {
        QString filePath = this->getFilePath(0);
    }
}

void MainWindow::on_bdFileButton_released()
{
    QString filePath = this->getFilePath(0);
}

void MainWindow::on_bdPath_selectionChanged()
{
    if((ui->bdPath->text()).isEmpty()) {
        QString folderPath = this->getFolderPath(0);
    }
}

void MainWindow::on_bdPathButton_released()
{
    QString folderPath = this->getFolderPath(0);
}

void MainWindow::on_bdConvertButton_released()
{
    string openPath = ui->bdFile->text().toStdString();
    string savePath = ui->bdPath->text().toStdString();
    string saveName = ui->bdFileName->text().toStdString();

    if(!openPath.empty() && !savePath.empty() && !saveName.empty()) {
        qDebug()<<"Rozpoczęto analizę!";


        int colorType;
        if(ui->greyScale->checkState()) {
            colorType = 1;
        } else {
            colorType = 0;
        }
        qDebug()<<"Uruchamianie nowego wątku!";

        QProgressDialog progress("Trwa konwersja", "", 0,0, this);
        progress.setWindowModality(Qt::WindowModal);
        progress.setWindowTitle("Konwersja");
        progress.setCancelButton(0);
        progress.setFixedSize(250, 100);
        progress.setRange(0,100);
        progress.setValue(5);
        progress.show();

        QCoreApplication::processEvents();

        compressorThread->run(progress, openPath, savePath, saveName, colorType);

        progress.close();

    } else {
        QMessageBox::information( this, "Błąd", "Wypełnij wszystkie pola", QMessageBox::Ok, 0 );
    }
}

void MainWindow::compressionSuccess() {
    QMessageBox::information( this, "Koniec", "Plik został przekonwertowany poprawnie!", QMessageBox::Ok, 0 );
}

void MainWindow::compressionFailed() {
    QMessageBox::critical( this, "Błąd", "Konwersja nie powiodła się. Spróbuj ponownie.", QMessageBox::Ok, 0 );
}

void MainWindow::on_dbFile_selectionChanged()
{
    if((ui->dbFile->text()).isEmpty()) {
        QString filePath = this->getFilePath(1);
    }
}

void MainWindow::on_dbPath_selectionChanged()
{
    if((ui->dbPath->text()).isEmpty()) {
        QString folderPath = this->getFolderPath(1);
    }
}

void MainWindow::on_dbFileButton_released()
{
     QString filePath = this->getFilePath(1);
}

void MainWindow::on_dbPathButton_released()
{
     QString folderPath = this->getFolderPath(1);
}

void MainWindow::on_dbConvertButton_released()
{
    if(!(ui->dbFile->text()).isEmpty() && !(ui->dbPath->text()).isEmpty()) {
        qDebug()<<"Obsługa konwersji z DT do BMP";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
