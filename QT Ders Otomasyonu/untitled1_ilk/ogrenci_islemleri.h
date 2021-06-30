#ifndef OGRENCI_ISLEMLERI_H
#define OGRENCI_ISLEMLERI_H

#include <QWidget>
#include <QDialog>
#include "veritabani_islemleri.h"
namespace Ui {
class ogrenci_islemleri;
}

class ogrenci_islemleri : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenci_islemleri(QWidget *parent = nullptr);
    ~ogrenci_islemleri();

    int ogr_no;
    QString ogr_ad, ogr_soyad;
    QVector<int> vector_ogrno;
    QVector<QString> vector_ograd;
    QVector<QString> vector_ogrsoyad;

    QVector<int> vector_ogr_no;
    QVector<int> vector_ders_kod;
    QVector<int> vector_vize;
    QVector<int> vector_final;
    QVector<int> vector_gecme;

    veritabani_islemleri *veritabaniislemleri = nullptr;

    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *e);

private slots:
    void on_pushButton_yeni_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

    void secileni_goster(int row, int column);

    void ogr_tablo_goster();

private:
    Ui::ogrenci_islemleri *ui;
};

#endif // OGRENCI_ISLEMLERI_H
