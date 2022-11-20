#ifndef BAND_H
#define BAND_H
#include<QMovie>
#include <QDialog>
#include <QMediaPlayer>
#include<QKeySequence>
#include<QLatin1String>
#include <QMediaPlayer>
#include<QSound>
namespace Ui {
class band;
}

class band : public QDialog
{
    Q_OBJECT

public:
    explicit band(QWidget *parent = nullptr);
    ~band();

private slots:

    void on_drumBtn_clicked();

    void on_erhuBtn_clicked();

    void on_pianoBtn_clicked();

    void on_accordionBtn_clicked();

    void on_celloBtn_clicked();

    void on_violinBtn_clicked();

    void on_guitarBtn_clicked();

    void on_togeBtn_clicked();

private:
    Ui::band *ui;
    int playing;
    QSound *sound;
};

#endif // BAND_H
