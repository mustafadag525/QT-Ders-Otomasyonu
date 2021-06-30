#include "veritabani_islemleri.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
extern QSqlDatabase veritabanii;

veritabani_islemleri::veritabani_islemleri()
{

}

bool veritabani_islemleri::ogrenci_getir(QString &hata,  QVector<int> &no,  QVector<QString> &ad, QVector<QString> &soyad)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);

    if(!sorgu.exec(QString("SELECT * FROM ogrenci;"))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    while(sorgu.next()){
        int _no;
        QString _ad,_soyad;
        _no = sorgu.value(0).toInt();
        _ad = sorgu.value(1).toString().trimmed();
        _soyad = sorgu.value(2).toString().trimmed();
        no.append(_no);
        ad.append(_ad);
        soyad.append(_soyad);

    }

    sorgu.clear();
    return true;
}

bool veritabani_islemleri::ogrenci_ekle(QString &hata, int &no, QString &ad, QString &soyad)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);
    QSqlQuery databaseQuery(veritabanii);

    if(!sorgu.exec(QString("INSERT INTO ogrenci (ogr_no, ogr_ad,ogr_soyad)VALUES(%1,'%2','%3');").arg(QString::number(no),ad,soyad))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    return true;
}

bool veritabani_islemleri::ogrenci_duzenle(QString &hata, int &no, QString &ad, QString &soyad)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);
    if(!sorgu.exec(QString("UPDATE ogrenci set ogr_ad = '%2' , ogr_soyad = '%3' WHERE ogr_no = %1 ;").arg(QString::number(no),ad,soyad))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }

    return true;
}

bool veritabani_islemleri::ogrenci_sil(QString &hata, int &no)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);


    if(!sorgu.exec(QString("DELETE FROM ogrenci WHERE ogr_no = %1;").arg(QString::number(no)))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    return true;
}

bool veritabani_islemleri::ders_getir(QString &hata, QVector<int> &kod, QVector<QString> &ad)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);

    if(!sorgu.exec(QString("SELECT * from dersler;"))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    while(sorgu.next()){
        int _kod;
        QString _ad;
        _kod = sorgu.value(0).toInt();
        _ad = sorgu.value(1).toString().trimmed();

        kod.append(_kod);
        ad.append(_ad);
    }
    sorgu.clear();
    return true;
}

bool veritabani_islemleri::ders_ekle(QString &hata, int &kod, QString &ad)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);
    if(!sorgu.exec(QString("INSERT INTO dersler (ders_kodu, ders_adi) VALUES (%1,'%2');").arg(QString::number(kod),ad))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    return true;
}

bool veritabani_islemleri::ders_duzenle(QString &hata, int &kod, QString &ad)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);
    if(!sorgu.exec(QString("UPDATE dersler set ders_adi = '%2' WHERE ogr_no = %1;").arg(QString::number(kod),ad))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    return true;
}

bool veritabani_islemleri::ders_sil(QString &hata, int &kod)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);
    if(!sorgu.exec(QString("DELETE FROM dersler WHERE ders_kodu = %1;").arg(QString::number(kod)))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    return true;
}

bool veritabani_islemleri::ders_kaydi_getir(QString &hata, QVector<int> &no, QVector<int> &kod, QVector<int> &vize, QVector<int> &final, QVector<int> &gecme)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);

    if(!sorgu.exec(QString("SELECT * from notlar;"))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    while(sorgu.next()){
        int _no, _kod, _vize, _final, _gecme;

        _no = sorgu.value(0).toInt();
        _kod = sorgu.value(1).toInt();
        _vize = sorgu.value(2).toInt();
        _final = sorgu.value(3).toInt();
        _gecme = sorgu.value(4).toInt();

        no.append(_no);
        kod.append(_kod);
        vize.append(_vize);
        final.append(_final);
        gecme.append(_gecme);

    }

    sorgu.clear();
    return true;
}

bool veritabani_islemleri::ders_kaydi_ekle(QString &hata, int &no, int &kod, int &vize, int &final, int &gecme)
{
    if(!veritabanii.isOpen())
        return false;
    QSqlQuery sorgu(veritabanii);
    if(!sorgu.exec(QString("INSERT INTO notlar (ogr_no, ders_kodu, vize_not, final_not, gecme_notu) VALUES (%1,%2,%3,%4,%5);").arg(QString::number(no),QString::number(kod),QString::number(vize),QString::number(final),QString::number(gecme)))){
        hata = sorgu.lastError().nativeErrorCode();
        return false;
    }
    return true;
}
