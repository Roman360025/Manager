#include "statistic.h"
#include "ui_statistic.h"
#include "buy.h"
#include "popbuy.h"
#include <QFile>

void quicksort(std::vector<popbuy *> a, int first, int last )
{
    int i=first, j=last,  x=a.at((i+j)/2)->get_pop();
    do
    {
        while (a.at(i)->get_pop()<x) i++;
        while(a.at(j)->get_pop()>x) j--;

        if(i<=j) {
            if(i<j)
            {
                QString name;
                int pop;
                float xmin;
                float xmax;
                QDate date1;
                QDate date2;
                pop=a.at(i)->get_pop();
                name=a.at(i)->get_name();
                xmin=a.at(i)->get_min();
                xmax=a.at(i)->get_max();
                date1=a.at(i)->get_dmin();
                date2=a.at(i)->get_dmax();
                a.at(i)->set_name(a.at(j)->get_name());
                a.at(i)->set_pop(a.at(j)->get_pop());
                a.at(i)->set_dmin(a.at(j)->get_dmin());
                a.at(i)->set_dmax(a.at(j)->get_dmax());
                a.at(i)->set_min(a.at(j)->get_min());
                a.at(i)->set_max(a.at(j)->get_max());
                a.at(j)->set_name(name);
                a.at(j)->set_pop(pop);
                a.at(j)->set_dmin(date1);
                a.at(j)->set_dmax(date2);
                a.at(j)->set_min(xmin);
                a.at(j)->set_max(xmax);
            }
            i++;
            j--;
        }
    } while(i<=j);
    if(i<last)
        quicksort(a, i, last);
    if(first<j)
        quicksort(a, first, j);
}

statistic::statistic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistic)
{
    ui->setupUi(this);

    ui->pushButton->setDefault(true);  //Делаем кнопку по-умолчанию
    ui->pushButton->setEnabled(true); //Делаем её активной

    //Устанавливаем границы выбора промежутка расчёта
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit_2->setMaximumDate(QDate::currentDate());
}

statistic::~statistic()
{
    delete ui;
}

void statistic::on_pushButton_clicked() //Слот нажатия на кнопку
{
    ui->textEdit->clear(); //Очищаем область вывода
    QFile file("buy.txt");
    int kol=0;//Переменная для подсчёта количества нужных товаров
    if ((file.exists()&&(file.open(QIODevice::ReadOnly))))
    {
        //Считываем данные введённые пользователем
        QDate date1=ui->dateEdit->date();
        QDate date2=ui->dateEdit_2->date();

        if (date1>date2) /*Делаем так, чтобы date1<=date2 для удабства расчёта*/
        {
            QDate d=date1;
            date1=date2;
            date2=d;
        }

        //Создадим переменные для сохранения промежуточных данных
        QString strDate="";
        QString strName="";
        QString str;
        //Сюда будем складывать необходимые объекты
        std::vector<popbuy *> basket;
        int n=0;
        bool flag=false;
        while(!file.atEnd()) //Считываем необходимые товары из файла
        {
            str=file.readLine();
            strDate=str.left(10);
            QDate date=QDate::fromString(strDate, "dd.MM.yyyy");
            flag=false;
            //Условие для сохранения объектов в векторе
            if (date>=date1&&date<=date2) {
                strName=str.mid(str.indexOf(" ",11)+1);
                n=strName.size();
                strName=strName.mid(0,n);
                for(unsigned int i=0; i<basket.size(); i++) //Цикл для поиска одинаковых товаров
                {
                    if(basket.at(i)->get_name()==strName)
                    {
                        basket.at(i)->inc_pop();
                        flag=true;
                        break;
                    }
                }
                if (!flag) //Если попался новый товар, то сохраняем его в векторе
                {
                     popbuy *purchase=new popbuy();
                     purchase->set_name(strName);
                     purchase->inc_pop();
                     basket.push_back(purchase);
                     kol++;
                }
            }
        }
        if (!basket.empty()){ //Если контейнер не пуст, то выводим данные
            sort(basket.begin(), basket.end());
        ui->textEdit->insertPlainText("Статистика популярности продажи товаров от общего числа прожа за введённый период :");
        for(unsigned int i=0;i<basket.size();i++) {
            int part=floor((basket.at(i)->get_pop()*100/kol)+0.5);
            QString svalue;
            svalue.setNum(part);
            QString name=basket.at(i)->get_name();
            name[name.size()-1]='\0';
            name[name.size()-2]='\0';
            QString s=name+" "+svalue+"%";
            ui->textEdit->append(s);
        }
        }
        else ui->textEdit->insertPlainText("Нет продуктов в данный период"); //Иначе выводим на экран, что таких товаров нет
    }
    file.close();
}
