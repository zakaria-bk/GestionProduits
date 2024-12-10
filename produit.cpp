#include "produit.h"

produit::produit()
{

}
produit::~produit() {

}

produit::produit(QString ref,float pr,QString t,QString coul,int quant,QString cat,QString qual){
    ref_prod=ref;
    prix=pr;
    taille=t;
    couleur=coul;
    quantite=quant;
    categorie=cat;
    qualite=qual;
}

bool produit::ajouter(){
    QString pr=QString::number(prix);
    QString q=QString::number(quantite);
    QSqlQuery query;
    query.prepare("insert into GS_PRODUIT(ref_produit,prix,taille,couleur,quantite,categorie,qualite) VALUES(:ref_produit,:prix,:taille,:couleur,:quantite,:categorie,:qualite)");
    query.bindValue(":ref_produit",ref_prod);
    query.bindValue(":prix",pr);
    query.bindValue(":taille",taille);
    query.bindValue(":couleur",couleur);
    query.bindValue(":quantite",q);
    query.bindValue(":categorie",categorie);
    query.bindValue(":qualite",qualite);
    return query.exec();
}

bool produit::supprimer(QString ref){
    bool test=rechercherproduit(ref);
    QSqlQuery query;
    query.prepare("delete from GS_PRODUIT where ref_produit=:ref");
    query.bindValue(":ref",ref);
    query.exec();
    return test;
}

bool produit::rechercherproduit(QString ref) {
    QSqlQuery q("select * from GS_PRODUIT where ref_produit=:ref");
    q.bindValue(":ref",ref);
    while(q.next())
    {
        return true;
    }
    return false;
}


QSqlQueryModel* produit::rechercherproduit1(QString a) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryText = "SELECT * FROM GS_PRODUIT WHERE "
                        "(ref_produit LIKE '%" + a + "%' OR prix LIKE '%" + a + "%' OR "
                        "taille LIKE '%" + a + "%' OR couleur LIKE '%" + a + "%' OR "
                        "quantite LIKE '%" + a + "%' OR qualite LIKE '%" + a + "%' OR "
                        "categorie LIKE '%" + a + "%')";

    qDebug() << "Requête SQL:" << queryText;
    model->setQuery(queryText);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL:" << model->lastError().text();
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Qualité"));

    return model;
}


QSqlQueryModel* produit::afficherproduit()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from GS_PRODUIT");
     model->setHeaderData(0, Qt::Horizontal,QObject::tr("Reference"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("Prix"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("Taille"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("Couleur"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("Quantité"));
     model->setHeaderData(5, Qt::Horizontal,QObject::tr("Catégorie"));
     model->setHeaderData(6, Qt::Horizontal,QObject::tr("Qualité"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("Image"));
    return model;
}

bool produit::modifierproduit(QString ref)
{
    QSqlQuery query;
    query.prepare("update GS_PRODUIT set prix=:prix,taille=:taille,couleur=:couleur,quantite=:quantite,categorie=:categorie,qualite=:qualite where ref_produit=:ref");
    query.bindValue(":ref",ref_prod);
    query.bindValue(":prix",prix);
    query.bindValue(":taille",taille);
    query.bindValue(":couleur",couleur);
    query.bindValue(":categorie",categorie);
    query.bindValue(":quantite",quantite);
    query.bindValue(":qualite",qualite);
    query.exec();
    return rechercherproduit(ref);
}

QSqlQueryModel* produit::trierproduit_quantite()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from GS_PRODUIT  order by quantite ASC");
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Taille"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Couleur"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Quantité"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Catégorie"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("Qualité"));
return  model ;
}
QSqlQueryModel* produit::trierproduit_prix()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from GS_PRODUIT  order by prix ASC");
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Taille"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Couleur"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Quantité"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Catégorie"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("Qualité"));
return  model ;
}
QSqlQueryModel* produit::trierproduit_qualite() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT * FROM GS_PRODUIT "
        "ORDER BY CASE "
        "WHEN qualite = 'high' THEN 1 "
        "WHEN qualite = 'mediocre' THEN 2 "
        "WHEN qualite = 'low' THEN 3 "
        "ELSE 4 END ASC"
    );

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Qualité"));

    return model;
}

void produit::CREATION_PDF()
{
    // Define the file name and path directly
    QString fileName = "C:/Users/medzi/Downloads/produits.pdf";

    // Set up the printer for PDF generation
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;

    // Prepare SQL query to get data from the produit table
    q.prepare("SELECT ref_produit, prix, taille, couleur, quantite, categorie, qualite FROM GS_PRODUIT");
    q.exec();

    // HTML content for the PDF (table header)
    QString pdf = "<br><h1 style='color:blue'>LISTE DES PRODUITS</h1>\n<br>"
                  "<table border='1' style='border-collapse: collapse;'>"
                  "<tr><th>Référence</th><th>Prix</th><th>Taille</th><th>Couleur</th>"
                  "<th>Quantité</th><th>Catégorie</th><th>Qualité</th></tr>";

    // Loop through query results and add rows to the table
    while (q.next()) {
        pdf += "<tr><td>" + q.value(0).toString() + "</td>"  // ref_produit
             + "<td>" + QString::number(q.value(1).toFloat(), 'f', 2) + "</td>"  // prix (float with 2 decimal places)
             + "<td>" + q.value(2).toString() + "</td>"  // taille
             + "<td>" + q.value(3).toString() + "</td>"  // couleur
             + "<td>" + QString::number(q.value(4).toInt()) + "</td>"  // quantite (integer)
             + "<td>" + q.value(5).toString() + "</td>"  // categorie
             + "<td>" + q.value(6).toString() + "</td></tr>";  // qualite
    }

    // Close the table tag
    pdf += "</table>";

    // Set the HTML content to the QTextDocument
    doc.setHtml(pdf);

    // Set the page size and print the document to the PDF
    doc.setPageSize(printer.pageRect().size());  // This ensures the page layout is correct
    doc.print(&printer);  // Print the document to the specified file

    // Optional: Inform the user that the PDF has been saved
    QMessageBox::information(nullptr, "Export PDF", "The PDF file has been successfully saved to: " + fileName);
}


ImageDelegate::ImageDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 7) { // Assuming the image column is at index 7
        QByteArray imageData = index.data(Qt::EditRole).toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        painter->drawPixmap(option.rect, pixmap.scaled(option.rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 7) { // Image column
        return QSize(100, 100); // Default size for images
    }
    return QStyledItemDelegate::sizeHint(option, index);
}
bool produit::ajouterImage(QString ref, const QString &imagePath)
{
    QSqlQuery query;
    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open image file.";
        return false;
    }
    QByteArray imageData = file.readAll();
    query.prepare("UPDATE GS_PRODUIT SET image = :image WHERE ref_produit = :ref");
    query.bindValue(":image", imageData);
    query.bindValue(":ref", ref);
    return query.exec();
}




