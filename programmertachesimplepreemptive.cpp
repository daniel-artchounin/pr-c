#include "programmertachesimplepreemptive.h"
#include "fenetreprincipale.h"
# include <QCloseEvent>

ProgrammerTacheSimplePreemptive::ProgrammerTacheSimplePreemptive(QWidget *parent) :
    QWidget(parent)
{
    dateProgrammation = new QDateEdit;
    horaireProgrammation = new QTimeEdit();
    pourcentage = new QSpinBox;
    formlayout = new QFormLayout;
    formlayout->addRow("Date de début de programmation",dateProgrammation);
    formlayout->addRow("Horaire de début de programmation",horaireProgrammation);
    formlayout->addRow("Pourcentage de programmation",pourcentage);
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

void ProgrammerTacheSimplePreemptive::retourFenetrePrincipale(){
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
}

void ProgrammerTacheSimplePreemptive::closeEvent(QCloseEvent *event)
{
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
    event->accept();
}
