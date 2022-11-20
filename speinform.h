#ifndef SPEINFORM_H
#define SPEINFORM_H

#include <QDialog>

namespace Ui {
class speInform;
}

class speInform : public QDialog
{
    Q_OBJECT

public:
    explicit speInform(QWidget *parent = nullptr);
    ~speInform();

private slots:
    void on_pushButton_clicked();

private:
    Ui::speInform *ui;
};

#endif // SPEINFORM_H
