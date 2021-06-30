#ifndef NOT_ISLEMLERI_H
#define NOT_ISLEMLERI_H

#include <QWidget>
#include <QDialog>
#include "veritabani_islemleri.h"

namespace Ui {
class not_islemleri;
}

class not_islemleri : public QDialog
{
    Q_OBJECT

public:
    explicit not_islemleri(QWidget *parent = nullptr);
    ~not_islemleri();
    int ogr_no, ders_kod, vize_not, final_not, gecme_notu;
    QVector<int> vector_ogr_no;
    QVector<int> vector_ders_kod;
    QVector<int> vector_vize;
    QVector<int> vector_final;
    QVector<int> vector_gecme;

    QVector<QString> vector_ad;
    QVector<int> vector_kod;

    QVector<int> vector_ogrno;
    QVector<QString> vector_ograd;
    QVector<QString> vector_ogrsoyad;

    veritabani_islemleri *veritabaniislemleri = nullptr;

    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *e);

private slots:
    void on_pushButton_ekle_clicked();

    void ogr_secileni_goster(int row, int column);

    void ders_secileni_goster(int row, int column);

    void ogr_tablo_goster();

    void ders_tablo_goster();

    void tum_ogr_ders_tablo_goster();

private:
    Ui::not_islemleri *ui;
};

#endif // NOT_ISLEMLERI_H
