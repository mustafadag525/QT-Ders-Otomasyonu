#ifndef VERITABANI_ISLEMLERI_H
#define VERITABANI_ISLEMLERI_H
#include <QString>
#include <QVector>
#include <QtWidgets>

class veritabani_islemleri
{
public:
    veritabani_islemleri();

    bool ogrenci_getir(QString &hata,  QVector<int> &no,  QVector<QString> &ad,  QVector<QString> &soyad);
    bool ogrenci_ekle(QString &hata, int &no, QString &ad, QString &soyad);
    bool ogrenci_duzenle(QString &hata, int &no, QString &ad, QString &soyad);
    bool ogrenci_sil(QString &hata, int &no);

    bool ders_getir(QString &hata, QVector<int> &kod, QVector<QString> &ad);
    bool ders_ekle(QString &hata, int &kod, QString &ad);
    bool ders_duzenle(QString &hata, int &kod, QString &ad);
    bool ders_sil(QString &hata, int &kod);

    bool ders_kaydi_getir(QString &hata, QVector<int> &no, QVector<int> &kod, QVector<int> &vize, QVector<int> &final, QVector<int> &gecme);
    bool ders_kaydi_ekle(QString &hata, int &no, int &kod, int &vize, int &final, int &gecme);

};

#endif // VERITABANI_ISLEMLERI_H
