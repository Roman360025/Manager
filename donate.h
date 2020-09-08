#ifndef DONATE_H
#define DONATE_H

#include <QDialog>

namespace Ui {
class donate;
}

class donate : public QDialog
{
    Q_OBJECT

public:
    explicit donate(QWidget *parent = 0);
    ~donate();

private slots:
    void on_pushButton_clicked();
    void buttonEnabled();
    void buttonDefault();
private:
    Ui::donate *ui;
};

#endif // DONATE_H
