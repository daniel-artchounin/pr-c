#include "programmertachesimplenonpreemptive.h"
#include "fenetreprincipale.h"
#include "programmationmanagerexception.h"

ProgrammerTacheSimpleNonPreemptive::ProgrammerTacheSimpleNonPreemptive(Projet* projet, std::string * chaine, unsigned int* taille, std::string& titreT, QWidget *parent):
    ProgrammerTacheSimple(projet, chaine, taille, titreT, parent)
{

}

ProgrammerTacheSimpleNonPreemptive::ProgrammerTacheSimpleNonPreemptive(ProgrammationTacheSimpleNonPreemptive* prog, QWidget *parent):ProgrammerTacheSimple(prog, parent){
    dateDebut->setText(QString::fromStdString(prog->getTacheSimple().getDateDebut().toString()));
    horaireDebut->setText(QString::fromStdString(prog->getTacheSimple().getHoraireDebut().toString()));
    dateEcheance->setText(QString::fromStdString(prog->getTacheSimple().getDateFin().toString()));
    heureEcheance->setText(QString::fromStdString(prog->getTacheSimple().getHoraireFin().toString()));
    duree->setText(QString::fromStdString(prog->getTacheSimple().getDuree().toString()));
}

void ProgrammerTacheSimpleNonPreemptive::retourFenetrePrincipaleValider(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    if(progTache==0) {
        try{
            TacheSimpleNonPreemptive& myTacheSimpleNonPreemptive = nomProjet->accederTacheSimpleNonPreemptive(
                        chemin,
                        *tailleChemin,
                        titreTache
                        );
            programmationManager.addProgrammationTacheSimpleNonPreemptive(
                        Date(dateProgrammation->date().day(), dateProgrammation->date().month(), dateProgrammation->date().year()),
                        Horaire(horaireProgrammation->time().hour(), horaireProgrammation->time().minute()),
                        myTacheSimpleNonPreemptive
                        );
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.getZoneCentrale()->getFenetreEDT()->loadWeek();
        }
        catch(std::logic_error& e){
            QMessageBox::warning(this, "Création de tâche tâche simple non préemptive", e.what());
        }
    }else {
        try {
            programmationManager.updateProgrammationTacheSimpleNonPreemptive(dynamic_cast<ProgrammationTacheSimpleNonPreemptive&>(*progTache), Date(dateProgrammation->date().day(), dateProgrammation->date().month(), dateProgrammation->date().year()), Horaire(horaireProgrammation->time().hour(), horaireProgrammation->time().minute()));
            EditerProgrammation *ed=dynamic_cast<EditerProgrammation*>(parentWidget());
            ed->updateListe();
        }catch(ProgrammationManagerException e) {
            QMessageBox::information(this, "Information", "Votre programmation n'a pas pu être modifiée. Vérifier que vous n'ayez pas déjà un évènement prévu à ce moment là.");
        }
    }
    this->close();
}
