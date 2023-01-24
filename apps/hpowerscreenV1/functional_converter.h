#ifndef FUNCTIONAL_CONVERTER_H
#define FUNCTIONAL_CONVERTER_H

#include <unistd.h>
#include <QVariant>
#include <QMap>
#include <functional>
#include <QString>
#include <unistd.h>

namespace conversion{
    QMap<std::string, std::function<QVariant(int)>> fun{
        {"uint8", [](int a){
            uint8_t val = 10;
            return QVariant(val);
        }},
    };
};

#endif // FUNCTIONAL_CONVERTER_H
