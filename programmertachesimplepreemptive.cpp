#include "programmertachesimplepreemptive.h"
#include "fenetreprincipale.h"
#include "programmationmanagerexception.h"

ProgrammerTacheSimplePreemptive::ProgrammerTacheSimplePreemptive(Projet* projet, std::string * chaine, unsigned int* taille, std::string& titreT, QWidget *parent):
    ProgrammerTacheSimple(projet, chaine, taille, titreT, parent)
{
    pourcentage = new QSpinBox;
    pourcentage->setRange(1,100);
    formlayout->addRow("Pourcentage de programmation",pourcentage);
}

ProgrammerTacheSimplePreemptive::ProgrammerTacheSimplePreemptive(ProgrammationTacheSimplePreemptive* prog, QWidget *parent):ProgrammerTacheSimple(prog, parent) {
    dateDebut->setText(QString::fromStdString(prog->getTacheSimple().getDateDebut().toString()));
    horaireDebut->setText(QString::fromStdString(prog->getTacheSimple().getHoraireDebut().toString()));
    dateEcheance->setText(QString::fromStdString(prog->getTacheSimple().getDateFin().toString()));
    heureEcheance->setText(QString::fromStdString(prog->getTacheSimple().getHoraireFin().toString()));
    duree->setText(QString::fromStdString(prog->getTacheSimple().getDuree().toString()));
    pourcentage = new QSpinBox;
    pourcentage->setRange(1,100);
    pourcentage->setValue(prog->getPourcentage());
    formlayout->addRow("Pourcentage de programmation",pourcentage);
}

void ProgrammerTacheSimplePreemptive::retourFenetrePrincipaleValider(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    if(progTache==0) {
        try{
            TacheSimplePreemptive& myTacheSimplePreemptive = nomProjet->accederTacheSimplePreemptive(
                        chemin,
                        *tailleChemin,
                        titreTache
                        );
            programmationManager.addProgrammationTacheSimplePreemptive(
                        Date(dateProgrammation->date().day(), dateProgrammation->date().month(), dateProgrammation->date().year()),
                        Horaire(horaireProgrammation->time().hour(), horaireProgrammation->time().minute()),
                        pourcentage->value(),
                        myTacheSimplePreemptive
                        );
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.getZoneCentrale()->getFenetreEDT()->loadWeek();
        }
        catch(std::logic_error& e){
            QMessageBox::warning(this, "Création de tâche tâche simple préemptive", e.what());
        }
    }else {
        try {
            programmationManager.updateProgrammationTacheSimplePreemptive(dynamic_cast<ProgrammationTacheSimplePreemptive&>(*progTache), Date(dateProgrammation->date().day(), dateProgrammation->date().month(), dateProgrammation->date().year()), Horaire(horaireProgrammation->time().hour(), horaireProgrammation->time().minute()), pourcentage->value());
            EditerProgrammation *ed=dynamic_cast<EditerProgrammation*>(parentWidget());
            ed->updateListe();
        }catch(ProgrammationManagerException e) {
            QMessageBox::information(this, "Information", "Votre programmation n'a pas pu être modifiée. Vérifier que vous n'ayez pas déjà un évènement prévu à ce moment là.");
        }
    }
    this->close();
}
