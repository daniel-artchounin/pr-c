#include "programmerreunion.h"
#include "programmationmanager.h"
#include "programmationmanagerexception.h"
#include "tools.h"
#include <QMessageBox>

ProgrammerReunion::ProgrammerReunion(QWidget *parent) : ProgrammerEvenement(parent) {}

void ProgrammerReunion::retourFenetrePrincipaleValider() {
    try {
        ProgrammationEvenement evt = ProgrammationManager::getInstance().addProgrammationEvenement(Date(toString(dateDebut->date().toString("dd/MM/yyyy"))), Horaire(horaireDebut->time().hour(),horaireDebut->time().minute()), Duree(dureeHeure->value(), dureeMinute->value()));
        evt.programmerReunion(toString(nom->text()),toString(motif->text()),toString(motif->text()));
        QMessageBox::information(this, "Information", "Votre réunion a bien été programmé.");
    }catch(ProgrammationManagerException e) {
        QMessageBox::information(this, "Information", "Votre réunion n'a pas pu être programmé. Vérifier que vous n'ayez pas déjà un évènement prévu à ce moment là.");
    }
    retourFenetrePrincipaleAnnuler();
}
