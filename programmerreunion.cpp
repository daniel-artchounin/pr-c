#include "programmerreunion.h"
#include "programmationmanager.h"
#include "programmationmanagerexception.h"
#include "tools.h"
#include <QMessageBox>
#include "modifierprogrammationevenement.h"

ProgrammerReunion::ProgrammerReunion(QWidget *parent) : ProgrammerEvenement(parent) {}

ProgrammerReunion::ProgrammerReunion(ProgrammationEvenement* prog, QWidget *parent) : ProgrammerEvenement(prog,parent){}

void ProgrammerReunion::retourFenetrePrincipaleValider() {
    if(progEvt==0) {
        try {
            ProgrammationEvenement& evt = ProgrammationManager::getInstance().addProgrammationEvenement(Date(toString(dateDebut->date().toString("dd/MM/yyyy"))), Horaire(horaireDebut->time().hour(),horaireDebut->time().minute()), Duree(dureeHeure->value(), dureeMinute->value()));
            evt.programmerReunion(toString(nom->text()),toString(motif->text()),toString(motif->text()));
            QMessageBox::information(this, "Information", "Votre réunion a bien été programmé.");
        }catch(ProgrammationManagerException e) {
            QMessageBox::information(this, "Information", "Votre réunion n'a pas pu être programmé. Vérifier que vous n'ayez pas déjà un évènement prévu à ce moment là.");
        }
    }else {
        ProgrammationManager::getInstance().updateProgrammationEvenement(progEvt,Date(toString(dateDebut->date().toString("dd/MM/yyyy"))), Horaire(horaireDebut->time().hour(),horaireDebut->time().minute()),Duree(dureeHeure->value(),dureeMinute->value()));
        progEvt->getEvenement()->updateEvenement(toString(nom->text()),toString(lieu->text()),toString(motif->text()));
        ModifierProgrammationEvenement *mod=dynamic_cast<ModifierProgrammationEvenement*>(parentWidget());
        mod->updateListe();
    }
    retourFenetrePrincipaleAnnuler();
}
