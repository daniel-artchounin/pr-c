# include "ajouterprecedence.h"
# include "fenetreprincipale.h"
# include "fenetregestionprojetexception.h"

AjouterPrecedence::AjouterPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent) :
    GestionPrecedence(projet, chaine, taille, titreT, parent)
{
    label->setText("Veuillez sélectionne la tâche que vous souhaitez imposer de finir avant de débuter votre tâche ");
}

void AjouterPrecedence::retourFenetrePrincipaleValider(){
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Création de tache composite", "Veuillez d'abord sélectionner le projet ou la tache composite mère de votre future tache");
    }
    else{
        cheminement = FenetreGestionProjet::getCheminement(actuel);
        try{
            removeProjet(&cheminement);
            titreTache2 = FenetreGestionProjet::getNomTacheAndRemoveTache(&cheminement);
            std::cout << "depuis la fenetre ;-) titre ; " << titreTache2 << std::endl; // -> test
            tailleChemin2 = new unsigned int;
            chemin2 = FenetreGestionProjet::recupCheminDepuisProjet(cheminement, tailleChemin2);
            nomProjet.ajouterPrecedence(chemin, *tailleChemin, titreTache, chemin2, *tailleChemin2, titreTache2);
            QMessageBox::information(this, "Ajout de contrainte de précédence", "Votre modification a bien été prise en compte");
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Création de projet", e.what());
        }
        this->close();
    }
}
