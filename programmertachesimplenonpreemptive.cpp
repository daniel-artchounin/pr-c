#include "programmertachesimplenonpreemptive.h"
#include "fenetreprincipale.h"

ProgrammerTacheSimpleNonPreemptive::ProgrammerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent):
    ProgrammerTacheSimple(projet, chaine, taille, titreT, parent)
{

}

void ProgrammerTacheSimpleNonPreemptive::retourFenetrePrincipaleValider(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    try{
        std::cout << "description : " << nomProjet.getTitre() << std::endl;
        std::cout << "description : " << *tailleChemin << std::endl;
        for(unsigned int i =0; i < *tailleChemin; i++){
            std::cout << "TC" << chemin[i]<<std::endl;
        }
        std::cout << "titreTache depuis fenetre sauver :" << std::endl ;
        std::cout << titreTache << std::endl ;

        TacheSimpleNonPreemptive& myTacheSimpleNonPreemptive = nomProjet.accederTacheSimpleNonPreemptive(
                    chemin,
                    *tailleChemin,
                    titreTache
                    );
        programmationManager.addProgrammationTacheSimpleNonPreemptive(
                    Date(dateProgrammation->date().day(), dateProgrammation->date().month(), dateProgrammation->date().year()),
                    Horaire(horaireProgrammation->time().hour(), horaireProgrammation->time().minute()),
                    myTacheSimpleNonPreemptive
                    );
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Création de tâche tâche simple non préemptive", e.what());
    }
    this->close();
}
