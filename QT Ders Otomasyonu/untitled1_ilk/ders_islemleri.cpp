#include "ders_islemleri.h"
#include "ui_ders_islemleri.h"
#include <QMessageBox>
using namespace std;

ders_islemleri::ders_islemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ders_islemleri)
{
    ui->setupUi(this);

    this->ui->label_ad->setText("Ders Adı:");
    this->ui->label_kod->setText("Ders No Kodu:");
    this->ui->pushButton_ekle->setText("Ekle");
    this->ui->pushButton_guncelle->setText("Güncelle");
    this->ui->pushButton_sil->setText("Sil");

    this->veritabaniislemleri = new veritabani_islemleri();

    this->ders_tablo_goster();

    QObject::connect(this->ui->tableWidget_tumders,SIGNAL(cellClicked(int, int)), this, SLOT(secileni_goster(int,int)));

}

ders_islemleri::~ders_islemleri()
{
    delete ui;
}
void ders_islemleri::hideEvent(QHideEvent *event)
{
    this->ui->tableWidget_tumogr->clear();
    this->ui->tableWidget_tumders->clear();
    this->QDialog::hideEvent(event);
}

void ders_islemleri::showEvent(QShowEvent *e)
{
    this->ogr_tablo_goster();
    this->ders_tablo_goster();
    this->QDialog::showEvent(e);
}
void ders_islemleri::on_pushButton_ekle_clicked()
{
    if(this->ui->lineEdit_kod->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_ad->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else{
        QString hata;
        bool ekleme_flag = true;
        this->vector_kod.clear();
        this->vector_ad.clear();
        veritabaniislemleri->ders_getir(hata,this->vector_kod,this->vector_ad);
        ders_kodu = this->ui->lineEdit_kod->text().toInt();
        for (int i = 0; i< vector_kod.size(); i++){
            int kod = vector_kod.at(i);
            if(ders_kodu == kod){
                ekleme_flag = false;
                break;
            }
        }
        if(ekleme_flag){
            QString hata1;
            ders_adi = this->ui->lineEdit_ad->text();
            veritabaniislemleri->ders_ekle(hata1,ders_kodu,ders_adi);
            this->ders_tablo_goster();
        }
        else
            QMessageBox::warning(this, "Hata!", "Aynı kodda kayıtlı ders bulunmaktadır.", "OK");
    }
}

void ders_islemleri::on_pushButton_guncelle_clicked()
{
    if(this->ui->lineEdit_kod->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Ders seçiniz.", "OK");
    }
    else{
        ders_kodu = this->ui->lineEdit_kod->text().toInt();
        ders_adi = this->ui->lineEdit_ad->text();

        QString hata;
        veritabaniislemleri->ders_duzenle(hata,ders_kodu,ders_adi);
        this->ders_tablo_goster();
    }
}

void ders_islemleri::on_pushButton_sil_clicked()
{
    if(this->ui->lineEdit_kod->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Ders seçiniz.", "OK");
    }
    else{
        bool silme_flag = true;
        QString hata;
        vector_ogr_no.clear();
        vector_ders_kod.clear();
        vector_vize.clear();
        vector_final.clear();
        vector_gecme.clear();
        ders_kodu = this->ui->lineEdit_kod->text().toInt();
        veritabaniislemleri->ders_kaydi_getir(hata,this->vector_ogr_no, this->vector_ders_kod, this->vector_vize, this->vector_final, this->vector_gecme);
        for (int i = 0; i< vector_ders_kod.size(); i++){
            int kod = vector_ders_kod.at(i);
            if(ders_kodu == kod){
                silme_flag = false;
                break;
            }
        }
        if(silme_flag){
            QString hata1;
            ders_adi = this->ui->lineEdit_ad->text();
            veritabaniislemleri->ogrenci_sil(hata1, ders_kodu);
            this->ders_tablo_goster();
        }
        else
            QMessageBox::warning(this, "Hata!", "Bu derse kayıtlı öğrenci bulunmaktadır.", "OK");
    }
}

void ders_islemleri::secileni_goster(int row, int column)
{
    secilen = row;
    int text = this->vector_kod.at(row);
    this->ui->lineEdit_kod->setText(to_string(text).c_str());
    this->ui->lineEdit_ad->setText(vector_ad.at(row));
    this->ogr_tablo_goster();
}

void ders_islemleri::ders_tablo_goster()
{
    QString hata;
    this->ui->tableWidget_tumders->clear();
    this->vector_kod.clear();
    this->vector_ad.clear();
    veritabaniislemleri->ders_getir(hata,this->vector_kod,this->vector_ad);
    this->ui->tableWidget_tumders->setColumnCount(3);
    this->ui->tableWidget_tumders->setRowCount(vector_kod.size());

    QStringList tablo_baslik;
    tablo_baslik << "    " << "Ders Kodu" << "Ders Adı";
    this->ui->tableWidget_tumders->setHorizontalHeaderLabels(tablo_baslik);

    for(int i = 0; i < vector_kod.size(); i++){

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString::number(i+1));
        this->ui->tableWidget_tumders->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_kod.at(i)));
        this->ui->tableWidget_tumders->setItem(i,1,item);

        item = new QTableWidgetItem();
        item->setText(vector_ad.at(i));
        this->ui->tableWidget_tumders->setItem(i,2,item);
    }


}

void ders_islemleri::ogr_tablo_goster()
{
    QString hata;
    vector_ogr_no.clear();
    vector_ders_kod.clear();
    vector_vize.clear();
    vector_final.clear();
    vector_gecme.clear();
    this->ui->tableWidget_tumogr->clear();
    veritabaniislemleri->ders_kaydi_getir(hata, this->vector_ogr_no, this->vector_ders_kod, this->vector_vize, this->vector_final, this->vector_gecme);
    QVector<int> count;
    for(int i = 0; i < vector_ders_kod.size(); i++){
        int kod = vector_ders_kod.at(i);
        if(secilen == kod){
            count.append(i);
        }
    }
    this->ui->tableWidget_tumogr->setColumnCount(6);
    this->ui->tableWidget_tumogr->setRowCount(count.size());

    QStringList tablo_baslik;
    tablo_baslik << "    " << "Öğrenci No" << "Ders Kodu" << "Vize Notu" << "Final Notu" << "Geçme Notu";
    this->ui->tableWidget_tumogr->setHorizontalHeaderLabels(tablo_baslik);

    for(int i = 0; i < count.size(); i++){

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString::number(i+1));
        this->ui->tableWidget_tumogr->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_ogr_no.at(count.at(i))));
        this->ui->tableWidget_tumogr->setItem(i,1,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_ders_kod.at(count.at(i))));
        this->ui->tableWidget_tumogr->setItem(i,2,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_vize.at(count.at(i))));
        this->ui->tableWidget_tumogr->setItem(i,3,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_final.at(count.at(i))));
        this->ui->tableWidget_tumogr->setItem(i,4,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_gecme.at(count.at(i))));
        this->ui->tableWidget_tumogr->setItem(i,5,item);
    }

}
