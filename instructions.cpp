#include "instructions.h"
#include "ui_instructions.h"
#include <QTextStream>
#include <QFile>
#include <QStringList>

Instructions::Instructions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instructions)
{
    ui->setupUi(this);
    ui->textEdit->showMaximized();

    QFile file("Text.docx");
    QTextStream stream(&file);
    QStringList strList;
    if ((file.exists()&&(file.open(QIODevice::ReadOnly))))
    {
        while(!file.atEnd())
        {
            strList<<file.readLine();
        }
        foreach (QString s, strList) {
            ui->textEdit->setText(s);
        }
    }
    file.close();

}

Instructions::~Instructions()
{
    delete ui;
}
