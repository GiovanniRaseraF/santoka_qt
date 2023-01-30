#ifndef FAULTDIALOG_H
#define FAULTDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>

#include "ui_faultdialog.h"

class faultdialog : public QDialog, public Ui::FaultWindowDialog
{
    Q_OBJECT
public:
    faultdialog(QWidget *parent = nullptr);
    ~faultdialog();
private slots:
    void on_pushButton_clicked();
};

#endif // FAULTDIALOG_H
