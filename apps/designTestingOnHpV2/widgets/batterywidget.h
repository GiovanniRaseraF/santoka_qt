#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>

namespace Ui {
class batterywidget;
}

class batterywidget : public QWidget
{
    Q_OBJECT

public:
    explicit batterywidget(QWidget *parent = nullptr);
    ~batterywidget();

private:
    Ui::batterywidget *ui;
};

#endif // BATTERYWIDGET_H
