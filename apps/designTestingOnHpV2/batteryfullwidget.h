#ifndef BATTERYFULLWIDGET_H
#define BATTERYFULLWIDGET_H

#include <QWidget>

/*
 * General info
 * border-radius: 150px;
 * background-color: qconicalgradient(
 * 	cx:0,
 * 	cy:0.7,
 * 	angle:90,
 * 	stop:0.700
 * 	rgba(255, 0, 127, 0),
 * 	stop:0.75
 * 	rgba(85, 170, 255, 255));
*/

namespace Ui {
class batteryFullWidget;
}

class batteryFullWidget : public QWidget
{
    Q_OBJECT

public:
    explicit batteryFullWidget(QWidget *parent = nullptr);
    ~batteryFullWidget();

private:
    Ui::batteryFullWidget *ui;
};

#endif // BATTERYFULLWIDGET_H
