#include "buyediting.h"
#include "ui_buyediting.h"
#include "buy.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QQueue>
extern QQueue<buy *>memory;
QStringList strList;
buyEditing::buyEditing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buyEditing)
{
    strList.clear();
    ui->setupUi(this);

    ui->dateEdit->setMaximumDate(QDate::currentDate());

    ui->pushButton->setEnabled(false);

    QRegExp float_exp("([0-9]{1,})(\\.)([0-9]{1,2})");
    ui->lineEdit->setValidator(new QRegExpValidator(float_exp, this));

    connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(buttonEnabled()));
    connect(ui->checkBox_2, SIGNAL(clicked(bool)), this, SLOT(buttonEnabled()));
    connect(ui->checkBox_3, SIGNAL(clicked(bool)), this, SLOT(buttonEnabled()));
    connect(ui->checkBox_4, SIGNAL(clicked(bool)), this, SLOT(buttonEnabled()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(buttonEnabled()));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(buttonEnabled()));


    QFile file("buy.txt");

     if ((file.exists()&&(file.open(QIODevice::ReadOnly))))
    {
         int i=0;
        while(!file.atEnd())
        {
            strList<<file.readLine();
            ui->plainTextEdit->insertPlainText(strList[i]);
            i++;
        }
    }
         file.close();

     ui->spinBox->setMaximum(strList.size());

}

void buyEditing::buttonEnabled()
{
    if (ui->checkBox_4->isChecked())
        ui->pushButton->setEnabled(true);
    else
    {
    if(ui->checkBox->isChecked()&&!ui->checkBox_2->isChecked()&&!ui->checkBox_3->isChecked())
        ui->pushButton->setEnabled(true);
   else  if(ui->checkBox_2->isChecked()&&ui->lineEdit->text().isEmpty())
        ui->pushButton->setEnabled(false);
    else if(ui->checkBox_3->isChecked()&&ui->lineEdit_2->text().isEmpty())
        ui->pushButton->setEnabled(false);
    else if(!ui->checkBox->isChecked()&&!ui->checkBox_2->isChecked()&&!ui->checkBox_3->isChecked())
        ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
    }
}

buyEditing::~buyEditing()
{
    delete ui;
}

void buyEditing::on_pushButton_clicked()
{
       QFile file("buy.txt");

     if((file.exists())&&(file.open(QIODevice::WriteOnly)))
     {
         if(ui->checkBox_4->isChecked())
         {
             strList.removeAt(ui->spinBox->value()-1);
             QTextStream stream(&file);
             ui->plainTextEdit->clear();
             foreach (QString s, strList) {
                stream<<s;
                ui->plainTextEdit->insertPlainText(s);
             }
         }
         else if (ui->checkBox->isChecked()&&!ui->checkBox_2->isChecked()&&!ui->checkBox_3->isChecked())
         {
             QString strDate=ui->dateEdit->text();
             QString str=strList[ui->spinBox->value()-1];
             QString strValue=str.mid(11, str.indexOf(" ",11)-10);
             QString strName=str.mid(str.indexOf(" ",11)+1);
             int n=strName.size()-2;
             strName=strName.mid(0,n);
             QString strNew=strDate+" "+strValue+strName+"\r"+"\n";
             strList[ui->spinBox->value()-1]=strNew;
             QTextStream stream(&file);
             ui->plainTextEdit->clear();
             foreach (QString s, strList) {
                 stream<<s;
                 ui->plainTextEdit->insertPlainText(s);
             }
         }
         else if(!ui->checkBox->isChecked()&&ui->checkBox_2->isChecked()&&!ui->checkBox_3->isChecked())
         {
             QString strValue=ui->lineEdit->text();
             QString str=strList[ui->spinBox->value()-1];
             QString strDate=str.left(10);
             QString strName=str.mid(str.indexOf(" ",11)+1);
             int n=strName.size()-2;
             strName=strName.mid(0,n);
             QString strNew=strDate+" "+strValue+" "+strName+"\r"+"\n";
             strList[ui->spinBox->value()-1]=strNew;
             QTextStream stream(&file);
             ui->plainTextEdit->clear();
             foreach (QString s, strList) {
                 stream<<s;
                 ui->plainTextEdit->insertPlainText(s);
             }
         }
         else if(!ui->checkBox->isChecked()&&!ui->checkBox_2->isChecked()&&ui->checkBox_3->isChecked())
         {
             QString str=strList[ui->spinBox->value()-1];
             QString strDate=str.left(10);
             QString strValue=str.mid(11, str.indexOf(" ",11)-10);
             QString strName=ui->lineEdit_2->text();
             QString strNew=strDate+" "+strValue+strName+"\r"+"\n";
             strList[ui->spinBox->value()-1]=strNew;
             QTextStream stream(&file);
             ui->plainTextEdit->clear();
             foreach (QString s, strList) {
                 stream<<s;
                 ui->plainTextEdit->insertPlainText(s);
             }
         }
         else if(ui->checkBox->isChecked()&&ui->checkBox_2->isChecked()&&!ui->checkBox_3->isChecked())
         {
             QString strDate=ui->dateEdit->text();
             QString strValue=ui->lineEdit->text();
             QString str=strList[ui->spinBox->value()-1];
             QString strName=str.mid(str.indexOf(" ",11)+1);
             int n=strName.size()-2;
             strName=strName.mid(0,n);
            QString strNew=strDate+" "+strValue+" "+strName+"\r"+"\n";
            strList[ui->spinBox->value()-1]=strNew;
            QTextStream stream(&file);
            ui->plainTextEdit->clear();
            foreach (QString s, strList ) {
                stream<<s;
                ui->plainTextEdit->insertPlainText(s);
            }
         }
         else if(!ui->checkBox->isChecked()&&!ui->checkBox_2->isChecked()&&ui->checkBox_3->isChecked())
         {
             QString strDate=ui->dateEdit->text();
             QString str=strList[ui->spinBox->value()-1];
             QString strName=ui->lineEdit_2->text();
             QString strValue=str.mid(11, str.indexOf(" ",11)-10);
             QString strNew=strDate+" "+strValue+" "+strName+"\r"+"\n";
             strList[ui->spinBox->value()-1]=strNew;
             QTextStream stream(&file);
             ui->plainTextEdit->clear();
             foreach (QString s, strList ) {
                 stream<<s;
                 ui->plainTextEdit->insertPlainText(s);
             }
         }
         else if(!ui->checkBox->isChecked()&&ui->checkBox_2->isChecked()&&ui->checkBox_3->isChecked())
         {
              QString str=strList[ui->spinBox->value()-1];
              QString strDate=str.left(10);
              QString strValue=ui->lineEdit->text();
              QString strName=ui->lineEdit_2->text();
              QString strNew=strDate+" "+strValue+" "+strName+"\r"+"\n";
              strList[ui->spinBox->value()-1]=strNew;
              QTextStream stream(&file);
              ui->plainTextEdit->clear();
              foreach (QString s, strList ) {
                  stream<<s;
                  ui->plainTextEdit->insertPlainText(s);
              }
         }
         else if(ui->checkBox->isChecked()&&!ui->checkBox_2->isChecked()&&ui->checkBox_3->isChecked())
         {
             QString strDate=ui->dateEdit->text();
             QString strName=ui->lineEdit_2->text();
             QString str=strList[ui->spinBox->value()-1];
             QString strValue=str.mid(11, str.indexOf(" ",11)-10);
             QString strNew=strDate+" "+strValue+" "+strName+"\r"+"\n";
             strList[ui->spinBox->value()-1]=strNew;
             QTextStream stream(&file);
             ui->plainTextEdit->clear();
             foreach (QString s, strList ) {
                 stream<<s;
                 ui->plainTextEdit->insertPlainText(s);
             }
         }
         else if(ui->checkBox->isChecked()&&ui->checkBox_2->isChecked()&&ui->checkBox_3->isChecked())
         {
             QString strDate=ui->dateEdit->text();
             QString strName=ui->lineEdit_2->text();
             QString strValue=ui->lineEdit->text();
             QString strNew=strDate+" "+strValue+" "+strName+"\r"+"\n";
             strList[ui->spinBox->value()-1]=strNew;
             QTextStream stream(&file);
             ui->plainTextEdit->clear();
             foreach (QString s, strList ) {
                 stream<<s;
                 ui->plainTextEdit->insertPlainText(s);
             }
         }
         file.close();

     }
     memory.clear();

}
