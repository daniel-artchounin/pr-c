#include "zonecentrale.h"

ZoneCentrale::ZoneCentrale(QWidget *parent) :
    QWidget(parent)
{
    onglets = new QTabWidget(this);
    fenetreGestionProjet = new FenetreGestionProjet;
    fenetreEDT = new FenetreEDT;
    onglets->addTab(fenetreGestionProjet,"Gestion de Projet");
    onglets->addTab(fenetreEDT,"Agenda");
    this->show();
}
