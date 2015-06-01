#include "zonecentrale.h"
# include <QDebug>
# include <QDate>
# include "tools.h"
#include <QHBoxLayout>

ZoneCentrale::ZoneCentrale(QWidget *parent) :
    QWidget(parent)
{
    bBox = new QHBoxLayout(this);
    onglets = new QTabWidget(this);
    fenetreGestionProjet = new FenetreGestionProjet(this);
    fenetreEDT = new FenetreEDT;
    onglets->setGeometry(30, 20,1000 ,700);
    onglets->addTab(fenetreGestionProjet,"Gestion de Projet");
    onglets->addTab(fenetreEDT,"Agenda");
    bBox->addWidget(onglets);
    this->setLayout(bBox);
}
