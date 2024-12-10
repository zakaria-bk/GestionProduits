#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QObject>
#include <QMessageBox>
#include<produit.h>
#include <QtSerialPort/QSerialPort>
#include <QtSql/QSqlDatabase>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();


    void on_pb_supprimer_clicked();

    void on_pb_afficher_clicked();

    void on_pb_modifier_clicked();

    void on_pb_trier_clicked();

    void on_pb_trier_2_clicked();

    void on_pb_recherche_clicked();

    void on_pb_trier_3_clicked();

    void on_pb_generer_pdf_clicked();


    void on_pb_ajouterimage_clicked();

    void readFromArduino();
    void updateProductStatus(QString status);

    void on_pb_updateStatus_clicked();
   void writeToArduino(const QString &message);
private:
    Ui::MainWindow *ui;
    QSerialPort serial;     // Serial port for Arduino communication
    QSqlDatabase db;
     bool manualUpdate = false;
};

#endif // MAINWINDOW_H
