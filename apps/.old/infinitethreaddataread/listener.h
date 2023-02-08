#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <worker.h>
#include <memory>

class listener : public QObject
{
    Q_OBJECT
public:
    explicit listener(QObject *parent = nullptr, std::shared_ptr<WorkerThread> bkworker = nullptr);

    void parsedata(int newvalue);

signals:
    void emitparsed(int value);
private:

};

#endif // LISTENER_H
