# include "supprimerprecedence.h"
# include "fenetreprincipale.h"
# include "fenetregestionprojetexception.h"
# include <QDebug>

SupprimerPrecedence::SupprimerPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent) :
    GestionPrecedence(projet, chaine, taille, titreT,parent)
{
    label->setText("Veuillez sélectionner la tâche que vous ne souhaitez plus imposer de finir avant de débuter votre tâche ");
    listeDeTaches = new QListWidget(this);
    afficherListeTacheWidget();
    hBox2->addWidget(listeDeTaches);
    vBox->addLayout(hBox1);
    vBox->addLayout(hBox2);
    vBox->addLayout(hBoxAnnulerValider);
    listeDeTaches->show();
}

void SupprimerPrecedence::retourFenetrePrincipaleValider(){
    QListWidgetItem * actuel = listeDeTaches->currentItem();
    if(actuel == 0){
        QMessageBox::warning(this, "Suppression de contrainte de précédence", "Veuillez séléctionner la tâche qui précède actuellement votre tâche");
    }
    else{
        QString cheminement = listeDeTaches->currentItem()->text();
        std::cout << "cheminement (SupprimerPrecedence::retourFenetrePrincipaleValider) :" << cheminement.toStdString() << std::endl;
        QStringList liste = cheminement.split("/");
        try{
            tailleChemin2 = new unsigned int;
            chemin2 = fromQStringListToStdStringArray(liste, tailleChemin2);
            titreTache2 = chemin2[*tailleChemin2-1];
            nomProjet.supprimerPrecedence(chemin2, (*tailleChemin2)-1, titreTache2, chemin, *tailleChemin, titreTache);
            QMessageBox::information(this, "Suppression de contrainte de précédence", "Votre suppression de contrainte de précédence entre les tâches " + QString::fromStdString(titreTache) + " et " + QString::fromStdString(titreTache2) + " a bien été prise en compte.");
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Suppression de contrainte de précédence de projet", e.what());
        }
        this->close();
    }
}

std::string* SupprimerPrecedence::fromQStringListToStdStringArray(QStringList chemin, unsigned int* taille){
    *taille = (unsigned int)chemin.size();
    std::string* cheminFinal = new std::string[*taille];
    for(int i = 0; i < chemin.size(); ++i){
        cheminFinal[i] = chemin.at(i).toStdString();
    }
    return cheminFinal;
}

void SupprimerPrecedence::afficherListeTacheWidget(){
    try{
        Tache& tache = nomProjet.accederTache(chemin, *tailleChemin, titreTache);
        for(Tache::tp_iterator it = tache.tPBegin(); it!= tache.tPEnd() ; ++it){
            new QListWidgetItem(QString::fromStdString(it->first), listeDeTaches);
        }
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Suppression de contrainte de précédence de projet", e.what());
        this->close();
    }
}
