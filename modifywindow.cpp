#include "modifywindow.h"
#include"mainwindow.h"
#include "ui_modifywindow.h"
#include<QMessageBox>
Student *p;
QString numStr;
extern Student *head;
extern QString modifyStuNum;
extern QString academyName[100];
extern bool illegalInput(int,QString);
extern bool numSame(QString);
extern bool isNum(char);
enum Pattern{inputIsEmpty,noAllNumbers};
modifyWindow::modifyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyWindow)
{
    ui->setupUi(this);
    setWindowFlags((windowFlags() & ~Qt::WindowCloseButtonHint));
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint));
    setWindowTitle("修改信息");
    modifyWindow::setFixedSize(689,355);
    p=head;
    while(p->num!=modifyStuNum)
        p=p->next;
    ui->nameEdit->setText(p->name);
    ui->numEdit->setText(p->num);
    ui->teleEdit->setText(p->telenum);
    ui->addEdit->setText(p->address);
    ui->emailEdit->setText(p->email);
    ui->QQEdit->setText(p->QQ);
    ui->VXEdit->setText(p->VX);
    numStr=p->num;
    p->num="_____";
    QStringList sexList;
    if(p->sex=="男")
        sexList<<"男"<<"女";
    else
        sexList<<"女"<<"男";
    ui->sexComboBox->addItems(sexList);
    QStringList acaList;
    ui->acaComboBox->addItem(p->academy);
    for(int i=0;academyName[i]!='\0';i++)
    {
        if(academyName[i]!=p->academy)
                ui->acaComboBox->addItem(academyName[i]);
    }
}

modifyWindow::~modifyWindow()
{
    delete ui;
}

void modifyWindow::on_OKbtn_clicked()
{
    if(illegalInput(inputIsEmpty,ui->nameEdit->text()))
    {
        QMessageBox::question(this,"提示！","未输入姓名！",QMessageBox::Ok);
        ui->nameEdit->clear();
    }
    else if(illegalInput(inputIsEmpty,ui->numEdit->text()))
    {
        QMessageBox::question(this,"提示！","未输入学号！",QMessageBox::Ok);
        ui->numEdit->clear();
    }
    else if(illegalInput(inputIsEmpty,ui->teleEdit->text()))
    {
        QMessageBox::question(this,"提示！","未输入电话号码！",QMessageBox::Ok);
        ui->teleEdit->clear();
    }
    else if(illegalInput(noAllNumbers,ui->numEdit->text()))
    {
        QMessageBox::question(this,"提示！","学号存在非法字符！(仅允许数字0-9)",QMessageBox::Ok);
        ui->numEdit->clear();
    }
    else if(illegalInput(noAllNumbers,ui->teleEdit->text()))
    {
        QMessageBox::question(this,"提示！","电话号码存在非法字符！(仅允许数字0-9)",QMessageBox::Ok);
        ui->teleEdit->clear();
    }
    else if(numSame(ui->numEdit->text()))
        QMessageBox::question(this,"提示！","库中已存在该学号，请检查是否输入有误！",QMessageBox::Ok);
    else if(illegalInput(inputIsEmpty,ui->addEdit->text()))
    {
        QMessageBox::question(this,"提示！","未输入地址！",QMessageBox::Ok);
        ui->addEdit->clear();
    }
    else if(illegalInput(inputIsEmpty,ui->emailEdit->text()))
    {
        QMessageBox::question(this,"提示！","未输入邮箱！",QMessageBox::Ok);
        ui->emailEdit->clear();
    }
    else if(ui->QQEdit->text()!="无"&&illegalInput(noAllNumbers,ui->QQEdit->text()))
    {
        QMessageBox::question(this,"提示！","QQ存在非法字符！(仅允许数字0-9)",QMessageBox::Ok);
        ui->QQEdit->clear();
    }
    else
    {
        p->name=ui->nameEdit->text();
        p->num=ui->numEdit->text();
        p->sex=ui->sexComboBox->currentText();
        p->academy=ui->acaComboBox->currentText();
        p->telenum=ui->teleEdit->text();
        p->address=ui->addEdit->text();
        p->email=ui->emailEdit->text();
        if(illegalInput(inputIsEmpty,ui->QQEdit->text()))
            p->QQ="无";
        else
            p->QQ=ui->QQEdit->text();
        if(illegalInput(inputIsEmpty,ui->VXEdit->text()))
            p->VX="无";
        else
            p->VX=ui->VXEdit->text();
        QMessageBox::question(this,"提示！","修改成功！",QMessageBox::Ok);
        close();
    }
}

void modifyWindow::on_cancelBtn_clicked()
{
    p->num=numStr;
    close();
}
