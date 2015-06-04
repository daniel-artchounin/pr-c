#include "programmertachesimplenonpreemptive.h"
#include "fenetreprincipale.h"

ProgrammerTacheSimpleNonPreemptive::ProgrammerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent) :
    QWidget(parent), nomProjet(projet)
{
    chemin = chaine;
    tailleChemin = taille;
    dateProgrammation = new QDateEdit;
    horaireProgrammation = new QTimeEdit();
    formlayout = new QFormLayout;
    formlayout->addRow("Date de début de programmation",dateProgrammation);
    formlayout->addRow("Horaire de début de programmation",horaireProgrammation);
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

void ProgrammerTacheSimpleNonPreemptive::retourFenetrePrincipale(){
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
}

void ProgrammerTacheSimpleNonPreemptive::closeEvent(QCloseEvent *event)
{
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
    event->accept();
}
