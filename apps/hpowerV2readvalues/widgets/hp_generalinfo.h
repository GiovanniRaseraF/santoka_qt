#ifndef HP_GENERALINFO_H
#define HP_GENERALINFO_H

#include <QWidget>

namespace Ui {
class hp_generalinfo;
}

class hp_generalinfo : public QWidget
{
    Q_OBJECT

public:
    explicit hp_generalinfo(QWidget *parent = nullptr);
    ~hp_generalinfo();

private:
    Ui::hp_generalinfo *ui;
};

#endif // HP_GENERALINFO_H
