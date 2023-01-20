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
            /* ... here is the expensive or blocking operation ... */
            emit resultReady(c++);
            QThread::sleep(2);
        }

        QThread::run();
    }
signals:
    void resultReady(const int s);
};

#endif // WORKER_H
