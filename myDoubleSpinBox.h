#ifndef MYDOUBLESPINBOX_H
#define MYDOUBLESPINBOX_H

#include <QObject>
#include <QDoubleSpinBox>


class MyDoubleSpinBox: public QDoubleSpinBox  {
    Q_OBJECT
 public:
    MyDoubleSpinBox( QWidget * parent = 0)
        : QDoubleSpinBox(parent) {}

    virtual QString textFromValue ( double value ) const;
    ~MyDoubleSpinBox() {}
signals:
        void valueChanged(double);
};

#endif
