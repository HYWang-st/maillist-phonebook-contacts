#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"modifywindow.h"
#include"band.h"
#include"speinform.h"
void ctrl_acaWidget(Ui::MainWindow *,int);
void ctrl_broWidget(Ui::MainWindow *,int,int,int);
void cho_find(bool,Ui::MainWindow *);
extern bool illegalInput(int,QString);
extern bool numSame(QString);
extern bool isNum(char);
void emptyTheList();
extern Student *head=NULL;
extern QString modifyStuNum=" ";
extern QString academyName[100]={"\0"};
Student selected[3000];
char inputJudge[10]={'0','1','2','3','4','5','6','7','8','9'};
int judgeButtonCondition=-1;//判断按钮的禁用状态，其中的数字序号对应被禁用的按钮
void buttonEnabled(Ui::MainWindow *UI);
void fileSave();
void stanum();
void data_lead_in(QString str);
void Export();
enum Button{addbutton,findbutton,brobutton,stabutton,setbutton};
enum Pattern{inputIsEmpty,noAllNumbers};
enum Sort{num_AscendingOrder,name_AscendingOrder,num_DescendingOrder,name_DescendingOrder};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    setWindowFlags((windowFlags() & ~Qt::WindowCloseButtonHint));
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint));
    MainWindow::setFixedSize(1524,823);
    buttonEnabled(ui);//对按钮图像初始化
    academyName[0]="计算机学院";
    academyName[1]="心理学院";
    academyName[2]="历史学院";
    academyName[3]="外文学院";
    academyName[4]="马克思学院";
    QFile file("../maillist/nameList.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::question(this,"提示！","数据初始化失败！",QMessageBox::Ok);
    }
    else
    {
    QByteArray array=file.readAll();
    QString data_in=QString(array);
    data_lead_in(data_in);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_addbutton_clicked()
{
    buttonEnabled(ui);
    judgeButtonCondition=addbutton;
    ui->stustack->setCurrentIndex(1);
    ui->addbutton->setStyleSheet("QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disabledbutton.jpg)};");
    ui->addbutton->setDisabled(1);
    ui->acacombo->clear();
    for(int i=0;academyName[i]!="\0";i++)
        ui->acacombo->addItem(academyName[i]);
}

void MainWindow::on_findbutton_clicked()
{
    buttonEnabled(ui);
    judgeButtonCondition=findbutton;
    ui->stustack->setCurrentIndex(2);
    ui->findbutton->setStyleSheet("QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disfind.jpg)};");
    ui->findbutton->setDisabled(1);
    ui->del_in_find_btn->setDisabled(1);
    ui->change_btn->setDisabled(1);
    ui->del_tableWidget->setRowCount(0);
    ui->change_btn->setText("修改");
    ui->to_del_btn->setStyleSheet("QPushButton{"
                                  "border-image:url(:/new/prefix1/MailList_photos/combtn1.jpg)}"
                                  "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovbtn1.jpg)}"
                                  "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/pressbtn1.jpg)};");
    ui->to_find_btn->setStyleSheet("QPushButton{"
                                  "border-image:url(:/new/prefix1/MailList_photos/combtn2.jpg)}"
                                  "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovbtn2.jpg)}"
                                  "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/pressbtn2.jpg)};");
}

void MainWindow::on_brobutton_clicked()
{
    ui->brotablewidget->setStyleSheet("background-color:rgba(0,0,0,0)");
    ui->bro_pre->setStyleSheet("QPushButton{"
                               "border-image:url(:/new/prefix1/MailList_photos/comLarrow.jpg)}"
                               "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovLarrow.jpg)}"
                               "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/disLarrow.jpg)}"
                               "QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disLarrow.jpg)};");
    ui->bro_next->setStyleSheet("QPushButton{"
                               "border-image:url(:/new/prefix1/MailList_photos/comRarrow.jpg)}"
                               "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovRarrow.jpg)}"
                               "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/disRarrow.jpg)}"
                               "QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disRarrow.jpg)};");
    ui->brotablewidget->setRowCount(0);
    buttonEnabled(ui);
    judgeButtonCondition=brobutton;
    ui->stustack->setCurrentIndex(3);
    ui->brobutton->setStyleSheet("QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disbro.jpg)};");
    ui->brobutton->setDisabled(1);
    Student *p=head;
    if(head==NULL)
    {
        ui->brotablewidget->setColumnCount(1);
        ui->brotablewidget->setHorizontalHeaderLabels(QStringList()<<" ");
        ui->brotablewidget->verticalHeader()->setHidden(1);
        ui->brotablewidget->setRowCount(1);
        ui->brotablewidget->setItem(0,0,new QTableWidgetItem("暂无学生信息"));
        ui->bro_pre->setDisabled(1);
        ui->bro_next->setDisabled(1);
    }
    else
    {
        ui->brotablewidget->setColumnCount(7);
        ui->brotablewidget->setHorizontalHeaderLabels(QStringList()<<" "<<"序号"<<"姓名"<<"性别"<<"学号"<<"学院"<<"电话");
        int sum=0;
        while (p!=NULL)
        {
            sum++;
            p=p->next;
        }
        ctrl_broWidget(ui,0,sum,sum%10==0?sum/10:sum/10+1);
    }
}
QString cur_text="全选";
void MainWindow::on_stabutton_clicked()
{
    buttonEnabled(ui);
    judgeButtonCondition=stabutton;
    ui->prebtn->setStyleSheet("QPushButton{"
                               "border-image:url(:/new/prefix1/MailList_photos/comLarrow.jpg)}"
                               "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovLarrow.jpg)}"
                               "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/disLarrow.jpg)}"
                               "QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disLarrow.jpg)};");
    ui->nextbtn->setStyleSheet("QPushButton{"
                               "border-image:url(:/new/prefix1/MailList_photos/comRarrow.jpg)}"
                               "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovRarrow.jpg)}"
                               "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/disRarrow.jpg)}"
                               "QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disRarrow.jpg)};");
    ui->stustack->setCurrentIndex(5);
    ui->stabutton->setStyleSheet("QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/dissta.jpg)};");
    ui->stabutton->setDisabled(1);
    QProgressBar *probar_male=new QProgressBar(ui->sumWidget);
    QProgressBar *probar_female=new QProgressBar(ui->sumWidget);
    probar_male->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{background:azure}");
    probar_female->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{background:pink}");
    ui->sumWidget->verticalHeader()->setHidden(1);
    ui->sumWidget->setColumnCount(4);
    ui->sumWidget->setRowCount(2);
    ui->sumWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->sumWidget->setHorizontalHeaderLabels(QStringList()<<"性别"<<"比例"<<"人数"<<"总人数");
    ui->sumWidget->setCellWidget(0,1,probar_male);
    ui->sumWidget->setCellWidget(1,1,probar_female);
    ui->sumWidget->setItem(0,0,new QTableWidgetItem("男"));
    ui->sumWidget->setItem(1,0,new QTableWidgetItem("女"));
    int sum=0,maleNum=0;
    Student *p=head;
    if(p==NULL){}
    else
    {
        while(p!=NULL)
        {
            if(p->sex=="男")
                maleNum++;
            sum++;
            p=p->next;
        }
    }
    probar_male->setMaximum(sum);
    probar_female->setMaximum(sum);
    probar_male->setValue(maleNum);
    probar_female->setValue(sum-maleNum);
    ui->sumWidget->setItem(0,2,new QTableWidgetItem(QString::number(maleNum)));
    ui->sumWidget->setItem(1,2,new QTableWidgetItem(QString::number(sum-maleNum)));
    ui->sumWidget->setItem(0,3,new QTableWidgetItem(QString::number(sum)));
    ctrl_acaWidget(ui,0);
}

void MainWindow::on_setbutton_clicked()
{
    buttonEnabled(ui);
    judgeButtonCondition=setbutton;
    ui->stustack->setCurrentIndex(6);
    ui->setbutton->setStyleSheet("QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disset.jpg)};");
    ui->setbutton->setDisabled(1);
    ui->addAcademy->setEnabled(1);
    ui->lineEdit->setVisible(0);
    ui->pushButton->setVisible(0);
    ui->pushButton_2->setVisible(0);
    ui->importLineEdit->setVisible(0);
    ui->out_putlLineEdit->setVisible(0);
}

void MainWindow::on_exitbutton_clicked()//退出按钮程序框
{
    int ret=QMessageBox::question(this,"退出程序","确认退出？");
    switch (ret)
    {
        case QMessageBox::Yes:
            Export();
        emptyTheList();
        QMainWindow::close();
            break;
        case QMessageBox::No:
            break;
    }
}
void buttonEnabled(Ui::MainWindow *UI)//启用按钮，使页面可以相互跳转
{
    switch (judgeButtonCondition)
    {
    case addbutton:
        UI->addbutton->setEnabled(1);
        UI->addbutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/commonbutton.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hoveraddbutton.jpg)};");
        break;
    case findbutton:
        UI->findbutton->setEnabled(1);
        UI->findbutton->setStyleSheet("QPushButton{"
                                      "border-image:url(:/new/prefix1/MailList_photos/comfind.jpg)}"
                                      "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovfind.jpg)};");
        break;
    case brobutton:
        UI->brobutton->setEnabled(1);
        UI->brobutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/combro.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovbro.jpg)};");
        break;
    case stabutton:
        UI->stabutton->setEnabled(1);
        UI->stabutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/comsta.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovsta.jpg)};");
        break;
    case setbutton:
        UI->setbutton->setEnabled(1);
        UI->setbutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/comset.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovset.jpg)};");
        break;
    default://初始状态
        UI->addbutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/commonbutton.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hoveraddbutton.jpg)};");
        UI->stabutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/comsta.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovsta.jpg)};");
        UI->setbutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/comset.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovset.jpg)};");
        UI->exitbutton->setStyleSheet("QPushButton{"
                                      "border-image:url(:/new/prefix1/MailList_photos/comexit.jpg)}"
                                      "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovexit.jpg)}"
                                      "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/disexit.jpg)};");
        UI->brobutton->setStyleSheet("QPushButton{"
                                     "border-image:url(:/new/prefix1/MailList_photos/combro.jpg)}"
                                     "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovbro.jpg)};");
        UI->findbutton->setStyleSheet("QPushButton{"
                                      "border-image:url(:/new/prefix1/MailList_photos/comfind.jpg)}"
                                      "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovfind.jpg)};");
        UI->addokbutton->setStyleSheet("QPushButton{"
                          "border-image:url(:/new/prefix1/MailList_photos/addokcom.jpg)}"
                          "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/addokhov.jpg)}"
                                       "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/addokpressed.jpg)};");
        break;
    }
}

void MainWindow::on_addokbutton_clicked()
{
        if(illegalInput(inputIsEmpty,ui->nameedit->text()))
        {
            QMessageBox::question(this,"提示！","未输入姓名！",QMessageBox::Ok);
            ui->nameedit->clear();
        }
        else if(illegalInput(inputIsEmpty,ui->numedit->text()))
        {
            QMessageBox::question(this,"提示！","未输入学号！",QMessageBox::Ok);
            ui->numedit->clear();
        }
        else if(illegalInput(inputIsEmpty,ui->teleedit->text()))
        {
            QMessageBox::question(this,"提示！","未输入电话号码！",QMessageBox::Ok);
            ui->teleedit->clear();
        }
        else if(illegalInput(noAllNumbers,ui->numedit->text()))
        {
            QMessageBox::question(this,"提示！","学号存在非法字符！(仅允许数字0-9)",QMessageBox::Ok);
            ui->numedit->clear();
        }
        else if(illegalInput(noAllNumbers,ui->teleedit->text()))
        {
            QMessageBox::question(this,"提示！","电话号码存在非法字符！(仅允许数字0-9)",QMessageBox::Ok);
            ui->teleedit->clear();
        }
        else if(numSame(ui->numedit->text()))
            QMessageBox::question(this,"提示！","库中已存在该学号，请检查是否输入有误！",QMessageBox::Ok);
        else if(illegalInput(inputIsEmpty,ui->addedit->text()))
        {
            QMessageBox::question(this,"提示！","未输入地址！",QMessageBox::Ok);
            ui->addedit->clear();
        }
        else if(illegalInput(inputIsEmpty,ui->emailedit->text()))
        {
            QMessageBox::question(this,"提示！","未输入邮箱！",QMessageBox::Ok);
            ui->emailedit->clear();
        }
        else if(illegalInput(noAllNumbers,ui->QQedit->text()))
        {
            QMessageBox::question(this,"提示！","QQ存在非法字符！(仅允许数字0-9)",QMessageBox::Ok);
            ui->QQedit->clear();
        }
        else
        {
            Student *current,*previous;
            current=new Student;
            if(head==NULL)
            {
                head=current;
            }
            else
            {
                previous=head;
                while(previous->next!=NULL)
                previous=previous->next;
                previous->next=current;
            }
            current->next=NULL;
            current->name=ui->nameedit->text();
            current->sex=ui->sexcombo->currentText();
            current->num=ui->numedit->text();
            current->academy=ui->acacombo->currentText();
            current->telenum=ui->teleedit->text();
            current->address=ui->addedit->text();
            current->email=ui->emailedit->text();
            if(illegalInput(inputIsEmpty,ui->QQedit->text()))
                current->QQ="无";
            else
                current->QQ=ui->QQedit->text();
            if(illegalInput(inputIsEmpty,ui->VXedit->text()))
                current->VX="无";
            else
                current->VX=ui->VXedit->text();
            ui->nameedit->clear();
            ui->numedit->clear();
            ui->teleedit->clear();
            ui->addedit->clear();
            ui->emailedit->clear();
            ui->QQedit->clear();
            ui->VXedit->clear();
            QMessageBox::question(this,"提示","学生信息录入成功！",QMessageBox::Ok);
        }
}


bool numSame(QString n)//检索学号相同的情况,有相同情况返回TRUE
{
    Student *pStu=head;
    if(head==NULL)
        return 0;
    else
    {
        while(pStu!=NULL)
        {
            if(pStu->num==n)
                return 1;
            pStu=pStu->next;
        }
        return 0;
    }
}
void ctrl_acaWidget(Ui::MainWindow *ui,int AddOrMinus)
{
    int comboIndex=ui->acacombo->count();
    static int curIndex=0;
    if(AddOrMinus==0)
        curIndex=0;
    else
        curIndex+=AddOrMinus;
    ui->academy->setText(academyName[curIndex]);
    if(curIndex==0)
        ui->prebtn->setDisabled(1);
    else
    {
        ui->prebtn->setEnabled(1);
        ui->nextbtn->setStyleSheet("QPushButton{"
                                   "border-image:url(:/new/prefix1/MailList_photos/comRarrow.jpg)}"
                                   "QPushButton:hover{border-image:url(:/new/prefix1/MailList_photos/hovRarrow.jpg)}"
                                   "QPushButton:pressed{border-image:url(:/new/prefix1/MailList_photos/disRarrow.jpg)}"
                                   "QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disRarrow.jpg)};");
    }
    if(curIndex==comboIndex-1)
    {
        ui->nextbtn->setDisabled(1);
        ui->nextbtn->setStyleSheet("QPushButton:disabled{border-image:url(:/new/prefix1/MailList_photos/disRarrow.jpg)};");
    }
    else
        ui->nextbtn->setEnabled(1);
    int sum=0,maleNum=0;
    Student *p=head;
    if(p==NULL){}
    else
    {
        while(p!=NULL)
        {
            if(p->sex=="男"&&p->academy==academyName[curIndex])
            {
                maleNum++;
                sum++;
            }
            else if(p->sex=="女"&&p->academy==academyName[curIndex])
                sum++;
            p=p->next;
        }
    }
    QProgressBar *probar_male=new QProgressBar(ui->acaWidget);
    QProgressBar *probar_female=new QProgressBar(ui->acaWidget);
    probar_male->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{background:azure}");
    probar_female->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{background:pink}");
    ui->acaWidget->verticalHeader()->setHidden(1);
    ui->acaWidget->setColumnCount(4);
    ui->acaWidget->setRowCount(2);
    ui->acaWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->acaWidget->setHorizontalHeaderLabels(QStringList()<<"性别"<<"比例"<<"人数"<<"总人数");
    ui->acaWidget->setCellWidget(0,1,probar_male);
    ui->acaWidget->setCellWidget(1,1,probar_female);
    ui->acaWidget->setItem(0,0,new QTableWidgetItem("男"));
    ui->acaWidget->setItem(1,0,new QTableWidgetItem("女"));
    probar_male->setMaximum(sum);
    probar_female->setMaximum(sum);
    probar_male->setValue(maleNum);
    probar_female->setValue(sum-maleNum);
    ui->acaWidget->setItem(0,2,new QTableWidgetItem(QString::number(maleNum)));
    ui->acaWidget->setItem(1,2,new QTableWidgetItem(QString::number(sum-maleNum)));
    ui->acaWidget->setItem(0,3,new QTableWidgetItem(QString::number(sum)));
}
void MainWindow::ctrl_broWidget(Ui::MainWindow *ui,int changePage,int sum=0,int sP=0)//用代码写出翻页效果
{
    static int Sum=0;
    if(sum!=0)
        Sum=sum;
    static int sumPage=0;
    if(sP!=0)
        sumPage=sP;
    static int stuSerialNum=0;//序号
    static Student *pt=head;//每页的头结点记录
    static int page=1;
    if(changePage==0)
    {
        page=1;
        pt=head;
        stuSerialNum=0;
    }
    else if(changePage==-1)//上一页，让指针回溯到上一页首部
    {
        page+=changePage;
        int n=stuSerialNum;//获取当前最底部学生序号
        while(n%10!=1)//获得最顶部学生序号
            n-=1;
        int D_value=stuSerialNum-n+10;//获取差值
        stuSerialNum=n-11;
        Student *p1=head;
        Student *p2=head;
        Student *p3;
        while(p1->next!=pt)
        {
            p1=p2;
            for(int i=1;i<=D_value;i++)
                p1=p1->next;
            p3=p2;
            p2=p2->next;
        }
        pt=p3;
    }
    else//下一页
        page+=changePage;
    if(page==1)
        ui->bro_pre->setDisabled(1);
    else
        ui->bro_pre->setEnabled(1);
    if(page==sumPage)
        ui->bro_next->setDisabled(1);
    else
        ui->bro_next->setEnabled(1);
    QString string="第"+QString::number(page)+"/"+QString::number(sumPage)+"页";
    ui->pageText->setText(string);
    int row=1;
    while(pt!=NULL&&row<=10)
    {
        ui->brotablewidget->verticalHeader()->setHidden(1);
        int rowIndex=ui->brotablewidget->rowCount();
        ui->brotablewidget->setRowCount(rowIndex+1);
        ui->brotablewidget->setRowHeight(rowIndex , 50);
        QPushButton *btn=new QPushButton(this);
        btn->setStyleSheet("QPushButton{color:white;background-color:rgb(170,170,255);font-family:黑体;border-radius: 15px;}"
                             "QPushButton:pressed{background-color:rgb(37,226,255)}");
        btn->setFixedSize(80,30);
        connect(btn,SIGNAL(clicked()),this,SLOT(create_seeWidget()));
        btn->setText("查看");
        ui->brotablewidget->setItem(rowIndex,1,new QTableWidgetItem(QString::number(++stuSerialNum)));
        QTableWidgetItem *pitem=ui->brotablewidget->item(rowIndex,1);
        pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
        ui->brotablewidget->setItem(rowIndex,2,new QTableWidgetItem(pt->name));
        pitem=ui->brotablewidget->item(rowIndex,2);
        pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
        ui->brotablewidget->setItem(rowIndex,3,new QTableWidgetItem(pt->sex));
        pitem=ui->brotablewidget->item(rowIndex,3);
        pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
        ui->brotablewidget->setItem(rowIndex,4,new QTableWidgetItem(pt->num));
        pitem=ui->brotablewidget->item(rowIndex,4);
        pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
        ui->brotablewidget->setItem(rowIndex,5,new QTableWidgetItem(pt->academy));
        pitem=ui->brotablewidget->item(rowIndex,5);
        pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
        ui->brotablewidget->setItem(rowIndex,6,new QTableWidgetItem(pt->telenum));
        pitem=ui->brotablewidget->item(rowIndex,6);
        pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
        QHBoxLayout *vLayout = new QHBoxLayout();
        QWidget *Widget_btn = new QWidget;
        vLayout->addWidget(btn);
        vLayout->addSpacing(20);
        Widget_btn->setLayout(vLayout);
        Widget_btn->setStyleSheet("QWidget{ border: 0px }");
        ui->brotablewidget->setCellWidget(rowIndex,0,Widget_btn);
        pt=pt->next;
        row++;
    }
}

void MainWindow::create_seeWidget()
{
 // 获取按钮的指针

    QPushButton *pushButton_ = dynamic_cast<QPushButton*>(this->sender());


    if(pushButton_==NULL)
    {
        return;
    }
    // 获取按钮的x坐标和y坐标
    int x = pushButton_->parentWidget()->pos().x();
    int y = pushButton_->parentWidget()->pos().y();
    // 根据按钮的x和y坐标来定位对应的单元格
    QModelIndex index = ui->brotablewidget->indexAt(QPoint(x, y));
    int row = index.row();
    modifyStuNum=ui->brotablewidget->item(row,4)->text();
    speInform s;
    s.exec();
}



void MainWindow::on_prebtn_clicked()
{
    ctrl_acaWidget(ui,-1);
}

void MainWindow::on_nextbtn_clicked()
{
    ctrl_acaWidget(ui,1);
}

void MainWindow::on_bro_pre_clicked()
{
        ui->brotablewidget->setRowCount(0);
      ctrl_broWidget(ui,-1);
}

void MainWindow::on_bro_next_clicked()
{
       ui->brotablewidget->setRowCount(0);
       ctrl_broWidget(ui,1);
}

void bubblesort(Student*p,int n,int sortMethod)
{
    if(sortMethod==num_AscendingOrder)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (p[j].num > p[j + 1].num)
                {
                    Student temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }
    else if(sortMethod==num_DescendingOrder)
    {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (p[j].num < p[j + 1].num)
                {
                    Student temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }
    else if(sortMethod==name_AscendingOrder)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (p[j].name > p[j + 1].name )
                {
                    Student temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }
    else if(sortMethod==name_DescendingOrder)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (p[j].name < p[j + 1].name )
                {
                    Student temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }
}



void cho_find(bool btnchoose,Ui::MainWindow *ui)
{
    //转录符合条件的数据
    ui->del_tableWidget->clearContents();//刷新
    QString flag_college=ui->comboBox_col->currentText();
    QString flag_sex=ui->comboBox_sex2->currentText();
    QString flag_sel=ui->comboBox_sel->currentText();
     int i=0;//存数计数
        if (head == NULL)
            {
                QTableWidgetItem *item = new QTableWidgetItem("无相关学生信息");
                ui->del_tableWidget->setItem(0,0,item); //添加到界面
            }
        else
            {
            Student* p = head;
            while (p!=NULL) {
                if (flag_college=="不限"){
                    if(flag_sex=="不限"){
                       selected[i].academy=p->academy;
                       selected[i].name=p->name;
                       selected[i].num=p->num;
                       selected[i].telenum=p->telenum;
                       selected[i].sex=p->sex;
                       i++;
                    }
                }
                if(flag_sex=="不限"){
                    if(p->academy==flag_college){
                        selected[i].academy = p->academy;
                        selected[i].name = p->name;
                        selected[i].num = p->num;
                        selected[i].telenum = p->telenum;
                        selected[i].sex = p->sex;
                        i++;
                    }
                }
                if(flag_college=="不限"){
                    if(p->sex==flag_sex){
                        selected[i].academy=p->academy;
                        selected[i].name=p->name;
                        selected[i].num=p->num;
                        selected[i].telenum=p->telenum;
                        selected[i].sex=p->sex;
                    i++;
                    }
                }
                if(p->academy==flag_college&&p->sex==flag_sex){
                    selected[i].academy=p->academy;
                    selected[i].name=p->name;
                    selected[i].num=p->num;
                    selected[i].telenum=p->telenum;
                    selected[i].sex=p->sex;
                    i++;
                }
                p=p->next;
            }
            }
        //输出前对转录的数组排序
        if(flag_sel=="姓名升序")bubblesort(selected,i,name_AscendingOrder);
        if(flag_sel=="姓名降序")bubblesort(selected,i,name_DescendingOrder);
        if(flag_sel=="学号升序")bubblesort(selected,i,num_AscendingOrder);
        if(flag_sel=="学号降序")bubblesort(selected,i,num_DescendingOrder);
        //控制输出
        ui->del_tableWidget->setRowCount(0);
        if(i==0)
        {
            ui->del_tableWidget->setColumnCount(1);
            ui->del_tableWidget->setHorizontalHeaderLabels(QStringList()<<" ");
            ui->del_tableWidget->setRowCount(1);
            ui->del_tableWidget->verticalHeader()->setHidden(1);
            ui->del_tableWidget->setItem(0,0,new QTableWidgetItem("无相关学生信息"));
            ui->del_in_del_btn->setDisabled(1);
            ui->cancel_all_btn->setDisabled(1);
            ui->all_choose_btn->setDisabled(1);
        }
        else
        {
            ui->del_tableWidget->setColumnCount(6);
            ui->del_tableWidget->setHorizontalHeaderLabels(QStringList()<<" "<<"姓名"<<"性别"<<"学号"<<"学院"<<"电话");
             for(int j=0;j<i;j++){
                 int rowIndex=ui->del_tableWidget->rowCount();
                 ui->del_tableWidget->setRowCount(rowIndex+1);
                 QTableWidgetItem *Chebox = new QTableWidgetItem();
                 Chebox->setCheckState(Qt::Checked);
                 ui->del_tableWidget->setItem(rowIndex,0,Chebox);
                 if(btnchoose==1)//默认勾选
                    Chebox->setCheckState(Qt::Checked);
                 else
                    Chebox->setCheckState(Qt::Unchecked);
                 ui->del_tableWidget->setItem(rowIndex,1,new QTableWidgetItem(selected[j].name));
                 QTableWidgetItem *pitem=ui->del_tableWidget->item(rowIndex,1);
                 pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
                 ui->del_tableWidget->setItem(rowIndex,2,new QTableWidgetItem(selected[j].sex));
                 pitem=ui->del_tableWidget->item(rowIndex,2);
                 pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
                 ui->del_tableWidget->setItem(rowIndex,3,new QTableWidgetItem(selected[j].num));
                 pitem=ui->del_tableWidget->item(rowIndex,3);
                 pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
                 ui->del_tableWidget->setItem(rowIndex,4,new QTableWidgetItem(selected[j].academy));
                 pitem=ui->del_tableWidget->item(rowIndex,4);
                 pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
                 ui->del_tableWidget->setItem(rowIndex,5,new QTableWidgetItem(selected[j].telenum));
                 pitem=ui->del_tableWidget->item(rowIndex,5);
                 pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
             }
        }
}
Student* find_stu(QString num){
     Student* p = head;
     while (p != NULL){
            if(p->num==num){
                return p;
            }
            p = p->next;}
     return NULL;
}
void _delete(Student* p)
{
    Student* pt = p;
                if (pt == NULL) {}
                else
                {
                    Student* temp = head;
                    while (temp->next != pt && temp->next != NULL)
                        temp = temp->next;
                    if (head == pt)//查找的是头结点
                    {
                        head = pt->next;
                        delete pt;
                    }
                    else if (temp->next == pt)
                    {
                        temp->next = pt->next;
                        delete pt;
                    }}
}


//以下为筛选查找
void MainWindow::on_find_btn_clicked()
{  
   ui->del_tableWidget->verticalHeader()->setHidden(1);
    ui->cancel_all_btn->setEnabled(1);
   ui->all_choose_btn->setEnabled(1);
   cho_find(0,ui);//跳转到筛选查找
}
//new
//以下为单独查找
void MainWindow::on_search_btn_clicked()
{
    ui->change_btn->setText("修改");
    ui->find_tableWidget->verticalHeader()->setHidden(1);
    ui->find_tableWidget->setRowCount(0);
    QString searchword;
    searchword=ui->serchEdit->text();
    if(searchword=='\0')
        QMessageBox::question(this,"提示","请输入姓名/学号！",QMessageBox::Ok);
    else
    {
   if (head == NULL)
       {
       ui->find_tableWidget->setColumnCount(1);
       ui->find_tableWidget->setHorizontalHeaderLabels(QStringList()<<" ");
       ui->find_tableWidget->setRowCount(1);
       ui->find_tableWidget->verticalHeader()->setHidden(1);
       ui->find_tableWidget->setItem(0,0,new QTableWidgetItem("无相关学生信息"));
       ui->del_in_find_btn->setDisabled(1);
       ui->change_btn->setDisabled(1);
       }
   else
       {
       ui->change_btn->setEnabled(1);
       ui->del_in_find_btn->setEnabled(1);
       ui->find_tableWidget->setColumnCount(6);
       ui->find_tableWidget->setHorizontalHeaderLabels(QStringList()<<" "<<"姓名"<<"性别"<<"学号"<<"学院"<<"电话");
       Student* p = head;
       bool stuIsnEmp=0;
       while (p!=NULL)
       {
            if (searchword==p->name||searchword==p->num)
            {
               int rowIndex=ui->find_tableWidget->rowCount();
               ui->find_tableWidget->setRowCount(rowIndex+1);
               QTableWidgetItem *Chebox = new QTableWidgetItem();
               ui->find_tableWidget->setItem(rowIndex,0,Chebox);
               Chebox->setCheckState(Qt::Unchecked);
               QTableWidgetItem *pitem=ui->find_tableWidget->item(rowIndex,0);
               pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
               ui->find_tableWidget->setItem(rowIndex,1,new QTableWidgetItem(p->name));
               pitem=ui->find_tableWidget->item(rowIndex,1);
               pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
               ui->find_tableWidget->setItem(rowIndex,2,new QTableWidgetItem(p->sex));
               pitem=ui->find_tableWidget->item(rowIndex,2);
               pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
               ui->find_tableWidget->setItem(rowIndex,3,new QTableWidgetItem(p->num));
               pitem=ui->find_tableWidget->item(rowIndex,3);
               pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
               ui->find_tableWidget->setItem(rowIndex,4,new QTableWidgetItem(p->academy));
               pitem=ui->find_tableWidget->item(rowIndex,4);
               pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
               ui->find_tableWidget->setItem(rowIndex,5,new QTableWidgetItem(p->telenum));
               pitem=ui->find_tableWidget->item(rowIndex,5);
               pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
               stuIsnEmp=1;
           }
               p=p->next;
       }
              if(!stuIsnEmp)
              {
                 ui->find_tableWidget->setColumnCount(1);
                 ui->find_tableWidget->setHorizontalHeaderLabels(QStringList()<<" ");
                 ui->find_tableWidget->setRowCount(1);
                 ui->find_tableWidget->verticalHeader()->setHidden(1);
                 ui->find_tableWidget->setItem(0,0,new QTableWidgetItem("无相关学生信息"));
              }


       }
    }
}

void MainWindow::on_to_del_btn_clicked()
{
    ui->del_in_del_btn->setDisabled(1);
    ui->cancel_all_btn->setDisabled(1);
    ui->all_choose_btn->setDisabled(1);
    connect(ui->del_tableWidget,&QTableWidget::cellChanged,
            [=]()
    {
        ui->del_in_del_btn->setEnabled(1);
        ui->cancel_all_btn->setEnabled(1);
        ui->all_choose_btn->setEnabled(1);
    });
    ui->del_tableWidget->setStyleSheet("background-color:rgba(0,0,0,0)");
    ui->stustack->setCurrentIndex(4);
}

void MainWindow::on_to_find_btn_clicked()
{
    ui->del_in_find_btn->setDisabled(1);
    ui->change_btn->setDisabled(1);
    ui->del_tableWidget->setRowCount(0);
    ui->change_btn->setText("修改");
    ui->find_tableWidget->setRowCount(0);
    ui->stustack->setCurrentIndex(2);
}

void MainWindow::on_all_choose_btn_clicked()
{
    ui->del_tableWidget->verticalHeader()->setHidden(1);
    cho_find(1,ui);
}

void MainWindow::on_cancel_all_btn_clicked()
{
   ui->del_tableWidget->verticalHeader()->setHidden(1);
    cho_find(0,ui);
}

void MainWindow::on_del_in_del_btn_clicked()
{
    QString s[1000];
    int i=0;//数组存学号
    int k=0;//用于遍历checkbox状态
    while (ui->del_tableWidget->item(k,3)!=NULL) {
        if(ui->del_tableWidget->item(k, 0)->checkState() == Qt::Checked)
        {
              s[i]=ui->del_tableWidget->item(k,3)->text();
              i++;
        }
        k++;
    }
    for(int j=0;j<i;j++){
        _delete(find_stu(s[j]));

    }
    ui->del_tableWidget->clearContents();
    cho_find(0,ui);//这里可能会产生一点冲突,存疑
}

void MainWindow::on_del_in_find_btn_clicked()
{
    QString s[1000];
    int i=0;//数组存学号
    int k=0;//用于遍历checkbox状态
    while (ui->find_tableWidget->item(k,3)!=NULL) {
        if(ui->find_tableWidget->item(k, 0)->checkState() == Qt::Checked)
        {
              s[i]=ui->find_tableWidget->item(k,3)->text();
              i++;
        }
        k++;
    }
    for(int j=0;j<i;j++){
        _delete(find_stu(s[j]));
    }
    if (i==0){
    QMessageBox::question(this,"提示","没有勾选有效信息！",QMessageBox::Ok);
    }
    else{
        for(int j=0;j<i;j++){
            _delete(find_stu(s[j]));
        }
        QMessageBox::question(this,"提示","删除成功！",QMessageBox::Ok);
    }
    MainWindow::on_search_btn_clicked();
}

extern bool illegalInput(int pattern,QString str)
{
    QByteArray qBA=str.toLocal8Bit();
    char *ch=qBA.data();
    char *p=ch;
    if(pattern==inputIsEmpty)
    {
        if(p[0]=='\0')
            return 1;
        else
        {
            for(unsigned int i=0;i<sizeof(str)-1;i++)
            {
                if(int(p[i])!=32&&p[i]!='\0')
                    return 0;
            }
        }
        return 1;
    }
    else if(pattern==noAllNumbers)
    {
        for(int i=0;p[i]!='\0';i++)
        {
                if(isNum(p[i]))
                    continue;
                return 1;
        }
        return 0;
    }
}

bool isNum(char c)
{
    for(int i=0;i<10;i++)
    {
        if(c==inputJudge[i])
            return 1;
    }
    return 0;
}

void Export()//退出前导出文件
{
    QFile file("../maillist/nameList.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
         qDebug()<<"失败";
         return;
    }
        Student *p=head;
        QTextStream stream(&file);
        while(p!=NULL)
        {
            stream<<p->name<<" "<<p->sex<<" "<<p->num<<" "<<p->academy<<" "<<p->telenum<<" "
                 <<p->address<<" "<<p->email<<" "<<p->QQ<<" "<<p->VX<<" "<<'\r'<<'\n';
        p=p->next;
        }
        stream<<"END ";
        file.close();
}

void emptyTheList()//退出前清除链表
{
    Student *p=head;
    while(p!=NULL)
    {
       head=head->next;
       delete p;
       p=head;
    }
}

void MainWindow::on_change_btn_clicked()
{
    ui->del_in_find_btn->setDisabled(1);
    if(ui->change_btn->text()=="修改")
    {
    QString searchword;
    searchword=ui->serchEdit->text();
    ui->find_tableWidget->setRowCount(0);
    ui->find_tableWidget->setColumnCount(6);
    ui->find_tableWidget->setHorizontalHeaderLabels(QStringList()<<" "<<"姓名"<<"性别"<<"学号"<<"学院"<<"电话");
    Student *p=head;
        while(p!=NULL)
        {
            if (searchword==p->name||searchword==p->num)
            {
            ui->find_tableWidget->verticalHeader()->setHidden(1);
            int rowIndex=ui->find_tableWidget->rowCount();
            ui->find_tableWidget->setRowCount(rowIndex+1);
            ui->find_tableWidget->setRowHeight(rowIndex , 50);
            QPushButton *btn=new QPushButton(this);
            btn->setStyleSheet("QPushButton{color:white;background-color:rgb(255,181,33);font-family:黑体;border-radius: 15px;}"
                                 "QPushButton:pressed{background-color:rgb(255,121,94)}");
            btn->setFixedSize(80,30);
            connect(btn,SIGNAL(clicked()),this,SLOT(create_editWidget()));
            btn->setText("编辑");
            ui->find_tableWidget->setItem(rowIndex,1,new QTableWidgetItem(p->name));
            QTableWidgetItem *pitem=ui->find_tableWidget->item(rowIndex,1);
            pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
            ui->find_tableWidget->setItem(rowIndex,2,new QTableWidgetItem(p->sex));
            pitem=ui->find_tableWidget->item(rowIndex,2);
            pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
            ui->find_tableWidget->setItem(rowIndex,3,new QTableWidgetItem(p->num));
            pitem=ui->find_tableWidget->item(rowIndex,3);
            pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
            ui->find_tableWidget->setItem(rowIndex,4,new QTableWidgetItem(p->academy));
            pitem=ui->find_tableWidget->item(rowIndex,4);
            pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
            ui->find_tableWidget->setItem(rowIndex,5,new QTableWidgetItem(p->telenum));
            pitem=ui->find_tableWidget->item(rowIndex,5);
            pitem->setFlags(pitem->flags()&(~Qt::ItemIsEditable));
            QHBoxLayout *vLayout = new QHBoxLayout();
            QWidget *Widget_btn = new QWidget;
            vLayout->addWidget(btn);
            vLayout->addSpacing(20);
            Widget_btn->setLayout(vLayout);
            Widget_btn->setStyleSheet("QWidget{ border: 0px }");
            ui->find_tableWidget->setCellWidget(rowIndex,0,Widget_btn);
            }
            p=p->next;
        }
            ui->change_btn->setText("退出修改");
    }
    else
    {
        ui->change_btn->setText("修改");
        ui->del_in_find_btn->setEnabled(1);
        MainWindow::on_search_btn_clicked();
    }
}
void MainWindow::create_editWidget()
{
 // 获取按钮的指针

    QPushButton *pushButton_ = dynamic_cast<QPushButton*>(this->sender());

    if(pushButton_==NULL)
    {
        return;
    }
    // 获取按钮的x坐标和y坐标
    int x = pushButton_->parentWidget()->pos().x();
    int y = pushButton_->parentWidget()->pos().y();
    // 根据按钮的x和y坐标来定位对应的单元格
    QModelIndex index = ui->find_tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    modifyStuNum=ui->find_tableWidget->item(row,3)->text();
    modifyWindow m;
    m.exec();
    ui->change_btn->setText("修改");
    MainWindow::on_change_btn_clicked();
}

void MainWindow::on_addAcademy_clicked()
{
    ui->addAcademy->setDisabled(1);
    ui->lineEdit->setVisible(1);
    ui->pushButton->setVisible(1);
    ui->pushButton_2->setVisible(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setVisible(0);
    ui->pushButton->setVisible(0);
    ui->pushButton_2->setVisible(0);
    ui->addAcademy->setEnabled(1);
}

bool repeatAcademy(QString academy,Ui::MainWindow *ui)
{
    int i=0;
    for(;academyName[i]!='\0';i++)
    {
        if(academy==academyName[i])
            return 1;
    }
    academyName[i]=academy;
    ui->acacombo->addItem(academyName[i]);
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    if(illegalInput(inputIsEmpty,ui->lineEdit->text()))
    {
        QMessageBox::question(this,"提示！","输入不能为空！",QMessageBox::Ok);
        ui->lineEdit->clear();
    }
    else if(repeatAcademy(ui->lineEdit->text(),ui))
    {
        QMessageBox::question(this,"提示！","该学院已存在！",QMessageBox::Ok);
        ui->lineEdit->clear();
    }
    else
    {
        QMessageBox::question(this,"提示！","添加成功！",QMessageBox::Ok);
        ui->lineEdit->clear();
    }
}

void data_lead_in(QString str)
{
    QStringList list = str.split('\n');
    int n=0;
    if(list[0]=="END ")
    {
        return;
    }
    else
    {
    Student* prev = NULL, * current;
    while (1)
    {
        QStringList word = list[n].split(" ");
        n++;
        current = new Student;
        if (head == NULL)
            head = current;
        else
        {
            prev = head;
            while (prev->next != NULL)
                prev = prev->next;
            prev->next = current;
        }
        current->next = NULL;
        current->name=word[0];
        current->sex=word[1];
        current->num=word[2];
        current->academy=word[3];
        for(int i=0,j=0;academyName[i]!='\0';i++)//若导入的学生里有新的学院，则添加新学院的选项
        {
            if(current->academy!=academyName[i])
                j++;
            if(j==i+1&&academyName[i+1]=='\0')
                academyName[++i]=word[3];
        }
        current->telenum=word[4];
        current->address=word[5];
        current->email=word[6];
        current->QQ=word[7];
        current->VX=word[8];
        QStringList next = list[n].split(" ");
        if(next[0]=="END")
            break;
        else
            prev=current;
    }
    }
}
void MainWindow::on_lead_in_btn_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"打开文件","");
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
        {
             QMessageBox::question(this,"提示！","未打开文件！",QMessageBox::Ok);
             return;
        }
        ui->importLineEdit->setVisible(1);
        ui->importLineEdit->setText(path);
        QByteArray array=file.readAll();
        QString data_in=QString(array);
        data_lead_in(data_in);
        QMessageBox::question(this,"提示！","导入成功！",QMessageBox::Ok);
}


void MainWindow::on_lead_out_btn_clicked()
{
    Student*p=head;
    QString path=QFileDialog::getOpenFileName(this,"打开文件","");
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
         QMessageBox::question(this,"提示！","未打开文件！",QMessageBox::Ok);
         return;
    }
    ui->out_putlLineEdit->setVisible(1);
    ui->out_putlLineEdit->setText(path);
    if(head==NULL)
    {
        QTextStream stream(&file);
        stream<<"END ";
    }
    else
    {
        QTextStream stream(&file);
        while(p!=NULL)
        {
        stream<<p->name<<" "<<p->sex<<" "<<p->num<<" "<<p->academy<<" "<<p->telenum<<" "
             <<p->address<<" "<<p->email<<" "<<p->QQ<<" "<<p->VX<<" "<<'\r'<<'\n';
        p=p->next;
        }
        stream<<"END ";
    }
    file.close();
    QMessageBox::question(this,"提示！","导出成功！",QMessageBox::Ok);
}

void MainWindow::on_bandBtn_clicked()
{
    band b;
    b.exec();
}


void MainWindow::on_updateLog_clicked()
{
    QWidget *textwidget=new QWidget;
    QTextEdit *text=new QTextEdit;
    text->setParent(textwidget);
    textwidget->setFixedSize(700,800);
    textwidget->setWindowTitle("更新日志");
    text->setGeometry(50,50,600,700);
    textwidget->show();
    QFile file(":/new/prefix1/updateLog.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
         QMessageBox::question(this,"提示！","打开失败！",QMessageBox::Ok);
         return;
    }
    QByteArray array=file.readAll();
    QString data_in=QString(array);
    text->setText(data_in);
}

void MainWindow::on_help_clicked()
{
    QWidget *textwidget=new QWidget;
    QTextEdit *text=new QTextEdit;
    text->setParent(textwidget);
    textwidget->setFixedSize(700,800);
    textwidget->setWindowTitle("帮助");
    text->setGeometry(50,50,600,700);
    textwidget->show();
    QFile file(":/new/prefix1/help.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
         QMessageBox::question(this,"提示！","打开失败！",QMessageBox::Ok);
         return;
    }
    QByteArray array=file.readAll();
    QString data_in=QString(array);
    text->setText(data_in);
}

void removeRepeat()
{
    if(head==NULL)
    {
        QMessageBox::question(NULL,"提示！","无学生信息！",QMessageBox::Ok);
        return;
    }
    Student *p1=head,*p2;
    while(p1!=NULL)
    {
        p2=p1->next;
        while(p2!=NULL)
        {
            if(p2->num==p1->num)
            {
                Student *p3=p1;
                while(p3->next!=p2)
                    p3=p3->next;
                p3->next=p2->next;
                delete p2;
                p2=p3;//清除p2后p2指向p3（上一位）
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
    QMessageBox::question(NULL,"提示！","已去除重复！",QMessageBox::Ok);
}

void MainWindow::on_removeRepeat_clicked()
{
     int ret=QMessageBox::question(this,"提示！","此行为会删除所有学号重复的学生，是否继续？",QMessageBox::Yes,QMessageBox::Cancel);
     switch (ret)
     {
     case QMessageBox::Yes:
         removeRepeat();
         break;
     case QMessageBox::Cancel:
         break;
     }
}
