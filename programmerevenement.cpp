#include "programmerevenement.h"
#include "fenetreprincipale.h"

ProgrammerEvenement::ProgrammerEvenement(QWidget *parent) :
    FenetreAnnulerValider(parent) {
    nom = new QLineEdit;
    motif = new QLineEdit;
    lieu = new QLineEdit;

    dateDebut = new QDateEdit(QDate::currentDate());
    horaireDebut = new QTimeEdit();

    dureeHeure = new QSpinBox();
    dureeHeure->setMinimum(0);
    dureeMinute = new QSpinBox();
    dureeMinute->setMaximum(59);
    dureeMinute->setMinimum(0);
    duree = new QHBoxLayout();
    duree->addWidget(dureeHeure);
    duree->addWidget(new QLabel("H"));
    duree->addWidget(dureeMinute);

    formlayout = new QFormLayout;
    formlayout->addRow("Nom : ", nom);
    formlayout->addRow("Motif : ", motif);
    formlayout->addRow("Lieu : ", lieu);
    formlayout->addRow("Date : ", dateDebut);
    formlayout->addRow("Horaire : ", horaireDebut);
    formlayout->addRow("Duree : ", duree);

    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxAnnulerValider);
}

void ProgrammerEvenement::closeEvent(QCloseEvent *event) {
    event->accept();
    FenetrePrincipale& fp = FenetrePrincipale::getInstance();
    fp.show();
    fp.updateEDT();
}
