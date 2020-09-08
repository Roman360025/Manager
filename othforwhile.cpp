#include "othforwhile.h"
#include "ui_othforwhile.h"
#include "popbuy.h"
#include <QFile>
#include <QDate>
extern quicksort(std::vector<popbuy *> a, int first, int last );


othforwhile::othforwhile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::othforwhile)
{
    ui->setupUi(this);
}

othforwhile::~othforwhile()
{
    delete ui;
}

void othforwhile::on_pushButton_clicked() //Слот нажатия на кнопку
{
    ui->textEdit->clear(); //Очищаем область вывода
    QFile file("buy.txt");

    if(file.open(QIODevice::ReadOnly)&&file.exists())
    {
          //Считываем данные введённые пользователем
        QDate date1=ui->dateEdit->date();
        QDate date2=ui->dateEdit_2->date();

        if (date1>date2)  /*Делаем так, чтобы date1<=date2 для удабства расчёта*/
        {
            QDate d=date1;
            date1=date2;
            date2=d;
        }

        //Создадим переменные для сохранения промежуточных данных
        QString strDate="";
        QString strName="";
        QString strValue="";
        QString str;
        bool flag=false;
        int kol=0; //Переменная для подсчёта количества нужных товаров
        int n=0;
        std::vector<popbuy *> basket; //Сюда будем складывать необходимые объекты
        while(!file.atEnd()) //Считываем необходимые товары из файла
        {
            str=file.readLine();
            strDate=str.left(10);
            QDate date=QDate::fromString(strDate, "dd.MM.yyyy");
            //Условие для сохранения объектов в векторе
            if(date>=date1&&date<=date2) {
                flag=false;
                kol++;
                strName=str.mid(str.indexOf(" ",11)+1);
                n=strName.size();
                strName=strName.mid(0,n);
                strValue=str.mid(11,str.indexOf(" ",11)-10);
                float value=strValue.toFloat();
                for(unsigned int i=0;i<basket.size();i++) //Цикл для поиска одинаковых товаров
                {
                    if(basket.at(i)->get_name()==strName)
                    {
                        //Ищем максимальные и минимальные цены товаров, и время когда они были куплены
                        if(value<=basket.at(i)->get_min())
                        {
                            if(value==basket.at(i)->get_min()&&date>basket.at(i)->get_dmin())
                                basket.at(i)->set_dmin(date);
                            else{
                                basket.at(i)->set_min(value);
                                basket.at(i)->set_dmin(date);
                            }
                        }
                        else if(value>=basket.at(i)->get_max())
                        {
                            if(value==basket.at(i)->get_max()&&date>basket.at(i)->get_dmax())
                                basket.at(i)->set_dmax(date);
                            else {
                                basket.at(i)->set_max(value);
                                basket.at(i)->set_dmax(date);
                            }
                        }
                        basket.at(i)->inc_pop();
                        flag=true;
                        break;
                     }
            }
                if(!flag) //Если попался новый товар, то сохраняем его в векторе
                {
                    popbuy *purchase=new popbuy();
                    purchase->set_name(strName);
                    purchase->inc_pop();
                    purchase->set_max(value);
                    purchase->set_min(value);
                    purchase->set_dmin(date);
                    purchase->set_dmax(date);
                    basket.push_back(purchase);
                }
        }
    }
         //Выводим необходимые данные на экран
        if (!basket.empty())
        {
            ui->textEdit->insertPlainText(trUtf8("Отчёт по продажам"));
             ui->textEdit->insertPlainText("");
            sort(basket.begin(), basket.end());
            QString s="Всего продано товаров:";
            QString svalue;
            s=s+svalue.setNum(kol);
             ui->textEdit->append(s);
            ui->textEdit->append("");
            ui->textEdit->append(trUtf8("Продынные товары, скидки и наценки:"));
            for(unsigned int i=0;i<basket.size();i++)
            {
                 int value=basket.at(i)->get_pop();
                 strName=basket.at(i)->get_name();
                strName[strName.size()-1]='\0';
                strName[strName.size()-2]='\0';
                s=strName+" sold "+svalue.setNum(value);
                if (basket.at(i)->get_max()==basket.at(i)->get_min())
                {
                  s=s+", нет скидок и наценок";
                 }
                 else if(basket.at(i)->get_dmin()<basket.at(i)->get_dmax())
                {
                    int tnp=floor((basket.at(i)->get_max()-basket.at(i)->get_min())*100/basket.at(i)->get_min()+0.5);
                     s=s+", повышение цены составило "+svalue.setNum(tnp)+"%";
                 }
                else if(basket.at(i)->get_dmin()>basket.at(i)->get_dmax())
                {
                      int tnp=floor(basket.at(i)->get_min()*100/basket.at(i)->get_max()+0.5);
                     s=s+", уменьшение цены составило "+svalue.setNum(tnp)+"%";
                }
                 else if(basket.at(i)->get_dmax()==basket.at(i)->get_dmax())
                {
                     int tnp=basket.at(i)->get_max()-basket.at(i)->get_min();
                     s=s+" , цена изменилась на"+svalue.setNum(tnp);
                }
                 ui->textEdit->append(s);
            }
             }
        else ui->textEdit->setPlainText("Нет таких товаров");
}
    file.close();
}
