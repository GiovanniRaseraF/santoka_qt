#ifndef GENERALINFO_LISTENER_H
#define GENERALINFO_LISTENER_H

#include <QObject>
#include "listener.h"
#include <unistd.h>
#include <map>
#include <tuple>
#include <functional>

#define CONVERSION(totype, varname) \
    std::pair<totype, std::function<totype(int a)>> varname;

class generalinfo_listener : public listener
{
    Q_OBJECT
public:
    explicit generalinfo_listener(QObject *parent = nullptr);

signals:

public slots:

private:
    CONVERSION(uint8_t, gen_helo)
    CONVERSION(std::string, gen_helo2)
};

#endif // GENERALINFO_LISTENER_H
