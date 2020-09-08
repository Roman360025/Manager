#include "donation.h"

donation::donation()
{

}

void donation::set_name(QString title)
{
    donation::name=title;
}

QString donation::get_name()
{
    return donation::name;
}

