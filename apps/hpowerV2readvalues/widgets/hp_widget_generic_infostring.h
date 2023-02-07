#ifndef HP_WIDGET_GENERIC_INFOSTRING_H
#define HP_WIDGET_GENERIC_INFOSTRING_H

#include <QWidget>
#include <QString>

#include <memory>

#include "displayer/filter.h"

namespace Ui {
class hp_widget_generic_infostring;
}

class hp_widget_generic_infostring : public QWidget
{
    Q_OBJECT

public:
    explicit hp_widget_generic_infostring(QString _name = "", std::shared_ptr<filter> type_filter = nullptr, QWidget *parent = nullptr);
    ~hp_widget_generic_infostring();

public slots:
    void setText(QString newtext);

private:
    Ui::hp_widget_generic_infostring *ui;

    // filter
    std::shared_ptr<filter> actual_filter;

    // info
    QString name;
};

#endif // HP_WIDGET_GENERIC_INFOSTRING_H
