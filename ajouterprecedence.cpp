# include "ajouterprecedence.h"
# include "fenetreprincipale.h"
# include "fenetregestionprojetexception.h"

AjouterPrecedence::AjouterPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent) :
    GestionPrecedence(projet, chaine, taille, titreT, parent)
{
    tree = new QTreeWidget(this);
    tree->setHeaderLabel("Mes projets");
    afficherTreeWidget(tree, &nomProjet);
    hBox2->addWidget(tree);
    vBox->addLayout(hBox1);
    vBox->addLayout(hBox2);
    vBox->addLayout(hBoxAnnulerValider);
    tree->show();
    label->setText("Veuillez sélectionner la tâche que vous souhaitez imposer de finir avant de débuter votre tâche : ");
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
            tailleChemin2 = new unsigned int;
            chemin2 = FenetreGestionProjet::recupCheminDepuisProjet(cheminement, tailleChemin2);
            nomProjet.ajouterPrecedence(chemin2, *tailleChemin2, titreTache2, chemin, *tailleChemin, titreTache);
            QMessageBox::information(this, "Ajout de contrainte de précédence", "Votre ajout de contrainte de précédence entre les tâches " + QString::fromStdString(titreTache) + " et " + QString::fromStdString(titreTache2) +" a bien été prise en compte.");
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Création de projet", e.what());
        }
        this->close();
    }
}

void AjouterPrecedence::afficherTreeWidget(QTreeWidget* arbre, Element* element, QTreeWidgetItem * actuel){
    Projet * projet = dynamic_cast<Projet *>(element);
    if(projet!=0){
        // l'élément en cours est un projet
        arbre->clear();
        QTreeWidgetItem* topLevel = new QTreeWidgetItem();
        topLevel->setText(0, QString::fromStdString(projet->getTitre()));
        arbre->addTopLevelItem(topLevel);
        for(Projet::iterator it= projet->begin(); it!=projet->end(); ++it){
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0,QString::fromStdString((it->first)));
            topLevel->addChild(item);
            afficherTreeWidget(arbre, it->second, item);
        }
    }
    else{
        TacheComposite * tacheComposite = dynamic_cast<TacheComposite *>(element);
        if(tacheComposite!=0){
            for(TacheComposite::iterator it= tacheComposite->begin(); it!=tacheComposite->end(); ++it){
                QTreeWidgetItem * item = new QTreeWidgetItem();
                item->setText(0, QString::fromStdString((it->first)));
                actuel->addChild(item);
                afficherTreeWidget(arbre, it->second, item);
            }

        }
    }
}

void AjouterPrecedence::removeProjet(QList<QString>* chemin){
    if(chemin->isEmpty()){
        throw FenetreGestionProjetException("Veuillez sélectionner un élément et réitérer");
    }
    chemin->removeFirst();
}

