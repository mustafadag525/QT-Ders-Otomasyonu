#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
QSqlDatabase veritabanii;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    veritabanii = QSqlDatabase::addDatabase("QSQLITE");
    veritabanii.setDatabaseName("D:/deneme15/veritabanii.db");

    if (!veritabanii.open())
    {
        qDebug() << veritabanii.lastError().text();

        this->ui->label->setText("Veritabanı bağlantısı başarısız.");
    }
    else
         this->ui->label->setText("Veri tabanına bağlandınız.");


    QObject::connect(this->ui->ogrenci_islemleri,SIGNAL(clicked(bool)), this, SLOT(ogrenciIslemleri()));
    QObject::connect(this->ui->ders_islemleri,SIGNAL(clicked(bool)), this, SLOT(dersIslemleri()));
    QObject::connect(this->ui->not_islemleri,SIGNAL(clicked(bool)), this, SLOT(notIslemleri()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ogrenciIslemleri()
{
    if(this->ogrenciislemleri == nullptr){
        this->ogrenciislemleri = new ogrenci_islemleri(this);
    }
    this->ogrenciislemleri->setWindowTitle("Öğrenci İşlemleri");
//    this->ogrenciislemleri->setFixedSize(1100,800);
    this->ogrenciislemleri->show();
}

void MainWindow::dersIslemleri()
{
    if(this->dersislemleri == nullptr){
        this->dersislemleri = new ders_islemleri(this);
    }
    this->dersislemleri->setWindowTitle("Ders İşlemleri");
//    this->dersislemleri->setFixedSize(1100,800);
    this->dersislemleri->show();
}

void MainWindow::notIslemleri()
{
    if(this->notislemleri == nullptr){
        this->notislemleri = new not_islemleri(this);
    }
    this->notislemleri->setWindowTitle("Not İşlemleri");
//    this->notislemleri->setFixedSize(1100,800);
    this->notislemleri->show();
}

