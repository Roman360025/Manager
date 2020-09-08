#ifndef OTHFORWHILE_H
#define OTHFORWHILE_H

#include <QDialog>

namespace Ui {
class othforwhile;
}

class othforwhile : public QDialog
{
    Q_OBJECT

public:
    explicit othforwhile(QWidget *parent = 0);
    ~othforwhile();

private slots:
    void on_pushButton_clicked();

private:
    Ui::othforwhile *ui;
};

#endif // OTHFORWHILE_H
