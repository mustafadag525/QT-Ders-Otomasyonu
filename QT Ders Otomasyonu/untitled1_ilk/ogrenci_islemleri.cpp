#include "ogrenci_islemleri.h"
#include "ui_ogrenci_islemleri.h"
#include <QMessageBox>
using namespace std;

ogrenci_islemleri::ogrenci_islemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenci_islemleri)
{
    ui->setupUi(this);
    this->ui->label_no->setText("Öğrenci No:");
    this->ui->label_ad->setText("Öğrenci Ad:");
    this->ui->label_soyad->setText("Öğrenci Soyadı:");
    this->ui->pushButton_yeni->setText("Yeni Kayıt");
    this->ui->pushButton_guncelle->setText("Güncelle");
    this->ui->pushButton_sil->setText("Sil");
    this->ui->label_tumogr->setText("Tüm Öğrenciler");

    this->veritabaniislemleri = new veritabani_islemleri();
    this->ogr_tablo_goster();

    QObject::connect(this->ui->tableWidget_tumogr,SIGNAL(cellClicked(int, int)), this, SLOT(secileni_goster(int,int)));

}

ogrenci_islemleri::~ogrenci_islemleri()
{
    delete ui;
}

void ogrenci_islemleri::hideEvent(QHideEvent *event)
{
    this->ui->tableWidget_tumogr->clear();
    this->QDialog::hideEvent(event);
}

void ogrenci_islemleri::showEvent(QShowEvent *e)
{
    this->ogr_tablo_goster();
    this->QDialog::showEvent(e);
}
void ogrenci_islemleri::on_pushButton_yeni_clicked()
{
    if(this->ui->lineEdit_no->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_ad->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_soyad->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else{
        QString hata;
        ogr_no = this->ui->lineEdit_no->text().toInt();
        ogr_ad = this->ui->lineEdit_ad->text();
        ogr_soyad = this->ui->lineEdit_soyad->text();
        veritabaniislemleri->ogrenci_ekle(hata, ogr_no, ogr_ad, ogr_soyad);
        this->ogr_tablo_goster();
    }
}

void ogrenci_islemleri::on_pushButton_guncelle_clicked()
{

    if(this->ui->lineEdit_no->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Öğrenci seçiniz.", "OK");
    }
    else if(this->ui->lineEdit_no->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_ad->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_soyad->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else{
        QString hata;
        ogr_no = this->ui->lineEdit_no->text().toInt();
        ogr_ad = this->ui->lineEdit_ad->text();
        ogr_soyad = this->ui->lineEdit_soyad->text();
        veritabaniislemleri->ogrenci_duzenle(hata, ogr_no, ogr_ad, ogr_soyad);
        this->ogr_tablo_goster();
    }
}

void ogrenci_islemleri::on_pushButton_sil_clicked()
{
    if(this->ui->lineEdit_no->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Öğrenci seçiniz.", "OK");
    }
    else{
        bool silme_flag = true;
        QString hata;
        vector_ogr_no.clear();
        vector_ders_kod.clear();
        vector_vize.clear();
        vector_final.clear();
        vector_gecme.clear();
        ogr_no = this->ui->lineEdit_no->text().toInt();
        veritabaniislemleri->ders_kaydi_getir(hata,this->vector_ogr_no, this->vector_ders_kod, this->vector_vize, this->vector_final, this->vector_gecme);
        for (int i = 0; i< vector_ogr_no.size(); i++){
            int no = vector_ogr_no.at(i);
            if(ogr_no == no){
                silme_flag = false;
                break;
            }
        }
        if(silme_flag){
            QString hata1;
            veritabaniislemleri->ogrenci_sil(hata1, ogr_no);
            this->ogr_tablo_goster();
        }
        else
            QMessageBox::warning(this, "Hata!", "Öğrencinin üstüne kayıtlı ders bulunmaktadır.", "OK");
    }
}

void ogrenci_islemleri::secileni_goster(int row, int column)
{
    int text = this->vector_ogrno.at(row);
    this->ui->lineEdit_no->setText(to_string(text).c_str());
    this->ui->lineEdit_ad->setText(vector_ograd.at(row));
    this->ui->lineEdit_soyad->setText(vector_ogrsoyad.at(row));
}

void ogrenci_islemleri::ogr_tablo_goster()
{
    QString hata;
    this->ui->tableWidget_tumogr->clear();
    this->vector_ogrno.clear();
    this->vector_ograd.clear();
    this->vector_ogrsoyad.clear();
    this->ui->tableWidget_tumogr->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->tableWidget_tumogr->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget_tumogr->setSortingEnabled(false);
    veritabaniislemleri->ogrenci_getir(hata,this->vector_ogrno,this->vector_ograd, this->vector_ogrsoyad);
    this->ui->tableWidget_tumogr->setColumnCount(4);
    this->ui->tableWidget_tumogr->setRowCount(vector_ogrno.size());

    QStringList tablo_baslik;
    tablo_baslik << " " << "Öğrenci No" << "Öğrenci Adı" << "Öğrenci Soyadı";
    this->ui->tableWidget_tumogr->setHorizontalHeaderLabels(tablo_baslik);

    for(int i = 0; i < vector_ogrno.size(); i++){

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString::number(i+1));
        this->ui->tableWidget_tumogr->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_ogrno.at(i)));
        this->ui->tableWidget_tumogr->setItem(i,1,item);

        item = new QTableWidgetItem();
        item->setText(vector_ograd.at(i));
        this->ui->tableWidget_tumogr->setItem(i,2,item);

        item = new QTableWidgetItem();
        item->setText(vector_ogrsoyad.at(i));
        this->ui->tableWidget_tumogr->setItem(i,3,item);
    }
    this->ui->tableWidget_tumogr->resizeColumnsToContents();

}
