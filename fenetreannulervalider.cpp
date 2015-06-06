#include "fenetreannulervalider.h"
# include <QCloseEvent>
# include "fenetreprincipale.h"

FenetreAnnulerValider::FenetreAnnulerValider(QWidget *parent) :
    QWidget(parent)
{
    annuler = new QPushButton("Annuler");
    valider = new QPushButton("Sauver");
    hBoxAnnulerValider = new QHBoxLayout;
    hBoxAnnulerValider->addWidget(annuler);
    hBoxAnnulerValider->addWidget(valider);
    vBox = new QVBoxLayout(this);
    connect(annuler,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleAnnuler()));
    connect(valider,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleValider()));
}

void FenetreAnnulerValider::retourFenetrePrincipaleAnnuler(){
    this->close();
}

void FenetreAnnulerValider::closeEvent(QCloseEvent *event){
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.show();
    event->accept();
}
