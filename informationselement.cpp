#include "informationselement.h"
# include "fenetreprincipale.h"
# include <QCloseEvent>

InformationsElement::InformationsElement(const Element &element, QWidget *parent) :
    QWidget(parent)
{
    ok = new QPushButton("OK");
    hBoxOK  = new QHBoxLayout;
    hBoxOK->addWidget(ok);
    vBox = new QVBoxLayout(this);
    titre = new QLabel(QString::fromStdString(element.getTitre()));
    dateDebut = new QLabel(QString::fromStdString(element.getDateDebut().toString()));
    horaireDebut = new QLabel(QString::fromStdString(element.getHoraireDebut().toString()));
    dateEcheance = new QLabel(QString::fromStdString(element.getDateFin().toString()));
    heureEcheance = new QLabel(QString::fromStdString(element.getHoraireFin().toString()));
    duree = new QLabel(QString::fromStdString(element.getDuree().toString()));
    formlayout = new QFormLayout;
    formlayout->addRow("Titre :", titre);
    formlayout->addRow("Date de disponibilité : ", dateDebut);
    formlayout->addRow("Horaire de disponibilité : ", horaireDebut);
    formlayout->addRow("Date d'échéance : ", dateEcheance);
    formlayout->addRow("Horaire d'échéance : ", heureEcheance);
    formlayout->addRow("Duree: ", duree);
    connect(ok,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipale()));
}

void InformationsElement::retourFenetrePrincipale(){
    this->close();
}

void InformationsElement::closeEvent(QCloseEvent *event){
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.show();
    event->accept();
}
