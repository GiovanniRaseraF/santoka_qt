#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <worker.h>
#include <QDebug>
#include "listener.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void handleResults(int res);
    void handlequickstring(QString res);

private:
    Ui::MainWindow *ui;

    std::shared_ptr<WorkerThread> backgroundCanbus;

    std::shared_ptr<listener> battery;
};
#endif // MAINWINDOW_H
