#ifndef DONATION_H
#define DONATION_H
#include "buy.h"
#include <QDate>

class donation : public buy
{
public:
    donation();
    void set_name(QString title);
    QString get_name();
    void show();
private:
    QString name;

};

#endif // DONATION_H
