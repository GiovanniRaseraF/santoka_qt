#ifndef HP_BATTERYDESIGN_H
#define HP_BATTERYDESIGN_H

#include <QWidget>
#include <QString>

#include <memory>

#include "displayer/battery_filter.h"

namespace Ui {
class hp_batterydesign;
}

class hp_batterydesign : public QWidget
{
    Q_OBJECT

public:
    explicit hp_batterydesign(std::shared_ptr<battery_filter> battery = nullptr, QWidget *parent = nullptr);
    ~hp_batterydesign();

public slots:
    void setText(QString newtext);

private:
    Ui::hp_batterydesign *ui;

    // filter
    std::shared_ptr<battery_filter> battery;
};

#endif // HP_BATTERYDESIGN_H
