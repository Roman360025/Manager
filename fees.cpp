#include "fees.h"
#include "ui_fees.h"
#include "donate.h"
#include "donation.h"
#include <QQueue>
#include <QFile>
QQueue <donation *>  donat;
QQueue <donation *> donat_2;

fees::fees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fees)
{
    ui->setupUi(this);

    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit_2->setMaximumDate(QDate::currentDate());

    ui->pushButton->setToolTip("Рассчитает сборы для указанного выше\n фонда за указанный промежуток времени");
    ui->pushButton->setEnabled(false);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(buttonEnabled(QString)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(buttonDefault(QString)));

}

void fees::buttonEnabled(QString str)
{
    ui->pushButton->setEnabled(!str.isEmpty());
}

void fees::buttonDefault(QString str)
{
    ui->pushButton->setDefault(!str.isEmpty());
}

fees::~fees()
{
    delete ui;
}

void fees::on_pushButton_clicked()
{
    float sum=0;
    if(donat.empty()&&donat_2.empty())
    {
        QFile file("donate.txt");
        if ((file.exists()&&(file.open(QIODevice::ReadOnly))))
        {
            QString str="";
            QString strDate="";
            QString strValue="";
            QString strName="";
            int n=0;
            while(!file.atEnd())
            {
                str=file.readLine();
                donation *fond=new donation();
                strDate=str.left(10);
                fond->set_date(QDate::fromString(strDate, "dd.MM.yyyy"));
                strValue=str.mid(11,str.indexOf(" ", 11)-10);
                strName=str.mid(str.indexOf(" ", 11)+1);
                n=strName.size()-2;
                strName=strName.mid(0,n);
                fond->set_value(strValue.toFloat());
                fond->set_name(strName);
                 donat.enqueue(fond);
            }
        }
        file.close();
    }

    QDate date1=ui->dateEdit->date();
    QDate date2=ui->dateEdit_2->date();

    if (date1>date2)
    {
        QDate d=date1;
        date1=date2;
        date2=d;
    }

    while(!donat.empty())
    {
        donat_2.enqueue(donat.head());
        int x=0;
        x=QString::compare(donat.head()->get_name(), ui->lineEdit->text());
        if((donat.head()->get_date()>=date1)&&(donat.head()->get_date()<=date2)&&(x==0))
            sum+=donat.head()->get_value();
        donat.dequeue();
    }
    if(donat.empty()&&!donat_2.empty())
        donat.swap(donat_2);
    donat_2.clear();

    QString str1=QString("%1").arg(sum);
    ui->lineEdit_2->setText(str1);

}






