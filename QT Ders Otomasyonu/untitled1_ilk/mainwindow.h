#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ogrenci_islemleri.h>
#include <not_islemleri.h>
#include <ders_islemleri.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ders_islemleri *dersislemleri = nullptr;
    not_islemleri *notislemleri = nullptr;
    ogrenci_islemleri *ogrenciislemleri = nullptr;

public slots:
    void ogrenciIslemleri();
    void dersIslemleri();
    void notIslemleri();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
