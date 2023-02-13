#include "hp_faultwarning_loader.h"

hp_faultwarning_loader::hp_faultwarning_loader(QObject *parent)
    : QObject{parent}
{

}

void hp_faultwarning_loader::loadfromfile(QString filename)
{
    // load file
    QString val;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    // loading configuration
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value1 = sett2.value(QString("packet"));

    // channel
    QString channel =  value1.toObject().value(QString("_canchannel")).toString();
    int currentchannel =  std::stoul(channel.toStdString(), nullptr, 16);
    std::shared_ptr<singlefaultwarningpacket> singlepacket = std::make_shared<singlefaultwarningpacket>();
    singlepacket->canchannel = currentchannel;
    std::vector<int> bits{};

    QJsonValue elems = value1.toObject().value(QString("elem"));
    QJsonArray elemsarray = elems.toArray();
    for(auto e : elemsarray){
        QString b = e.toObject().value("_bit").toString();
        int bit = std::stoul(b.toStdString(), nullptr, 10);

        QString desc = e.toObject().value("_description").toString();
        QString type = e.toObject().value("_type").toString();

        if(desc != "RESERVED"){
            bits.push_back(bit);


        }
        qDebug() << desc;
    }
}
