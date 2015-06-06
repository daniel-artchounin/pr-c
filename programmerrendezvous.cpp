#include "programmerrendezvous.h"
#include "programmationmanager.h"
#include "programmationmanagerexception.h"
#include "tools.h"
#include <QMessageBox>

ProgrammerRendezVous::ProgrammerRendezVous(QWidget *parent) : ProgrammerEvenement(parent){}

void ProgrammerRendezVous::retourFenetrePrincipaleValider() {
    try {
        ProgrammationEvenement evt = ProgrammationManager::getInstance().addProgrammationEvenement(Date(toString(dateDebut->date().toString("dd/MM/yyyy"))), Horaire(horaireDebut->time().hour(),horaireDebut->time().minute()), Duree(dureeHeure->value(), dureeMinute->value()));
        evt.programmerRendezVous(toString(nom->text()),toString(motif->text()),toString(motif->text()));
        QMessageBox::information(this, "Information", "Votre rendez-vous a bien été programmé.");
    }catch(ProgrammationManagerException e) {
        QMessageBox::information(this, "Information", "Votre réunion n'a pas pu être programmé. Vérifier que vous n'ayez pas déjà un évènement prévu à ce moment là.");
    }
    retourFenetrePrincipaleAnnuler();
}

