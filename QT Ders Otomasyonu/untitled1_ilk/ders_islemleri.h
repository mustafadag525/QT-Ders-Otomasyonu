#ifndef DERS_ISLEMLERI_H
#define DERS_ISLEMLERI_H

#include <QWidget>
#include <QDialog>
#include "veritabani_islemleri.h"

namespace Ui {
class ders_islemleri;
}

class ders_islemleri : public QDialog
{
    Q_OBJECT

public:
    explicit ders_islemleri(QWidget *parent = nullptr);
    ~ders_islemleri();
    int ders_kodu, secilen;
    QString ders_adi;
    QVector<QString> vector_ad;
    QVector<int> vector_kod;
    QVector<int> vector_ogr_no;
    QVector<int> vector_ders_kod;
    QVector<int> vector_vize;
    QVector<int> vector_final;
    QVector<int> vector_gecme;


    veritabani_islemleri *veritabaniislemleri = nullptr;

    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *e);

private slots:
    void on_pushButton_ekle_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

    void secileni_goster(int row, int column);

    void ders_tablo_goster();

    void ogr_tablo_goster();

private:
    Ui::ders_islemleri *ui;
};

#endif // DERS_ISLEMLERI_H
