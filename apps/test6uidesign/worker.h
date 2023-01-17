#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>



class Producer : public QThread
{
public:
    Producer(QObject *parent = NULL) : QThread(parent)
    {
    }

    void run() override
    {
        for (int i = 0; i < DataSize; ++i) {
            mutex.lock();
            if (numUsedBytes == BufferSize)
                bufferNotFull.wait(&mutex);
            mutex.unlock();
            buffer[i % BufferSize] = "ACGT"[2];
            mutex.lock();
            ++numUsedBytes;
            bufferNotEmpty.wakeAll();
            mutex.unlock();

            QThread::sleep(1);
        }
    }
};

class Consumer : public QThread
{
    Q_OBJECT
public:
    Consumer(QObject *parent = NULL) : QThread(parent)
    {
    }

    void run() override
    {
        for (int i = 0; i < DataSize; ++i) {
            mutex.lock();
            if (numUsedBytes == 0)
                bufferNotEmpty.wait(&mutex);

            mutex.unlock();
            fprintf(stderr, "%c", buffer[i % BufferSize]);
            mutex.lock();

            --numUsedBytes;
            bufferNotFull.wakeAll();
            mutex.unlock();
        }
        fprintf(stderr, "\n");
    }
};

#endif // WORKER_H
