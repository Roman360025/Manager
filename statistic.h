#ifndef STATISTIC_H
#define STATISTIC_H

#include <QDialog>

namespace Ui {
class statistic;
}

class statistic : public QDialog
{
    Q_OBJECT

public:
    explicit statistic(QWidget *parent = 0);
    ~statistic();

private slots:
    void on_pushButton_clicked();

private:
    Ui::statistic *ui;
};

#endif // STATISTIC_H
