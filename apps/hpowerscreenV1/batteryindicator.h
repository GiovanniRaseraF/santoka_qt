#ifndef BATTERYINDICATOR_H
#define BATTERYINDICATOR_H

#include <QObject>
#include <QDialog>

namespace Ui {
    class BatteryIndicator;
}

class BatteryIndicator : public QDialog
{
    Q_OBJECT
public:
    explicit BatteryIndicator(QWidget *parent = nullptr);
    ~BatteryIndicator();
private:
    Ui::BatteryIndicator *ui;
    //void setupGeneral();

signals:

public slots:
};

#endif // BATTERYINDICATOR_H
