#include "speinform.h"
#include "ui_speinform.h"
#include"mainwindow.h"
extern Student *head;
extern QString modifyStuNum;
speInform::speInform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::speInform)
{
    ui->setupUi(this);
    speInform::setFixedSize(689,355);
    speInform::setWindowTitle("查看信息");
    qDebug()<<"1";
    Student *p=head;
    while(p->num!=modifyStuNum)
        p=p->next;
    ui->name->setText(p->name);
    ui->academy->setText(p->academy);
    ui->sex->setText(p->sex);
    ui->num->setText(p->num);
    ui->tele->setText(p->telenum);
    ui->address->setText(p->address);
    ui->email->setText(p->email);
    ui->QQ->setText(p->QQ);
    ui->VX->setText(p->VX);
}

speInform::~speInform()
{
    delete ui;
}

void speInform::on_pushButton_clicked()
{
    close();
}
