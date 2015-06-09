#include "programmerevenement.h"
#include "fenetreprincipale.h"

ProgrammerEvenement::ProgrammerEvenement(QWidget *parent) :
    FenetreAnnulerValider(parent) {
    progEvt=0;
    initialiserFormulaire();
}

ProgrammerEvenement::ProgrammerEvenement(ProgrammationEvenement* prog, QWidget *parent) : FenetreAnnulerValider(parent), progEvt(prog) {
    initialiserFormulaire();
    nom->setText(toQString(progEvt->getNom()));
    lieu->setText(toQString(progEvt->getEvenement()->getLieu()));
    motif->setText(toQString(progEvt->getEvenement()->getMotif()));
    dateDebut->setDate(QDate::fromString(toQString(progEvt->getDateProgrammation().toString()), "dd/MM/yyyy"));
    horaireDebut->setTime(QTime(progEvt->getHoraireProgrammation().getHeure(),progEvt->getHoraireProgrammation().getMinute()));
    dureeHeure->setValue(progEvt->getDuree().getHeure());
    dureeMinute->setValue(progEvt->getDuree().getMinute());
}

void ProgrammerEvenement::initialiserFormulaire() {
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
    if(progEvt==0) {
        fp.show();
    }else {
        this->close();
    }
    fp.updateEDT();
}
