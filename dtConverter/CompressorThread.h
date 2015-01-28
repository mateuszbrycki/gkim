#ifndef COMPRESSORTHREADD_H
#define COMPRESSORTHREADD_H

#include <QThread>
#include <QProgressDialog>
#include <string>

class CompressorThread : public QThread
{
    Q_OBJECT
public:
    explicit CompressorThread(QObject *parent = 0);
    void run(QProgressDialog& dialog, const std::string& openPath, const std::string& savePath, const std::string& saveName, const int& colorType);

signals:
    void compressionSuccess();
    void compressionFailed();
public slots:

};

#endif // COMPRESSORTHREADD_H
