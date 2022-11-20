#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QLabel>
#include<QMessageBox>
#include<fstream>
#include<QCheckBox>
#include<QProgressBar>
#include<QObject>
#include<QMetaObject>
#include<QString>
#include <QTextEdit>
#include<QComboBox>
#include<QTableWidget>
#include<QRegExp>
#include <QFileDialog>
#include<QRegExpValidator>
#include <QAbstractItemView>
#include<QLayout>
#include<QLCDNumber>
#include<QTime>
#include<QTimeEdit>
#include<QTimer>
#include<QTextCodec>
#include<QMediaPlayer>
QT_BEGIN_NAMESPACE
struct Student
{
    QString name;
    QString sex;
    QString num;
    QString academy;
    QString telenum;
    QString address;
    QString email;
    QString QQ;
    QString VX;
    Student *next;
};
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addbutton_clicked();

        void on_findbutton_clicked();

        void on_brobutton_clicked();

        void on_stabutton_clicked();

        void on_setbutton_clicked();

        void on_exitbutton_clicked();

        void on_addokbutton_clicked();

        void on_prebtn_clicked();

        void on_nextbtn_clicked();

        void on_bro_pre_clicked();

        void on_bro_next_clicked();

        void on_find_btn_clicked();
        
        void on_search_btn_clicked();

        void on_to_del_btn_clicked();

        void on_to_find_btn_clicked();

        void on_all_choose_btn_clicked();

        void on_cancel_all_btn_clicked();

        void on_del_in_del_btn_clicked();

        void on_del_in_find_btn_clicked();

        void on_change_btn_clicked();

        void create_editWidget();

        void create_seeWidget();

        void on_addAcademy_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_clicked();

        void on_lead_in_btn_clicked();

        void on_lead_out_btn_clicked();

        void on_bandBtn_clicked();

        void on_updateLog_clicked();

        void on_help_clicked();

        void on_removeRepeat_clicked();

        void ctrl_broWidget(Ui::MainWindow *ui,int changePage,int sum,int sP);

private:

};
#endif // MAINWINDOW_H

