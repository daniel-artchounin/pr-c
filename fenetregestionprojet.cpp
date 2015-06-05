#include "fenetregestionprojet.h"
# include "tachecomposite.h"
# include "projet.h"
# include "tachecomposite.h"
# include <QDate>
# include <QDebug>
# include <QMessageBox>

FenetreGestionProjet::FenetreGestionProjet(QWidget *parent) :
    QWidget(parent)
{
    creerTacheComposite = 0;
    creerTacheSimplePreemptive = 0;
    creerTacheSimpleNonPreemptive = 0;
    programmerTacheSimplePreemptive = 0;
    programmerTacheSimpleNonPreemptive = 0;
    ProjetManager& projetManager = ProjetManager::getInstance();
    tree = new QTreeWidget(this);
    hBox = new QHBoxLayout;
    afficherTreeWidget(0, projetManager, tree);
    tree->show();
    hBox->addWidget(tree);
    this->setLayout(hBox);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    monAction = new QAction("Test",this); // -> test
    creationTacheComposite = new QAction("Creer une tâche composite",this);;
    creationTacheSimplePreemptive = new QAction("Creer une tâche simple préemptive",this);;
    creationTacheSimpleNonPreemptive = new QAction("Créer une tâche simple non préemptive",this);
    programmationTacheSimplePreemptive = new QAction("Programmer une tâche simple préemptive",this);
    programmationTacheSimpleNonPreemptive = new QAction("Programmer une tâche simple non préemptive",this);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));
    connect(monAction, SIGNAL(triggered()),this, SLOT(test())); // -> test
    connect(creationTacheComposite, SIGNAL(triggered()),this, SLOT(fenetreCreerTacheComposite()));
    connect(creationTacheSimplePreemptive, SIGNAL(triggered()),this, SLOT(fenetreCreerTacheSimplePreemptive()));
    connect(creationTacheSimpleNonPreemptive, SIGNAL(triggered()),this, SLOT(fenetreCreerTacheSimpleNonPreemptive()));
    connect(programmationTacheSimplePreemptive, SIGNAL(triggered()),this, SLOT(fenetreProgrammerTacheSimplePreemptive()));
    connect(programmationTacheSimpleNonPreemptive, SIGNAL(triggered()),this, SLOT(fenetreProgrammerTacheSimpleNonPreemptive()));


}

void FenetreGestionProjet::afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel, Element* element){
    if(profondeur==0){
        arbre->clear();
        for(ProjetManager::iterator it= projetManager.begin(); it!=projetManager.end(); ++it){
            QTreeWidgetItem * topLevel = new QTreeWidgetItem();
            topLevel->setText(profondeur, QString::fromStdString(it->first)); // QString::fromStdString(it->second->getTitre())
            arbre->addTopLevelItem(topLevel);
            QString::fromStdString(it->second->getTitre());
            // std::cout<<it->second->getTitre();
            // std::cout << it->second->getTitre()<< std::endl; // -> test
            afficherTreeWidget(profondeur+1, projetManager, arbre, topLevel,it->second);


        }

    }
    else{
        Projet * projet = dynamic_cast<Projet *>(element);
        if(projet!=0){
            for(Projet::iterator it= projet->begin(); it!=projet->end(); ++it){
                QTreeWidgetItem * item = new QTreeWidgetItem();
                item->setText(0,QString::fromStdString((it->first)));
                actuel->addChild(item);
                // std::cout << it->second->getTitre()<< std::endl; -> test
                afficherTreeWidget(profondeur+1, projetManager, arbre, item,it->second);
            }
        }
        else{
            TacheComposite * tacheComposite = dynamic_cast<TacheComposite *>(element);
            if(tacheComposite!=0){
                // qDebug() << typeid(tacheComposite).name()<< QDate::currentDate(); -> test
                // qDebug() << typeid(*tacheComposite).name()<< QDate::currentDate(); -> test
                tacheComposite->getTitre();
                tacheComposite->begin();
                tacheComposite->end();
                for(TacheComposite::iterator it= tacheComposite->begin(); it!=tacheComposite->end(); ++it){
                    QTreeWidgetItem * item = new QTreeWidgetItem();
                    item->setText(0, QString::fromStdString((it->first)));
                    actuel->addChild(item);
                    // std::cout << it->second->getTitre()<< std::endl; -> test
                    afficherTreeWidget(profondeur+1, projetManager, arbre, item,it->second);
                }

            }
            else{
                // std::cout << "tache de fin" <<std::endl; // -> test
            }

        }

    }
}

void FenetreGestionProjet::showContextMenu(const QPoint& pos){
    // for most widgets
    QPoint globalPos = this->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("Supprimer une contrainte de précédence");
    myMenu.addAction("Ajouter une contrainte de précédence");
    myMenu.addAction(FenetrePrincipale::getInstance().getCreerActionProjet());
    myMenu.addAction(creationTacheComposite);
    myMenu.addAction(creationTacheSimplePreemptive);
    myMenu.addAction(creationTacheSimpleNonPreemptive);
    myMenu.addAction(programmationTacheSimplePreemptive);
    myMenu.addAction(programmationTacheSimpleNonPreemptive);
    // myMenu.addAction(monAction);
    myMenu.exec(globalPos);
    // QAction* selectedItem = ;
    // if (selectedItem)
    // {
        // something was chosen, do stuff
    // }
    // else
    // {
        // nothing was chosen
    // }
}

void FenetreGestionProjet::test(){
    qDebug() << "Le test semble fonctionner";
}


// créer une méthode privé pour éviter les duplications de code !!!
void FenetreGestionProjet::fenetreCreerTacheComposite(){
    if(creerTacheComposite !=0){
        delete creerTacheComposite;
        creerTacheComposite = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Création de tache composite", "Veuillez d'abord sélectionner le projet ou la tache composite mère de votre future tache");
    }
    else{
        cheminement = getCheminement(actuel);
        try{
            Projet& projet = getProjet(cheminement);
            unsigned int* taille = new unsigned int;
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            creerTacheComposite = new CreerTacheComposite(projet, chaine, taille);
            creerTacheComposite->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Création de projet", e.what());
        }
    }

}

void FenetreGestionProjet::fenetreCreerTacheSimplePreemptive(){
    if(creerTacheSimplePreemptive !=0){
        delete creerTacheSimplePreemptive;
        creerTacheSimplePreemptive = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Création de tache simple préemptive", "Veuillez d'abord sélectionner le projet ou la tache composite mère de votre future tache");
    }
    else{
        cheminement = getCheminement(actuel);
        try{
            Projet& projet = getProjet(cheminement);
            unsigned int* taille = new unsigned int;
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            creerTacheSimplePreemptive = new CreerTacheSimplePreemptive(projet, chaine, taille);
            creerTacheSimplePreemptive->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Création de tâche simple préemptive", e.what());
        }
    }

}

void FenetreGestionProjet::fenetreCreerTacheSimpleNonPreemptive(){
    if(creerTacheSimpleNonPreemptive !=0){
        delete creerTacheSimpleNonPreemptive;
        creerTacheSimpleNonPreemptive = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Création de tache simple non préemptive", "Veuillez d'abord sélectionner le projet ou la tache composite mère de votre future tache");
    }
    else{
        cheminement = getCheminement(actuel);
        try{
            Projet& projet = getProjet(cheminement);
            unsigned int* taille = new unsigned int;
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            creerTacheSimpleNonPreemptive = new CreerTacheSimpleNonPreemptive(projet, chaine, taille);
            creerTacheSimpleNonPreemptive->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Création de tache simple non préemptive", e.what());
        }
    }

}

void FenetreGestionProjet::fenetreProgrammerTacheSimplePreemptive(){
    if(programmerTacheSimplePreemptive !=0){
        delete programmerTacheSimplePreemptive;
        programmerTacheSimplePreemptive = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Programmation de tache simple préemptive", "Veuillez d'abord sélectionner le projet ou la tache composite mère de votre future tache");
    }
    else{
        cheminement = getCheminement(actuel);
        try{
            Projet& projet = getProjet(cheminement);
            std::string titreTache = getNomTacheAndRemoveTache(&cheminement);
            unsigned int* taille = new unsigned int;
            std::cout << "depuis la fenetre ;-) titre ; " << titreTache << std::endl;
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            programmerTacheSimplePreemptive = new ProgrammerTacheSimplePreemptive(projet, chaine, taille, titreTache);
            programmerTacheSimplePreemptive->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Création de projet", e.what());
        }
    }


}

void FenetreGestionProjet::fenetreProgrammerTacheSimpleNonPreemptive(){
    if(programmerTacheSimpleNonPreemptive !=0){
        delete programmerTacheSimpleNonPreemptive;
        programmerTacheSimpleNonPreemptive = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Programmation de tache simple non préemptive", "Veuillez d'abord sélectionner le projet ou la tache composite mère de votre future tache");
    }
    else{
        cheminement = getCheminement(actuel);
        try{
            std::cout << "************************" << std::endl;
            Projet& projet = getProjet(cheminement);
            std::string titreTache = getNomTacheAndRemoveTache(&cheminement);
            unsigned int* taille = new unsigned int;
            std::cout << "depuis la fenetre ;-) titre ; " << titreTache << std::endl ;
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            programmerTacheSimpleNonPreemptive = new ProgrammerTacheSimpleNonPreemptive(projet, chaine, taille, titreTache);
            programmerTacheSimpleNonPreemptive->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Création de projet", e.what());
        }
    }
}

// récupération du projet et gestion du cas d'erreur
Projet& FenetreGestionProjet::getProjet(QList<QString> chemin){
    if(chemin.isEmpty()){
        QMessageBox::warning(this, "Echec d'action", "Veuillez sélectionner un élément et réitérer");
    }
    else{
        ProjetManager& projetManager = ProjetManager::getInstance();
        QString& titreProjet = chemin.first();
        return projetManager.getProjet(titreProjet.toStdString());
    }
}
// récupération du projet et gestion du cas d'erreur
void FenetreGestionProjet::removeTache(QList<QString>* chemin){
    if(chemin->isEmpty()){
        QMessageBox::warning(this, "Echec d'action", "Veuillez sélectionner une tâche et réitérer");
    }
    else{
        chemin->removeLast();
    }
}

// récupération du projet et gestion du cas d'erreur
std::string FenetreGestionProjet::getNomTacheStd(QList<QString> chemin){
    if(chemin.isEmpty()){
        QMessageBox::warning(this, "Echec d'action", "Veuillez sélectionner une tâche et réitérer");
    }
    else{
        QString& titreTache = chemin.last();
        std::string titreTacheStd = titreTache.toStdString();
        std::cout << "Mon titre : " << titreTacheStd << std::endl;
        return titreTacheStd;
    }
}

// récupération du projet et gestion du cas d'erreur
std::string FenetreGestionProjet::getNomTacheAndRemoveTache(QList<QString>* chemin){
    if(chemin->isEmpty()){
        QMessageBox::warning(this, "Echec d'action", "Veuillez sélectionner une tâche et réitérer");
    }
    else{
        std::string titreProjetStd = getNomTacheStd(*chemin);
        removeTache(chemin);
        return titreProjetStd;
    }
}

std::string* FenetreGestionProjet::recupCheminDepuisProjet(QList<QString> chemin, unsigned int* taille){
    chemin.removeFirst();
    *taille = (unsigned int)chemin.size();
    qDebug() << "taille :"; // -> test
    qDebug() << *taille; // -> test
    qDebug() << "result"; // -> test
    std::string* cheminFinal = new std::string[*taille];
    unsigned int i = 0;
    for(QList<QString>::iterator it = chemin.begin() ; it != chemin.end() ; ++it){
        cheminFinal[i] = (*it).toStdString();
        qDebug() << QString::fromStdString(cheminFinal[i]); // -> test
        i++;
    }
    return cheminFinal;
}


// méthode permettant de générer le cheminement de la chaine à partir de la sélection du user
QList<QString> FenetreGestionProjet::getCheminement(QTreeWidgetItem * actuel){
    QList<QString> cheminement;
    do{
        cheminement.prepend(actuel->data(0,0).toString());
        actuel = actuel->parent();
    }while(actuel != 0);
    for(QList<QString>::iterator it = cheminement.begin() ; it != cheminement.end() ; ++it){
        qDebug() << *it; // -> test
    }
    return cheminement;
}
