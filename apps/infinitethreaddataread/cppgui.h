#ifndef CPPGUI_H
#define CPPGUI_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <QVariant>

class CppGui : public QWidget {
    Q_OBJECT

    QPushButton *button;

signals:
    void cppSignal(const QVariant& sentMsg) const;

public slots:
    void cppSlot(const QString& receivedMsg) const {
        qDebug() << "C++ received:" << receivedMsg;
    }

public:
    CppGui(QWidget *parent = nullptr) : QWidget(parent) {
        button = new QPushButton("Click Me!", this);
        connect(button, &QPushButton::clicked, [=] {
            emit cppSignal("Hello from C++!");
        });
    }
};
#endif // CPPGUI_H
