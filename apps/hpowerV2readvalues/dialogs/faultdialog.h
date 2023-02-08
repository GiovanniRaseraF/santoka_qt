#ifndef FAULTDIALOG_H
#define FAULTDIALOG_H

#include <QDialog>
#include <QMap>
#include <QVector>

#include <map>
#include <vector>
#include <memory>

namespace Ui {
class faultdialog;
}


class faultdialog : public QDialog
{
    Q_OBJECT

public:
    explicit faultdialog(QWidget *parent = nullptr);
    ~faultdialog();

private slots:
    void on_faultdialog_accepted();

    void on_pushButton_51_clicked();

    void getFaults(uint32_t newfaultmap);
    void getWarnings(uint32_t newwarningsmap);

private:
    Ui::faultdialog *ui;

    // faults


    // warnings
};

#endif // FAULTDIALOG_H
