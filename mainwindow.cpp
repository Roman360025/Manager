#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buyediting.h"
#include "dialog.h"
#include "addbuy.h"
#include "fees.h"
#include "donate.h"
#include "donateedite.h"
#include "instructions.h"
#include "statistic.h"
#include "othforwhile.h"
#include <QQueue>
#include <QFile>
#include <buy.h>
#include <QTextStream>
QQueue<buy *>memory;
QQueue<buy *>memory_2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setDefault(true);  //Делаем кнопку по-умолчанию
    ui->pushButton->setEnabled(true); //Делаем её активной

    //Устанавливаем границы выбора промежутка расчёта
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit_2->setMaximumDate(QDate::currentDate());

    ui->pushButton->setToolTip("Рассчитает выручку за промежуток времени между\n первой и второй датами, введёнными выше");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered() //Окно для добавления покупок
{
    addbuy *wnd=new addbuy(this);
    wnd->show();
}


void MainWindow::on_pushButton_clicked() //Слот нажатия на кнопку
{
    float sum=0; //Перменная для накопления выручки
    if (memory.empty()&&memory_2.empty())
    {
        QFile file("buy.txt");
        if ((file.exists()&&(file.open(QIODevice::ReadOnly))))
        {   //Создадим переменные для сохранения промежуточных данных
            QString str="";
            QString strDate="";
            QString strValue="";
            QString strName="";
            int n=0;
            while(!file.atEnd()) //Считываем даные с файла
            {
                    str=file.readLine();
                    buy *purchase=new buy();
                    strDate=str.left(10);
                    purchase->set_date(QDate::fromString(strDate,"dd.MM.yyyy"));
                    strValue=str.mid(11,str.indexOf(" ",11)-10);
                    strName=str.mid(str.indexOf(" ",11)+1);
                    n=strName.size();
                    strName=strName.mid(0,n);
                    purchase->set_value(strValue.toFloat());
                    purchase->set_name(strName);
                    memory.enqueue(purchase);
            }
        }
        file.close();
    }
    //Считываем даты
    QDate date1=ui->dateEdit->date();
    QDate date2=ui->dateEdit_2->date();

    if (date1>date2) /*Делаем так, чтобы date1<=date2 для удабства расчёта*/
    {
        QDate d=date1;
        date1=date2;
        date2=d;
    }

    while(!memory.empty()) /*Цикл  для расчёта выручки*/
    {
        memory_2.enqueue(memory.head());
        if((memory.head()->get_date()>=date1)&&(memory.head()->get_date()<=date2))
            sum+=memory.head()->get_value();
        memory.dequeue();
    }
    if (memory.empty()&&!memory_2.empty())/*Если основной контейнер пуст, то из запасного перекидываем данные в основной*/
        memory.swap(memory_2);
   memory_2.clear();

    QString str1=QString("%1").arg(sum);/*Переводим выручку в строковый тип*/
    ui->lineEdit->setText(str1);/*Выводим выручку на экран*/
}

void MainWindow::on_action_2_triggered()/*Окно для расчёта сборов пожертвований*/
{
    fees *wnd=new fees(this);
    wnd->show();
}

void MainWindow::on_action_3_triggered() /*Окно для добавления покупок*/
{
    donate *wnd=new donate(this);
    wnd->show();
}

void MainWindow::on_action_4_triggered()/*Окно редактирования покупок*/
{
    buyEditing *wnd=new  buyEditing(this);
    wnd->show();



}

void MainWindow::on_action_5_triggered()/*Окно редактирования пожертвования*/
{
    donateEdite *wnd=new donateEdite(this);
    wnd->show();
}

void MainWindow::on_action_6_triggered()
{
    Instructions *wnd=new Instructions(this);
    wnd->show();

}

void MainWindow::on_action_7_triggered() /*Окно статистики*/
{
    statistic *wnd=new statistic(this);
    wnd->show();
}

void MainWindow::on_action_8_triggered() /*Окно отчёта*/
{
    othforwhile *wnd=new othforwhile(this);
    wnd->show();
}


