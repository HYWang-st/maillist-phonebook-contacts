#ifndef MODIFYWINDOW_H
#define MODIFYWINDOW_H

#include <QDialog>

namespace Ui {
class modifyWindow;
}

class modifyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit modifyWindow(QWidget *parent = nullptr);
    ~modifyWindow();

private slots:
    void on_OKbtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::modifyWindow *ui;
};

#endif // MODIFYWINDOW_H
