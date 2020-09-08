#ifndef BUY_H
#define BUY_H
#include <QDate>


class buy
{
public:
    buy();
    void set_value(float value);
    void set_date(QDate date);
    void set_name(QString title);
    float get_value();
    QString get_name();
    QDate get_date();
    void show();
protected:
    float cost;
    QDate date;
    QString name;
};

#endif // BUY_H
