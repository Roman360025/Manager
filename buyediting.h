#ifndef BUYEDITING_H
#define BUYEDITING_H

#include <QDialog>

namespace Ui {
class buyEditing;
}

class buyEditing : public QDialog
{
    Q_OBJECT

public:
    explicit buyEditing(QWidget *parent = 0);
    ~buyEditing();

private slots:
    void on_pushButton_clicked();
    void buttonEnabled();

private:
    Ui::buyEditing *ui;
};

#endif // BUYEDITING_H
