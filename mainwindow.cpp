#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    if (!test)
    {
        //p.statproduit(series);
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
    bool test=p.modifierproduit(ref);
    if (!test)
    { //p.statproduit(series);
        ui->tab_produit->setModel(p.afficherproduit());
        QMessageBox::information(nullptr, QObject::tr("modification avec succes"),
                    QObject::tr(" successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr(" erreur.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }}
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

    // Vérifiez si le modèle contient des données
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
