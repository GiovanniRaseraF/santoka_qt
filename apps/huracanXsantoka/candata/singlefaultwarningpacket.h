#ifndef SINGLEFAULTWARNINGPACKET_H
#define SINGLEFAULTWARNINGPACKET_H

#include <QObject>
#include <QMap>
#include <QString>

#include <map>
#include <tuple>

class singlefaultwarningpacket : public QObject
{
    Q_OBJECT
public:
    explicit singlefaultwarningpacket(QObject *parent = nullptr);
    void loaddata(int _canchannel, std::map<int, std::tuple<QString, QString>> _bitdescription);

signals:

public:
    int canchannel;

    std::map<int, QString> alarms;
    std::map<int, QString> warnings;
    std::map<int, QString> faults;
};

#endif // SINGLEFAULTWARNINGPACKET_H
