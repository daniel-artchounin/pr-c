#include "creerprojettache.h"

CreerProjetTache::CreerProjetTache(QWidget *parent):
FenetreAnnulerValider(parent)
{
    titre = new QLineEdit;
    dateDebut = new QDateEdit();
    horaireDebut = new QTimeEdit();
    dateFin = new QDateEdit();
    horaireFin = new QTimeEdit();
    formlayout = new QFormLayout;
    formlayout->addRow("Titre de la tâche simple préemptive :", titre);
    formlayout->addRow("Date de disponibilité : ", dateDebut);
    formlayout->addRow("Horaire de disponibilité : ", horaireDebut);
    formlayout->addRow("Date d'échéance : ", dateFin);
    formlayout->addRow("Horaire d'échéance : ", horaireFin);
}
