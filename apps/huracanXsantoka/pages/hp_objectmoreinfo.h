#ifndef HP_OBJECTMOREINFO_H
#define HP_OBJECTMOREINFO_H

#include <QMainWindow>

namespace Ui {
class hp_objectmoreinfo;
}

class hp_objectmoreinfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit hp_objectmoreinfo(QWidget *parent = nullptr);
    ~hp_objectmoreinfo();

private slots:
    void on_pb_close_clicked();

protected:
    Ui::hp_objectmoreinfo *ui;
};

#endif // HP_OBJECTMOREINFO_H
