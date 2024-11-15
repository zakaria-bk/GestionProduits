#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QObject>
#include <QMessageBox>
#include<produit.h>
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
