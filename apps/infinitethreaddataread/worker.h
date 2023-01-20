#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QString>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent) : QThread(parent){}
    void run() override {
        int c = 0;
        while(true){
            QString result = QString::number(c++);
            /* ... here is the expensive or blocking operation ... */
            emit resultReady(result);
            QThread::sleep(1);
        }

        QThread::run();
    }
signals:
    void resultReady(const QString &s);
};

#endif // WORKER_H
