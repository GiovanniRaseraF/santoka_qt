#ifndef SOFTWAREINFO_H
#define SOFTWAREINFO_H

#include <QDialog>

namespace Ui {
class softwareinfo;
};

class softwareinfo : public QDialog
{
    Q_OBJECT

public:
    explicit softwareinfo(QWidget *parent = nullptr);
    ~softwareinfo();

private slots:
    void on_pb_close_clicked();

private:
    Ui::softwareinfo *ui;
};

#endif // SOFTWAREINFO_H
