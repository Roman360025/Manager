#include "donate.h"
#include "donation.h"
#include "ui_donate.h"
#include <QQueue>
#include <QFile>
#include <QTextStream>
extern QQueue<donation *>donat;

donate::donate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::donate)
{
    ui->setupUi(this);

    ui->dateEdit->setMaximumDate(QDate::currentDate());

    QRegExp float_exp("([0-9]{1,})(\\.)([0-9]{1,2})");
    ui->lineEdit->setValidator(new QRegExpValidator(float_exp, this));

    ui->pushButton->setToolTip("Добавит указанные выше данные в \nфайл c даннами о сборах пожертвований");
    ui->pushButton->setEnabled(false);
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(buttonEnabled()));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(buttonDefault()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(buttonEnabled()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(buttonDefault()));
}

void donate::buttonEnabled()
{
    ui->pushButton->setEnabled(!ui->lineEdit_2->text().isEmpty()&&!ui->lineEdit->text().isEmpty());
}

void donate::buttonDefault()
{
    ui->pushButton->setDefault(!ui->lineEdit_2->text().isEmpty()&&!ui->lineEdit->text().isEmpty());
}

donate::~donate()
{
    delete ui;
}

void donate::on_pushButton_clicked()
{
    QFile file("donate.txt");
    if(file.open(QIODevice::Append|QIODevice::Text))
    {
        QTextStream writeStream(&file);
        writeStream<<ui->dateEdit->text()<<" ";
        writeStream<<ui->lineEdit->text()<<" ";
        writeStream<<ui->lineEdit_2->text()<<endl;
        if(!donat.empty())
        {
            donation * fond=new donation;
            fond->set_date(ui->dateEdit->date());
            fond->set_value(ui->lineEdit->text().toDouble());
            fond->set_name(ui->lineEdit_2->text());
            donat.enqueue(fond);
        }
    }
    file.close();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    QDate date(2000, 1, 1);
    ui->dateEdit->setDate(date);
    ui->pushButton->setEnabled(false);
}
