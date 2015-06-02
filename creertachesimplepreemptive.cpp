#include "creertachesimplepreemptive.h"
# include "fenetreprincipale.h"

CreerTacheSimplePreemptive::CreerTacheSimplePreemptive(QWidget *parent) :
    QWidget(parent)
{
    titre = new QLineEdit;
    dateDebut = new QDateEdit();
    horaireDebut = new QTimeEdit();
    dateFin = new QDateEdit();
    horaireFin = new QTimeEdit();
    formlayout = new QFormLayout;
    heures = new QSpinBox;
    labelH = new QLabel("heure(s)");
    minutes =  new QSpinBox;
    labelM = new QLabel("minute(s)");
    formlayout->addRow("Titre du projet : ", titre);
    formlayout->addRow("Date de disponibilité du projet : ", dateDebut);
    formlayout->addRow("Horaire de disponibilité du projet : ", horaireDebut);
    formlayout->addRow("Date d'échéance du projet : ", dateFin);
    formlayout->addRow("Horaire d'échéance du projet : ", horaireFin);
    hBox1 = new QHBoxLayout;
    hBox1->addWidget(heures);
    hBox1->addWidget(labelH);
    hBox1->addWidget(minutes);
    hBox1->addWidget(labelM);
    formlayout->addRow("Durée du projet : ", hBox1);
    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauver");
    hBox2 = new QHBoxLayout;
    hBox2->addWidget(annuler);
    hBox2->addWidget(sauver);
    vBox = new QVBoxLayout(this);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBox2);
    connect(annuler,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipale()));
    connect(sauver,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipale()));
}

void CreerTacheSimplePreemptive::retourFenetrePrincipale(){
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
}

void CreerTacheSimplePreemptive::closeEvent(QCloseEvent *event)
{
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
    event->accept();

}
