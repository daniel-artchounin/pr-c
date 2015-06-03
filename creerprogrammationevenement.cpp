#include "creerprogrammationevenement.h"
#include "fenetreprincipale.h"

CreerProgrammationEvenement::CreerProgrammationEvenement(QWidget *parent) : QWidget(parent) {
    nom = new QLineEdit;
    dateDebut = new QDateEdit();
    horaireDebut = new QTimeEdit();
    duree = new QSpinBox();
    formlayout = new QFormLayout;
    formlayout->addRow("Nom : ", nom);
    formlayout->addRow("Date : ", dateDebut);
    formlayout->addRow("Horaire : ", horaireDebut);
    formlayout->addRow("Duree : ", duree);
    annuler = new QPushButton("Annuler");
    valider = new QPushButton("Valider");
    hBox = new QHBoxLayout;
    hBox->addWidget(annuler);
    hBox->addWidget(valider);
    vBox = new QVBoxLayout(this);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBox);
    connect(annuler,SIGNAL(clicked()),this,SLOT(quitter()));
    connect(valider,SIGNAL(clicked()),this,SLOT(programmer()));
}

void CreerProgrammationEvenement::quitter() {
    FenetrePrincipale& fp = FenetrePrincipale::getInstance();
    fp.show();
    this->close();
}

void CreerProgrammationEvenement::programmer() {
    //à modifier
}

void CreerProgrammationEvenement::closeEvent(QCloseEvent *event) {
    event->accept();
    quitter();
}
