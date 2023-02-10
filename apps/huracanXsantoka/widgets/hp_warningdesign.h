#ifndef HP_WARNINGDESIGN_H
#define HP_WARNINGDESIGN_H

#include "hp_faultwarning.h"
#include "ui_hp_faultwarning.h"

class hp_warningdesign : public hp_faultwarning
{
public:
    hp_warningdesign(QString name = "FAULT", int _canchannel = 0, int bit = 0, QWidget *parent = nullptr);
    hp_warningdesign() = default;

public slots:
    virtual void activatecolor(int c, int b, bool active) override;
};

#endif // HP_WARNINGDESIGN_H
