#include "supprimerprecedence.h"
# include "fenetreprincipale.h"
# include "fenetregestionprojetexception.h"

SupprimerPrecedence::SupprimerPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent) :
    GestionPrecedence(projet, chaine, taille, titreT,parent)
{
    label->setText("Veuillez sélectionner la tâche que vous ne souhaitez plus imposer de finir avant de débuter votre tâche ");
}

void SupprimerPrecedence::retourFenetrePrincipaleValider(){
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Suppression de contrainte de précédence", "Veuillez séléctionner la tâche qui précède actuellement votre tâche");
    }
    else{
        cheminement = FenetreGestionProjet::getCheminement(actuel);
        try{
            removeProjet(&cheminement);
            titreTache2 = FenetreGestionProjet::getNomTacheAndRemoveTache(&cheminement);
            std::cout << "depuis la fenetre ;-) titre ; " << titreTache2 << std::endl; // -> test
            tailleChemin2 = new unsigned int;
            chemin2 = FenetreGestionProjet::recupCheminDepuisProjet(cheminement, tailleChemin2);
            nomProjet.supprimerPrecedence(chemin, *tailleChemin, titreTache, chemin2, *tailleChemin2, titreTache2);
            QMessageBox::information(this, "Suppression de contrainte de précédence", "Votre suppression de contrainte de précédence entre les tâches " + QString::fromStdString(titreTache) + " et " + QString::fromStdString(titreTache2) + " a bien été prise en compte.");
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Suppression de contrainte de précédence de projet", e.what());
        }
        this->close();
    }
}
