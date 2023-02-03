#ifndef BATTERYFULLWIDGET_H
#define BATTERYFULLWIDGET_H

#include <QWidget>

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
