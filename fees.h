#ifndef FEES_H
#define FEES_H

#include <QDialog>

namespace Ui {
class fees;
}

class fees : public QDialog
{
    Q_OBJECT

public:
    explicit fees(QWidget *parent = 0);
    ~fees();

private slots:
    void on_pushButton_clicked();
    void buttonEnabled(QString str);
    void buttonDefault(QString str);

private:
    Ui::fees *ui;
};

#endif // FEES_H
