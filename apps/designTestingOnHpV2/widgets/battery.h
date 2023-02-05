#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>

namespace Ui {
class battery;
}

class battery : public QWidget
{
    Q_OBJECT

public:
    explicit battery(QWidget *parent = nullptr);
    ~battery();

private:
    Ui::battery *ui;
};

#endif // BATTERY_H
