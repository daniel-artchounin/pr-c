#include "zonecentrale.h"
#include <QDate>
#include "tools.h"
#include <QHBoxLayout>

ZoneCentrale::ZoneCentrale(QWidget *parent) :
    QWidget(parent)
{
    hBox = new QHBoxLayout(this);
    fenetreGestionProjet = new FenetreGestionProjet(this);
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    fenetreGestionProjet->setSizePolicy(spLeft);
    fenetreEDT = new FenetreEDT;
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(3);
    fenetreEDT->setSizePolicy(spRight);
    // onglets->setGeometry(30, 20,1000 ,700);
    // onglets->addTab(fenetreGestionProjet,"Gestion de Projet");
    //onglets->addTab(fenetreEDT,"Agenda");
    hBox->addWidget(fenetreGestionProjet);
    hBox->addWidget(fenetreEDT);
    this->setLayout(hBox);
}
