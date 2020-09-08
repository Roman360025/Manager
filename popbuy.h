#ifndef POPBUY_H
#define POPBUY_H
#include "buy.h"
#include <QString>
#include <QDate>


class popbuy: public buy
{
public:
    popbuy();
    bool operator <(popbuy &other);
    void set_min(float min);
    void set_max(float max);
    void set_dmin(QDate date);
    void set_dmax(QDate date);
    void inc_pop();
    void set_pop(int value);
    int get_pop();
    float get_min();
    float get_max();
    QDate get_dmin();
    QDate get_dmax();
private:
    int pop;
    float xmin, xmax;
    QDate dmin, dmax;
};

#endif // POPBUY_H
