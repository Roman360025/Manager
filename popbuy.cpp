#include "popbuy.h"
#include <QString>


popbuy::popbuy()
{
    pop=0;
}

bool popbuy::operator <(popbuy &other)
{
    return (this->pop<other.get_pop());
}

void popbuy::inc_pop()
{
    pop++;
}

void popbuy::set_pop(int value)
{
    pop=value;
}

int popbuy::get_pop()
{
    return popbuy::pop;
}

void popbuy::set_min(float min)
{
    xmin=min;
}

void popbuy::set_max(float max)
{
    xmax=max;
}

void popbuy::set_dmin(QDate date)
{
    dmin=date;
}

void popbuy::set_dmax(QDate date)
{
    dmax=date;
}

float popbuy::get_min()
{
    return popbuy::xmin;
}

float popbuy::get_max()
{
    return popbuy::xmax;
}

QDate popbuy::get_dmin()
{
    return popbuy::dmin;
}

QDate popbuy::get_dmax()
{
    return popbuy::dmax;
}

