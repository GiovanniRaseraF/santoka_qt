#ifndef BOATINFOWINDOW_H
#define BOATINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class BoatInfoWindow;
}

class BoatInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoatInfoWindow(QWidget *parent = 0);
    ~BoatInfoWindow();

private:
    Ui::BoatInfoWindow *ui;
};

#endif // BOATINFOWINDOW_H
