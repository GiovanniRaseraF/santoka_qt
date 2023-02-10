#ifndef HP_FAULTWARNING_LOADER_H
#define HP_FAULTWARNING_LOADER_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QtXml>
#include <QDomDocument>
#include <QXmlStreamReader>

#include <vector>
#include <memory>

#include "widgets/hp_faultdesing.h"
#include "widgets/hp_warningdesign.h"
#include "candata/singlefaultwarningpacket.h"

class hp_faultwarning_loader : public QObject
{
    Q_OBJECT
public:
    explicit hp_faultwarning_loader(QObject *parent = nullptr);

signals:
    void loadeddata();

public:
     void loadfromfile(QString filename);

private:
    std::vector<std::shared_ptr<singlefaultwarningpacket>> packets;
    std::vector<std::shared_ptr<hp_faultwarning>> faultswarnings;
    int numberofmotors = 0;
};

#endif // HP_FAULTWARNING_LOADER_H
