#include "programmerrendezvous.h"
#include "programmationmanager.h"
#include "programmationmanagerexception.h"
#include "tools.h"
#include <QMessageBox>
#include "modifierprogrammationevenement.h"

ProgrammerRendezVous::ProgrammerRendezVous(QWidget *parent) : ProgrammerEvenement(parent){}

ProgrammerRendezVous::ProgrammerRendezVous(ProgrammationEvenement* prog, QWidget *parent) : ProgrammerEvenement(prog,parent){}


void ProgrammerRendezVous::retourFenetrePrincipaleValider() {
    if(progEvt==0) {
        try {
            ProgrammationEvenement& evt = ProgrammationManager::getInstance().addProgrammationEvenement(Date(toString(dateDebut->date().toString("dd/MM/yyyy"))), Horaire(horaireDebut->time().hour(),horaireDebut->time().minute()), Duree(dureeHeure->value(), dureeMinute->value()));
            evt.programmerRendezVous(toString(nom->text()),toString(motif->text()),toString(motif->text()));
            QMessageBox::information(this, "Information", "Votre rendez-vous a bien été programmé.");
        }catch(ProgrammationManagerException e) {
            QMessageBox::information(this, "Information", "Votre réunion n'a pas pu être programmé. Vérifier que vous n'ayez pas déjà un évènement prévu à ce moment là.");
        }
    }else {
        try {
            ProgrammationManager::getInstance().updateProgrammationEvenement(progEvt,Date(toString(dateDebut->date().toString("dd/MM/yyyy"))), Horaire(horaireDebut->time().hour(),horaireDebut->time().minute()),Duree(dureeHeure->value(),dureeMinute->value()));
            progEvt->getEvenement()->updateEvenement(toString(nom->text()),toString(lieu->text()),toString(motif->text()));
            ModifierProgrammationEvenement *mod=dynamic_cast<ModifierProgrammationEvenement*>(parentWidget());
            mod->updateListe();
            QMessageBox::information(this, "Information", "Votre rendez-vous a bien été modifiée.");
        }catch(ProgrammationManagerException e) {
            QMessageBox::information(this, "Information", "Votre rendez-vous n'a pas pu être modifiée. Vérifier que vous n'ayez pas déjà un évènement prévu à ce moment là.");
        }
    }
    retourFenetrePrincipaleAnnuler();
}

