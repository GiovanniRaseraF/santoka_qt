#include "hp_faultwarning_loader.h"

hp_faultwarning_loader::hp_faultwarning_loader(QObject *parent)
    : QObject{parent}
{

}

void hp_faultwarning_loader::loadfromfile(QString filename)
{
    QFile file{filename};
    file.open(QIODevice::ReadOnly);




    /*
    QDomDocument doc{QDomDocument::from};
    QXmlStreamReader reader;
    reader.setDevice(&file);

    while(!reader.atEnd()){
        reader.readNext();

        QString elemname = reader.name().toString();
        if(elemname == "configuration"){
            reader.readNext();
            QString sett = reader.name().toString();

            if(sett == "settings"){
                reader.readNext();
                QString value = reader.name().toString();

                while(value != "settings"){
                    QString nn = reader.readElementText();
                    qDebug() << nn;
                    reader.readNext();
                }
            }
        }
    }
    QDomDocument configuration{filename};

    QFile f{filename};
    qDebug() << f ;

    QDomElement root = configuration.documentElement();
    QDomNode rootnode = root.firstChild();

    QDomElement roote = rootnode.toElement();

    std::cout << qPrintable(roote.tagName()) << std::endl;
    */
}
