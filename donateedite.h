#ifndef DONATEEDITE_H
#define DONATEEDITE_H

#include <QDialog>

namespace Ui {
class donateEdite;
}

class donateEdite : public QDialog
{
    Q_OBJECT

public:
    explicit donateEdite(QWidget *parent = 0);
    ~donateEdite();

private slots:
    void on_pushButton_clicked();
    void buttonEnabled();
private:
    Ui::donateEdite *ui;
};

#endif // DONATEEDITE_H
