#ifndef HP_FAULTWARNING_H
#define HP_FAULTWARNING_H

#include <QWidget>
#include <QString>

namespace Ui {
class hp_faultwarning;
}

class hp_faultwarning : public QWidget
{
    Q_OBJECT

public:
    explicit hp_faultwarning(QString name = "RESERVED", int _canchannel = 0, int bit = 0, QWidget *parent = nullptr);
    ~hp_faultwarning();

public slots:
    void activatecolor(int c, int b, bool active);
private:
    Ui::hp_faultwarning *ui;

    int canchannel;
    int bit;
};

#endif // HP_FAULTWARNING_H
