#ifndef HP_FAULTDESING_H
#define HP_FAULTDESING_H

#include "hp_faultwarning.h"
#include "ui_hp_faultwarning.h"

class hp_faultdesing : public hp_faultwarning
{
public:
    hp_faultdesing(QString name = "FAULT", int _canchannel = 0, int bit = 0, QWidget *parent = nullptr);
    hp_faultdesing() = default;

public slots:
   virtual void activatecolor(int c, int b, bool active) override;
};

#endif // HP_FAULTDESING_H
