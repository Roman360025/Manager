#include "buy.h"

buy::buy()
{

}


void buy::set_date(QDate data)
{
    date=data;
}


void buy::set_value(float value)
{
    cost=value;
}

void buy::set_name(QString title)
{
    name=title;
}


QDate buy::get_date()
{
    return date;
}


float buy::get_value()
{
    return cost;
}

QString buy::get_name()
{
    return name;
}
