#ifndef PRODUIT_H
#define PRODUIT_H
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include <QDebug>
#include <QSqlError>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>
#include <QVBoxLayout>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QByteArray>
#include <QSqlTableModel>
using namespace std;

class produit
{
private:
    QString ref_prod;
    float prix;
    QString taille;
    QString couleur;
    int quantite;
    QString categorie;
    QString qualite;
public:
        produit();
        ~produit();
        produit(QString ref,float pr,QString t,QString coul,int quant,QString cat,QString qual);


        QString Getref_prod() { return ref_prod; }
        void Setref_prod(QString val) { ref_prod = val; }
        float Getprix() { return prix; }
        void Setprix(float val) { prix = val; }
        QString Gettaille() { return taille; }
        void Settaille(QString val) { taille = val; }
        QString Getcouleur() { return couleur; }
        void Setcouleur(QString val) { couleur = val; }
        int Getquantite() { return quantite; }
        void Setquantite(int val) { quantite = val; }
        QString Getcategorie() { return categorie; }
        void Setcategorie(QString val) { categorie = val; }
        QString Getqualite() { return qualite; }
        void Setqualite(QString val) { qualite = val; }

        bool ajouter();
        bool supprimer(QString);
        bool rechercherproduit(QString ref);
        QSqlQueryModel* rechercherproduit1(QString a);
        QSqlQueryModel* afficherproduit();
        bool modifierproduit(QString);
        QSqlQueryModel* trierproduit_quantite();
        QSqlQueryModel* trierproduit_prix();
        QSqlQueryModel* trierproduit_qualite();
        void CREATION_PDF();
        bool ajouterImage(QString ref,const QString &imagePath);
};


class ImageDelegate : public QStyledItemDelegate
{

public:
    explicit ImageDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};



#endif // PRODUIT_H
