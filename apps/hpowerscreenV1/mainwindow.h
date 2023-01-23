#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataproducer.h"
#include <memory>
#include <QString>


namespace Ui {
class MainWindow;
}
Q_DECLARE_METATYPE(struct can_frame)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void canbusdatalog(const struct can_frame frame);

private:
    Ui::MainWindow *ui;

    // canbus
    std::shared_ptr<canbus_thread> can_thread;

    // log
    QString logstrign{};
    const uint32_t MAXLOGS = 1000;
    uint32_t numlogs = 0;
};

#endif // MAINWINDOW_H
