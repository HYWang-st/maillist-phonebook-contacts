#include "band.h"
#include "ui_band.h"

band::band(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::band)
{
    sound= new QSound(":/new/prefix1/mosi.wav");
    sound->play();
    ui->setupUi(this);
    playing=0;
    setWindowTitle("维也纳金色大厅");
    setFixedSize(1048,721);
    QMovie *movie1=new QMovie;
    movie1->setFileName(":/new/prefix1/gifResouce/7865D9DDF9BFD1C1640B51A2A38AAF7D.gif");
    ui->DJgif->setMovie(movie1);
    ui->DJgif->setScaledContents(1);
    movie1->start();//开始播放
}



band::~band()
{
    sound->stop();
    delete sound;
    delete ui;
}


void band::on_drumBtn_clicked()
{


    QMovie *movie2=new QMovie;
    movie2->setFileName(":/new/prefix1/gifResouce/B9761802DEF8BB285DE54742869CB040.gif");
    ui->drumgif->setMovie(movie2);
    ui->drumgif->setScaledContents(1);
    if(ui->drumBtn->text()=="鼓-奏")
    {
        ui->drumBtn->setText("鼓-停");
        ui->drumBtn->setShortcut(QKeySequence(QLatin1String("F")));
        ui->drumgif->setVisible(1);
        movie2->start();//开始播放
        playing++;
        if(playing==7)
        {
            ui->togeBtn->setText("大合奏-停");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
    else
    {
        ui->drumBtn->setText("鼓-奏");
        ui->drumBtn->setShortcut(QKeySequence(QLatin1String("F")));
        movie2->stop();
        ui->drumgif->setVisible(0);
        playing--;
        if(!playing)
        {
            ui->togeBtn->setText("大合奏-起");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
}

void band::on_erhuBtn_clicked()
{
    QMovie *movie3=new QMovie;
    movie3->setFileName(":/new/prefix1/gifResouce/27A81379FB6D59957A65670CC3258204.gif");
    ui->erhuGif->setMovie(movie3);
    ui->erhuGif->setScaledContents(1);
    if(ui->erhuBtn->text()=="二胡-奏")
    {
        ui->erhuBtn->setText("二胡-停");
        ui->erhuBtn->setShortcut(QKeySequence(QLatin1String("G")));
        ui->erhuGif->setVisible(1);
        movie3->start();//开始播放
        playing++;
        if(playing==7)
        {
            ui->togeBtn->setText("大合奏-停");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
    else
    {
        ui->erhuBtn->setText("二胡-奏");
        ui->erhuBtn->setShortcut(QKeySequence(QLatin1String("G")));
        movie3->stop();
        ui->erhuGif->setVisible(0);
        playing--;
        if(!playing)
        {
            ui->togeBtn->setText("大合奏-起");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
}

void band::on_pianoBtn_clicked()
{
    QMovie *movie4=new QMovie;
    movie4->setFileName(":/new/prefix1/gifResouce/5C181136592248301C93932464D049D7.gif");
    ui->pianoGif->setMovie(movie4);
    ui->pianoGif->setScaledContents(1);
    if(ui->pianoBtn->text()=="钢琴-奏")
    {
        ui->pianoBtn->setText("钢琴-停");
        ui->pianoBtn->setShortcut(QKeySequence(QLatin1String("H")));
        ui->pianoGif->setVisible(1);
        movie4->start();//开始播放
        playing++;
        if(playing==7)
        {
            ui->togeBtn->setText("大合奏-停");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
    else
    {
        ui->pianoBtn->setText("钢琴-奏");
        ui->pianoBtn->setShortcut(QKeySequence(QLatin1String("H")));
        movie4->stop();
        ui->pianoGif->setVisible(0);
        playing--;
        if(!playing)
        {
            ui->togeBtn->setText("大合奏-起");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
}

void band::on_accordionBtn_clicked()
{
    QMovie *movie5=new QMovie;
    movie5->setFileName(":/new/prefix1/gifResouce/82A95570D53F5B3AC092E11088CA7B85.gif");
    ui->accordionGif->setMovie(movie5);
    ui->accordionGif->setScaledContents(1);
    if(ui->accordionBtn->text()=="手风琴-奏")
    {
        ui->accordionBtn->setText("手风琴-停");
        ui->accordionBtn->setShortcut(QKeySequence(QLatin1String("J")));
        ui->accordionGif->setVisible(1);
        movie5->start();//开始播放
        playing++;
        if(playing==7)
        {
            ui->togeBtn->setText("大合奏-停");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
    else
    {
        ui->accordionBtn->setText("手风琴-奏");
        ui->accordionBtn->setShortcut(QKeySequence(QLatin1String("J")));
        movie5->stop();
        ui->accordionGif->setVisible(0);
        playing--;
        if(!playing)
        {
            ui->togeBtn->setText("大合奏-起");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
}

void band::on_celloBtn_clicked()
{
    QMovie *movie6=new QMovie;
    movie6->setFileName(":/new/prefix1/gifResouce/2F266766DF74A1EF9203728D77538135.gif");
    ui->celloGif->setMovie(movie6);
    ui->celloGif->setScaledContents(1);
    if(ui->celloBtn->text()=="大提琴-奏")
    {
        ui->celloBtn->setText("大提琴-停");
        ui->celloBtn->setShortcut(QKeySequence(QLatin1String("D")));
        ui->celloGif->setVisible(1);
        movie6->start();//开始播放
        playing++;
        if(playing==7)
        {
            ui->togeBtn->setText("大合奏-停");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
    else
    {
        ui->celloBtn->setText("大提琴-奏");
        ui->celloBtn->setShortcut(QKeySequence(QLatin1String("D")));
        movie6->stop();
        ui->celloGif->setVisible(0);
        playing--;
        if(!playing)
        {
            ui->togeBtn->setText("大合奏-起");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
}

void band::on_violinBtn_clicked()
{
    QMovie *movie7=new QMovie;
    movie7->setFileName(":/new/prefix1/gifResouce/B2EFC10B5BC163C0DF3C735BEAA3164A.gif");
    ui->violinGif->setMovie(movie7);
    ui->violinGif->setScaledContents(1);
    if(ui->violinBtn->text()=="小提琴-奏")
    {
        ui->violinBtn->setText("小提琴-停");
        ui->violinBtn->setShortcut(QKeySequence(QLatin1String("K")));
        ui->violinGif->setVisible(1);
        movie7->start();//开始播放
        playing++;
        if(playing==7)
        {
            ui->togeBtn->setText("大合奏-停");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
    else
    {
        ui->violinBtn->setText("小提琴-奏");
        ui->violinBtn->setShortcut(QKeySequence(QLatin1String("K")));
        movie7->stop();
        ui->violinGif->setVisible(0);
        playing--;
        if(!playing)
        {
            ui->togeBtn->setText("大合奏-起");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
}

void band::on_guitarBtn_clicked()
{
    QMovie *movie8=new QMovie;
    movie8->setFileName(":/new/prefix1/gifResouce/DBB0CF6A051A4F3FF93AC92292607615.gif");
    ui->guitarGif->setMovie(movie8);
    ui->guitarGif->setScaledContents(1);
    if(ui->guitarBtn->text()=="电吉他-奏")
    {
        ui->guitarBtn->setText("电吉他-停");
        ui->guitarBtn->setShortcut(QKeySequence(QLatin1String("L")));
        ui->guitarGif->setVisible(1);
        movie8->start();//开始播放
        playing++;
        if(playing==7)
        {
            ui->togeBtn->setText("大合奏-停");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
    else
    {
        ui->guitarBtn->setText("电吉他-奏");
        ui->guitarBtn->setShortcut(QKeySequence(QLatin1String("L")));
        movie8->stop();
        ui->guitarGif->setVisible(0);
        playing--;
        if(!playing)
        {
            ui->togeBtn->setText("大合奏-起");
            ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        }
    }
}

void band::on_togeBtn_clicked()
{
    if(ui->togeBtn->text()=="大合奏-起")
    {
        ui->togeBtn->setText("大合奏-停");
        ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        if(ui->drumBtn->text()=="鼓-奏")
            band::on_drumBtn_clicked();
        if(ui->erhuBtn->text()=="二胡-奏")
            band::on_erhuBtn_clicked();
        if(ui->pianoBtn->text()=="钢琴-奏")
            band::on_pianoBtn_clicked();
        if(ui->accordionBtn->text()=="手风琴-奏")
            band::on_accordionBtn_clicked();
        if(ui->celloBtn->text()=="大提琴-奏")
            band::on_celloBtn_clicked();
        if(ui->violinBtn->text()=="小提琴-奏")
            band::on_violinBtn_clicked();
        if(ui->guitarBtn->text()=="电吉他-奏")
            band::on_guitarBtn_clicked();
        playing=7;
    }
    else
    {
        ui->togeBtn->setText("大合奏-起");
        ui->togeBtn->setShortcut(QKeySequence(QLatin1String("B")));
        if(ui->drumBtn->text()=="鼓-停")
            band::on_drumBtn_clicked();
        if(ui->erhuBtn->text()=="二胡-停")
            band::on_erhuBtn_clicked();
        if(ui->pianoBtn->text()=="钢琴-停")
            band::on_pianoBtn_clicked();
        if(ui->accordionBtn->text()=="手风琴-停")
            band::on_accordionBtn_clicked();
        if(ui->celloBtn->text()=="大提琴-停")
            band::on_celloBtn_clicked();
        if(ui->violinBtn->text()=="小提琴-停")
            band::on_violinBtn_clicked();
        if(ui->guitarBtn->text()=="电吉他-停")
            band::on_guitarBtn_clicked();
        playing=0;
    }
}
