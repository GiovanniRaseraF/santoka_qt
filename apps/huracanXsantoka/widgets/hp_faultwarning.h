#ifndef HP_FAULTWARNING_H
#define HP_FAULTWARNING_H

#include <QWidget>

namespace Ui {
class hp_faultwarning;
}

class hp_faultwarning : public QWidget
{
    Q_OBJECT

public:
    explicit hp_faultwarning(QWidget *parent = nullptr);
    ~hp_faultwarning();



private:
    Ui::hp_faultwarning *ui;

};

#endif // HP_FAULTWARNING_H
