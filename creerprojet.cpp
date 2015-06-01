#include "creerprojet.h"
# include <QPushButton>
# include <fenetreprincipale.h>
# include <QCloseEvent>

CreerProjet::CreerProjet(QWidget *parent) :
    QWidget(parent)
{
    titre = new QLineEdit;
    dateDebut = new QDateEdit();
    horaireDebut = new QTimeEdit();
    dateFin = new QDateEdit();
    horaireFin = new QTimeEdit();
    formlayout = new QFormLayout;
    formlayout->addRow("Titre du projet : ", titre);
    formlayout->addRow("Date de disponibilité du projet : ", dateDebut);
    formlayout->addRow("Horaire de disponibilité du projet : ", horaireDebut);
    formlayout->addRow("Date d'échéance du projet : ", dateFin);
    formlayout->addRow("Horaire d'échéance du projet : ", horaireFin);
    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauver");
    hBox = new QHBoxLayout;
    hBox->addWidget(annuler);
    hBox->addWidget(sauver);
    vBox = new QVBoxLayout(this);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBox);
    connect(annuler,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipale()));
    connect(sauver,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipale()));
}

void CreerProjet::retourFenetrePrincipale(){
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
}

void CreerProjet::closeEvent(QCloseEvent *event)
{
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
    event->accept();

}
