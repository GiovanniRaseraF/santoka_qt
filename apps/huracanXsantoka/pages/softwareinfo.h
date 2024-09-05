#ifndef SOFTWAREINFO_H
#define SOFTWAREINFO_H

#include <QDialog>
#include <memory>
#include "displayer/sniffer.h"

#define PASSSHARED(cl, name) \
    std::shared_ptr<cl> name = nullptr

#define PASSSHARED_NONULL(cl, name) \
    std::shared_ptr<cl> name

namespace Ui {
class softwareinfo;
};

class softwareinfo : public QDialog
{
    Q_OBJECT

public:
    explicit softwareinfo(QWidget *parent = nullptr);
    ~softwareinfo();

    void connectInformations(
        PASSSHARED(sniffer_filter, _sniffer)
    );

    void updateCandumpText(QString);
    void clearDump();

private slots:
    void on_pb_close_clicked();
    void on_candata(QString);

    void on_softwareinfo_accepted();

    void on_softwareinfo_rejected();

private:
    Ui::softwareinfo *ui;

    std::shared_ptr<sniffer_filter>  mysniffer;

    int appendCount = 0;
};

#endif // SOFTWAREINFO_H
