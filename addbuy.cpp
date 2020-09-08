#include "addbuy.h"
#include "buy.h"
#include "ui_addbuy.h"
#include <QFile>
#include <QDate>
#include <QTextStream>
#include <QRegExp>
#include <QQueue>
extern QQueue<buy *>memory;


addbuy::addbuy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addbuy), m_doubleValidator(-10000000000, 10000000000, 2, this)
{
    ui->setupUi(this);

    ui->dateEdit->setMaximumDate(QDate::currentDate());

    QRegExp float_exp("([0-9]{1,})(\\.)([0-9]{1,2})");
    ui->lineEdit->setValidator(new QRegExpValidator(float_exp, this));

    ui->pushButton->setToolTip("Добавит указанные выше данные в файл с даннами о покупках");
    ui->pushButton->setEnabled(false);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(butttonEnabled(QString)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(buttonDefault(QString)));

}


void addbuy::butttonEnabled(QString str)
{
    ui->pushButton->setEnabled(!str.isEmpty());
}

void addbuy::buttonDefault(QString str)
{
    ui->pushButton->setDefault(!str.isEmpty());
}
addbuy::~addbuy()
{
    delete ui;
}

void addbuy::on_pushButton_clicked()
{
   QFile file("buy.txt");
   if ( file.open(QIODevice::Append | QIODevice::Text))
   {
        QTextStream writeStream(&file);
        writeStream<<ui->dateEdit->text()<<" ";
        writeStream<<ui->lineEdit->text()<<" ";
        writeStream<<ui->lineEdit_2->text()<<endl;
        if (!memory.empty())
        {
            buy* purchase=new buy;
            purchase->set_date(ui->dateEdit->date());
            purchase->set_value(ui->lineEdit->text().toDouble());
            purchase->set_name(ui->lineEdit_2->text());
            memory.enqueue(purchase);
        }
        file.close();
   }
   QDate date(2000,1,1);
   ui->dateEdit->setDate(date);
   ui->lineEdit->clear();
   ui->lineEdit_2->clear();
   ui->pushButton->setEnabled(false);

}

