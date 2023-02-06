#ifndef HP_MOTORDESIGN_H
#define HP_MOTORDESIGN_H

#include <QWidget>

namespace Ui {
class hp_motordesign;
}

class hp_motordesign : public QWidget
{
    Q_OBJECT

public:
    explicit hp_motordesign(QWidget *parent = nullptr);
    ~hp_motordesign();

private:
    Ui::hp_motordesign *ui;
};

#endif // HP_MOTORDESIGN_H
