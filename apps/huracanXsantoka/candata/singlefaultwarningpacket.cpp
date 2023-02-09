#include "singlefaultwarningpacket.h"

singlefaultwarningpacket::singlefaultwarningpacket(QObject *parent)
    : QObject{parent}
{

}

void singlefaultwarningpacket::loaddata(int _canchannel, std::map<int, std::tuple<QString, QString> > _bitdescription)
{
    canchannel = _canchannel;

    for(auto v : _bitdescription){
        if(std::get<0>(v.second) == "fault"){
            faults[v.first] = std::get<1>(v.second);
        }
    }


}
