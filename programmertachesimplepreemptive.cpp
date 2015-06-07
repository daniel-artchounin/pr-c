#include "programmertachesimplepreemptive.h"
#include "fenetreprincipale.h"

ProgrammerTacheSimplePreemptive::ProgrammerTacheSimplePreemptive(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent):
    ProgrammerTacheSimple(projet, chaine, taille, titreT, parent)
{
    pourcentage = new QSpinBox;
    pourcentage->setRange(1,100);
    formlayout->addRow("Pourcentage de programmation",pourcentage);
}

void ProgrammerTacheSimplePreemptive::retourFenetrePrincipaleValider(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    std::cout << "titre de tâche depuis interface : " << titreTache << std::endl;
    try{
        TacheSimplePreemptive& myTacheSimplePreemptive = nomProjet.accederTacheSimplePreemptive(
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
    this->close();
}
