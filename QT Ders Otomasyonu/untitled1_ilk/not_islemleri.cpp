#include "not_islemleri.h"
#include "ui_not_islemleri.h"
#include <QMessageBox>
using namespace std;
not_islemleri::not_islemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::not_islemleri)
{
    ui->setupUi(this);
    this->ui->label_no->setText("Öğrenci No:");
    this->ui->label_kod->setText("DersKodu:");
    this->ui->label_vize->setText("Vize Notu:");
    this->ui->label_final->setText("Final Notu");
    this->ui->label_tumogr->setText("");
    this->ui->pushButton_ekle->setText("Ders Kaydı Ekle");

    this->veritabaniislemleri = new veritabani_islemleri();

    this->ogr_tablo_goster();
    this->ders_tablo_goster();
    this->tum_ogr_ders_tablo_goster();

    QObject::connect(this->ui->tableWidget_tumogr,SIGNAL(cellClicked(int, int)), this, SLOT(ogr_secileni_goster(int,int)));
    QObject::connect(this->ui->tableWidget_tumders,SIGNAL(cellClicked(int, int)), this, SLOT(ders_secileni_goster(int,int)));

}

not_islemleri::~not_islemleri()
{
    delete ui;
}
void not_islemleri::hideEvent(QHideEvent *event)
{
    this->ui->tableWidget_tumogr->clear();
    this->ui->tableWidget_tumders->clear();
    this->ui->tableWidget_tumogrders->clear();
    this->QDialog::hideEvent(event);
}

void not_islemleri::showEvent(QShowEvent *e)
{
    this->ogr_tablo_goster();
    this->ders_tablo_goster();
    this->QDialog::showEvent(e);
}
void not_islemleri::on_pushButton_ekle_clicked()
{
    if(this->ui->lineEdit_no->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_kod->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_vize->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else if(this->ui->lineEdit_final->text() == QString("")){
        QMessageBox::warning(this, "Hata!", "Gerekli alanları doldurunuz.", "OK");
    }
    else{

        bool ekleme_flag = true;
        QString hata;
        vector_ogr_no.clear();
        vector_ders_kod.clear();
        vector_vize.clear();
        vector_final.clear();
        vector_gecme.clear();
        ogr_no = this->ui->lineEdit_no->text().toInt();
        ders_kod = this->ui->lineEdit_kod->text().toInt();
        veritabaniislemleri->ders_kaydi_getir(hata,this->vector_ogr_no, this->vector_ders_kod, this->vector_vize, this->vector_final, this->vector_gecme);
        for (int i = 0; i< vector_ogr_no.size(); i++){
            int no = vector_ogr_no.at(i);
            int kod = vector_ders_kod.at(i);
            if(ogr_no == no && ders_kod == kod){
                ekleme_flag = false;
                break;
            }
        }
        if(ekleme_flag){
            QString hata1;
            vize_not = this->ui->lineEdit_vize->text().toInt();
            final_not = this->ui->lineEdit_final->text().toInt();
            gecme_notu =  gecme_notu = (40*vize_not + 60*final_not)/100;
            veritabaniislemleri->ders_kaydi_ekle(hata1, ogr_no,ders_kod,vize_not,final_not, gecme_notu);
            this->tum_ogr_ders_tablo_goster();
        }
        else
            QMessageBox::warning(this, "Hata!", "Öğrencinin üstüne kayıtlı ders bulunmaktadır.", "OK");
    }
}

void not_islemleri::ogr_secileni_goster(int row, int column)
{
    int text = this->vector_ogrno.at(row);
    this->ui->lineEdit_no->setText(to_string(text).c_str());
}

void not_islemleri::ders_secileni_goster(int row, int column)
{
    int text = this->vector_kod.at(row);
    this->ui->lineEdit_kod->setText(to_string(text).c_str());
}

void not_islemleri::ogr_tablo_goster()
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

void not_islemleri::ders_tablo_goster()
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

void not_islemleri::tum_ogr_ders_tablo_goster()
{
    QString hata;
    this->ui->tableWidget_tumogrders->clear();
    vector_ogr_no.clear();
    vector_ders_kod.clear();
    vector_vize.clear();
    vector_final.clear();
    vector_gecme.clear();
    veritabaniislemleri->ders_kaydi_getir(hata, this->vector_ogr_no, this->vector_ders_kod, this->vector_vize, this->vector_final, this->vector_gecme);
    this->ui->tableWidget_tumogrders->setColumnCount(6);
    this->ui->tableWidget_tumogrders->setRowCount(vector_ogr_no.size());

    QStringList tablo_baslik;
    tablo_baslik << "  " << "Öğrenci No" << "Ders Kodu" << "Vize Notu" << "Final Notu" << "Geçme Notu";
    this->ui->tableWidget_tumogrders->setHorizontalHeaderLabels(tablo_baslik);

    for(int i = 0; i < vector_ogr_no.size(); i++){

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString::number(i+1));
        this->ui->tableWidget_tumogrders->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_ogr_no.at(i)));
        this->ui->tableWidget_tumogrders->setItem(i,1,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_ders_kod.at(i)));
        this->ui->tableWidget_tumogrders->setItem(i,2,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_vize.at(i)));
        this->ui->tableWidget_tumogrders->setItem(i,3,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_final.at(i)));
        this->ui->tableWidget_tumogrders->setItem(i,4,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(vector_gecme.at(i)));
        this->ui->tableWidget_tumogrders->setItem(i,5,item);
    }
}
