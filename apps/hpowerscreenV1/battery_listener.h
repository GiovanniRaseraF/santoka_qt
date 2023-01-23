#ifndef BATTERY_LISTENER_H
#define BATTERY_LISTENER_H

#include <QObject>
#include "listener.h"

class battery_listener : public listener
{
    Q_OBJECT
public:
    explicit battery_listener(QObject *parent = nullptr);

signals:

public slots:
    void update(const struct can_frame frame);
};

#endif // BATTERY_LISTENER_H
