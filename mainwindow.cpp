#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialize serial port
    serial.setPortName("COM6");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    // Open serial port
    if (!serial.open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Unable to open serial port!");
    }

    // Connect serial data available signal
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readFromArduino);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
QString ref= ui->le_ref->text();
float prix=ui->le_prix->text().toFloat();
QString taille=ui->le_taille->text();
QString couleur=ui->le_couleur->text();
int quantite=ui->le_quant->text().toInt();
QString categorie;
QString qualite;
if (ui->h->isChecked()) {
    categorie="h";
    ui->f->setChecked(false);
}
else if (ui->f->isChecked()) {
    categorie="f";
    ui->h->setChecked(false);
}

if (ui->high->isChecked()) {
    qualite="high";
    ui->mediocre->setChecked(false);
    ui->low->setChecked(false);
}
else if (ui->mediocre->isChecked()) {
    qualite="mediocre";
    ui->high->setChecked(false);
    ui->low->setChecked(false);
}
else if (ui->low->isChecked()) {
    qualite="low";
    ui->high->setChecked(false);
    ui->mediocre->setChecked(false);
}
produit p(ref,prix,taille,couleur,quantite,categorie,qualite);
if((prix>0) && (quantite>0))
{
bool test=p.ajouter();
if (test==true)
{
    //p.statproduit(series);
    ui->tab_produit->setModel(p.afficherproduit());

}
else
{
    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                QObject::tr(" erreur.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

ui->le_ref->clear();
ui->le_prix->clear();
ui->le_quant->clear();
ui->le_taille->clear();
ui->le_couleur->clear();
ui->high->setChecked(false);
ui->mediocre->setChecked(false);
ui->low->setChecked(false);
ui->h->setChecked(false);
ui->f->setChecked(false);
}
else
    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                QObject::tr(" Verifier Votre informations.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_pb_supprimer_clicked()
{
    produit p;
    p.Setref_prod(ui->le_ref->text());
    bool test=p.supprimer(p.Getref_prod());
    if (test)
    {
        ui->tab_produit->setModel(p.afficherproduit());
        QMessageBox::information(nullptr, QObject::tr("suppression avec succes"),
                    QObject::tr(" successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr(" erreur.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->le_ref->clear();
    ui->le_prix->clear();
    ui->le_quant->clear();
    ui->le_taille->clear();
    ui->le_couleur->clear();
    ui->high->setChecked(false);
    ui->mediocre->setChecked(false);
    ui->low->setChecked(false);
    ui->h->setChecked(false);
    ui->f->setChecked(false);
}

void MainWindow::on_pb_afficher_clicked()
{
   produit p;
   ui->tab_produit->setModel(p.afficherproduit());
   ImageDelegate *imageDelegate = new ImageDelegate(this);
   ui->tab_produit->setItemDelegateForColumn(7, imageDelegate);

   ui->tab_produit->resizeColumnsToContents();
   ui->tab_produit->resizeRowsToContents();
}

void MainWindow::on_pb_modifier_clicked()
{
    QString ref=ui->le_ref->text();
    float prix=ui->le_prix->text().toFloat();
    QString couleur=ui->le_couleur->text();
    int quantite=ui->le_quant->text().toInt();
    QString taille=ui->le_taille->text();
    QString categorie;
    QString qualite;
    if (ui->h->isChecked()) {
        categorie = "h";
    } else if (ui->f->isChecked()) {
        categorie = "f";
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Please select a category.\nClick Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    if (ui->high->isChecked()) {
        qualite = "high";
    } else if (ui->mediocre->isChecked()) {
        qualite = "mediocre";
    } else if (ui->low->isChecked()) {
        qualite = "low";
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Please select a quality.\nClick Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    produit p(ref,prix,taille,couleur,quantite,categorie,qualite);
    if((prix>0) && (quantite>0))
    {
        bool test=p.rechercherproduit(ref);
        if (test)
        {
            bool test1=p.modifierproduit(ref,prix,taille,couleur,categorie,quantite,qualite);
            if(test1){
            ui->tab_produit->setModel(p.afficherproduit());
            QMessageBox::information(nullptr, QObject::tr("modification avec succes"),
                        QObject::tr(" successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }else{QMessageBox::critical(nullptr, QObject::tr("erreur"),
                                    QObject::tr(" erreur.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("erreur"),
                        QObject::tr(" reference inexistante.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else

            QMessageBox::critical(nullptr, QObject::tr("erreur"),
                        QObject::tr(" Verifier Votre informations.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    ui->le_ref->clear();
    ui->le_prix->clear();
    ui->le_quant->clear();
    ui->le_taille->clear();
    ui->le_couleur->clear();
    ui->high->setChecked(false);
    ui->mediocre->setChecked(false);
    ui->low->setChecked(false);
    ui->h->setChecked(false);
    ui->f->setChecked(false);
}

void MainWindow::on_pb_trier_clicked()
{
    produit p;
    ui->tab_produit->setModel(p.trierproduit_quantite());
}

void MainWindow::on_pb_trier_2_clicked()
{
    produit p;
    ui->tab_produit->setModel(p.trierproduit_prix());
}

void MainWindow::on_pb_recherche_clicked() {
    QString searchText = ui->le_recherche->text();
    if (searchText.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez saisir un mot-clé pour la recherche.");
        return;
    }

    produit p;
    QSqlQueryModel *model = p.rechercherproduit1(searchText);

    if (model->rowCount() > 0) {
        ui->tab_produit->setModel(model);
    } else {
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé.");
        qDebug() << "Aucun résultat pour:" << searchText;
    }
}



void MainWindow::on_pb_trier_3_clicked()
{
    produit p;
    ui->tab_produit->setModel(p.trierproduit_qualite());
}



void MainWindow::on_pb_generer_pdf_clicked()
{
    produit p;
    p.CREATION_PDF();
}

void MainWindow::on_pb_ajouterimage_clicked()
{
    QString ref = ui->le_ref->text(); // Get the product reference from the input field
    if (ref.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a product reference!");
        return;
    }

    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg)");
    if (imagePath.isEmpty()) {
        return; // User canceled the operation
    }

    produit p;
    bool success = p.ajouterImage(ref, imagePath);
    if (success) {
        QMessageBox::information(this, "Success", "Image added successfully!");
        ui->tab_produit->setModel(p.afficherproduit());
    } else {
        QMessageBox::critical(this, "Error", "Failed to add image to the database.");
    }
}
void MainWindow::readFromArduino() {
    QByteArray data = serial.readAll(); // Read all available data from Arduino
    QString receivedData = QString::fromUtf8(data).trimmed();
    qDebug() << "Received from Arduino:" << receivedData;

    if (receivedData.contains("Product Detected")) {
        updateProductStatus("expose"); // Update the database
        writeToArduino("1"); // Send '1' to Arduino to display "1"
    } else if (receivedData.contains("Product Missing")) {
        updateProductStatus("non expose"); // Update the database
        writeToArduino("0"); // Send '0' to Arduino to display "0"
    } else {
        qDebug() << "Unrecognized data from Arduino:" << receivedData;
    }
}


void MainWindow::updateProductStatus(QString status) {
    QString ref_prod = ui->le_ref->text();

    if (ref_prod.isEmpty()) {
        qDebug() << "No product reference provided. Skipping database update.";
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE GS_produit SET etagiére = :status WHERE ref_produit = :ref_prod");
    query.bindValue(":status", status);
    query.bindValue(":ref_prod", ref_prod);

    if (query.exec()) {
        qDebug() << "Product status updated successfully to:" << status;
    } else {
        qDebug() << "Failed to update product status:" << query.lastError().text();
    }
}


void MainWindow::on_pb_updateStatus_clicked()
{
    manualUpdate = true; // Indicate this is a manual update
    readFromArduino();  // Trigger Arduino read
    manualUpdate = false; // Reset after the operation
}
void MainWindow::writeToArduino(const QString &message) {
    if (serial.isOpen() && serial.isWritable()) {
        serial.write(message.toUtf8());
        qDebug() << "Sent to Arduino:" << message;
    } else {
        QMessageBox::warning(this, "Error", "Serial port is not open or writable.");
    }
}
