#ifndef ADDBUY_H
#define ADDBUY_H

#include <QDialog>
#include <QDoubleValidator>

namespace Ui {
class addbuy;
}

class addbuy : public QDialog
{
    Q_OBJECT

public:
    explicit addbuy(QWidget *parent = 0);
    ~addbuy();

private slots:
    void on_pushButton_clicked();
    void butttonEnabled(QString str);
    void buttonDefault(QString str);
private:
    Ui::addbuy *ui;
    QDoubleValidator m_doubleValidator;
};

#endif // ADDBUY_H
