#ifndef HP_TRIPLEVAL_H
#define HP_TRIPLEVAL_H

#include <QWidget>

namespace Ui {
class hp_tripleval;
}

class hp_tripleval : public QWidget
{
    Q_OBJECT

public:
    explicit hp_tripleval(QWidget *parent = nullptr);
    ~hp_tripleval();

private:
    Ui::hp_tripleval *ui;
};

#endif // HP_TRIPLEVAL_H
