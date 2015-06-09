# include "fenetregestionprojet.h"
# include "projet.h"
# include "tachecomposite.h"
# include <QDate>
# include <QDebug>
# include <QMessageBox>
# include "fenetregestionprojetexception.h"
# include "tachesimplenonpreemptive.h"
# include "tachesimplepreemptive.h"


FenetreGestionProjet::FenetreGestionProjet(QWidget *parent) :
    QWidget(parent)
{
    creerTacheComposite = 0;
    creerTacheSimplePreemptive = 0;
    creerTacheSimpleNonPreemptive = 0;
    programmerTacheSimplePreemptive = 0;
    programmerTacheSimpleNonPreemptive = 0;
    ajoutPrecedence = 0;
    suppressionPrecedence = 0;
    informationsTacheSimplePreemptive = 0;
    informationsTacheSimpleNonPreemptive = 0;
    informationsTacheComposite = 0;
    informationsProjet = 0;
    ProjetManager& projetManager = ProjetManager::getInstance();
    tree = new QTreeWidget(this);
    tree->setHeaderLabel("Mes projets");
    hBox = new QHBoxLayout;
    afficherTreeWidget(0, projetManager, tree);
    tree->show();
    hBox->addWidget(tree);
    this->setLayout(hBox);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    supprimerElement = new QAction("Supprimer un élément",this);
    consulterElement = new QAction("Consulter un élément",this);
    creationTacheComposite = new QAction("Creer une tâche composite",this);
    creationTacheSimplePreemptive = new QAction("Creer une tâche simple préemptive",this);
    creationTacheSimpleNonPreemptive = new QAction("Créer une tâche simple non préemptive",this);
    programmationTacheSimplePreemptive = new QAction("Programmer une tâche simple préemptive",this);
    programmationTacheSimpleNonPreemptive = new QAction("Programmer une tâche simple non préemptive",this);
    ajouterPrecedence = new QAction("Ajouter une contrainte de précédence",this);
    supprimerPrecedence = new QAction("Supprimer une contrainte de précédence",this);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));
    connect(creationTacheComposite, SIGNAL(triggered()),this, SLOT(fenetreCreerTacheComposite()));
    connect(creationTacheSimplePreemptive, SIGNAL(triggered()),this, SLOT(fenetreCreerTacheSimplePreemptive()));
    connect(creationTacheSimpleNonPreemptive, SIGNAL(triggered()),this, SLOT(fenetreCreerTacheSimpleNonPreemptive()));
    connect(programmationTacheSimplePreemptive, SIGNAL(triggered()),this, SLOT(fenetreProgrammerTacheSimplePreemptive()));
    connect(programmationTacheSimpleNonPreemptive, SIGNAL(triggered()),this, SLOT(fenetreProgrammerTacheSimpleNonPreemptive()));
    connect(ajouterPrecedence, SIGNAL(triggered()),this, SLOT(fenetreAjouterPrecedence()));
    connect(supprimerPrecedence, SIGNAL(triggered()),this, SLOT(fenetreSupprimerPrecedence()));
    connect(supprimerElement, SIGNAL(triggered()),this, SLOT(supprimerUnElemment()));
    connect(consulterElement, SIGNAL(triggered()),this, SLOT(consulterUnElemment()));
}

void FenetreGestionProjet::afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel, Element* element){
    if(profondeur==0){
        arbre->clear();
        for(ProjetManager::iterator it= projetManager.begin(); it!=projetManager.end(); ++it){
            QTreeWidgetItem * topLevel = new QTreeWidgetItem();
            topLevel->setText(profondeur, QString::fromStdString(it->first));
            arbre->addTopLevelItem(topLevel);
            QString::fromStdString(it->second->getTitre());
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
                afficherTreeWidget(profondeur+1, projetManager, arbre, item,it->second);
            }
        }
        else{
            TacheComposite * tacheComposite = dynamic_cast<TacheComposite *>(element);
            if(tacheComposite!=0){
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
            }

        }

    }
}

void FenetreGestionProjet::showContextMenu(const QPoint& pos){
    QPoint globalPos = this->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction(supprimerPrecedence);
    myMenu.addAction(ajouterPrecedence);
    myMenu.addAction(FenetrePrincipale::getInstance().getCreerActionProjet());
    myMenu.addAction(creationTacheComposite);
    myMenu.addAction(creationTacheSimplePreemptive);
    myMenu.addAction(creationTacheSimpleNonPreemptive);
    myMenu.addAction(programmationTacheSimplePreemptive);
    myMenu.addAction(programmationTacheSimpleNonPreemptive);
    myMenu.addAction(supprimerElement);
    myMenu.addAction(consulterElement);
    myMenu.exec(globalPos);
}

void FenetreGestionProjet::test(){
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
            Projet& projet = getAndRemoveProjet(&cheminement);
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
            Projet& projet = getAndRemoveProjet(&cheminement);
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
            Projet& projet = getAndRemoveProjet(&cheminement);
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
            Projet& projet = getAndRemoveProjet(&cheminement);
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
            QMessageBox::warning(this, "Programmation de tâche simple préemptive", e.what());
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
            Projet& projet = getAndRemoveProjet(&cheminement);
            std::string titreTache = getNomTacheAndRemoveTache(&cheminement);
            unsigned int* taille = new unsigned int;
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            programmerTacheSimpleNonPreemptive = new ProgrammerTacheSimpleNonPreemptive(projet, chaine, taille, titreTache);
            programmerTacheSimpleNonPreemptive->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Programmation de tâche simple non préemptive", e.what());
        }
    }
}

void FenetreGestionProjet::fenetreAjouterPrecedence(){
    if(ajoutPrecedence !=0){
        delete ajoutPrecedence;
        ajoutPrecedence = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Ajout de contrainte de précédence", "Veuillez d'abord sélectionner la tâche à laquelle vous souhaiter ajouter une contrainte de précédence");
    }
    else{
        cheminement = getCheminement(actuel);
        try{
            Projet& projet = getAndRemoveProjet(&cheminement);
            std::string titreTache = getNomTacheAndRemoveTache(&cheminement);
            unsigned int* taille = new unsigned int;
            // std::cout << "depuis la fenetre ;-) titre ; " << titreTache << std::endl; // -> test
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            ajoutPrecedence = new AjouterPrecedence(projet, chaine, taille, titreTache);
            ajoutPrecedence->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Ajout de contrainte de précédence", e.what());
        }
    }
}

void FenetreGestionProjet::fenetreSupprimerPrecedence(){
    if(suppressionPrecedence !=0){
        delete suppressionPrecedence;
        suppressionPrecedence = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Suppression de contrainte de précédence", "Veuillez d'abord sélectionner la tâche à laquelle vous souhaiter supprimer une contrainte de précédence");
    }
    else{
        cheminement = getCheminement(actuel);
        try{
            Projet& projet = getAndRemoveProjet(&cheminement);
            std::string titreTache = getNomTacheAndRemoveTache(&cheminement);
            unsigned int* taille = new unsigned int;
            std::cout << "depuis la fenetre ;-) titre ; " << titreTache << std::endl; // -> test
            std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
            suppressionPrecedence = new SupprimerPrecedence(projet, chaine, taille, titreTache);
            suppressionPrecedence->show();
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.hide();
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Suppression de contrainte de précédence", e.what());
        }
    }

}

void FenetreGestionProjet::supprimerUnElemment(){
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Supprimer un élément", "Veuillez d'abord sélectionner un élément pour le supprimer.");
    }
    else{
        try{
            ProjetManager& projetManager = ProjetManager::getInstance();
            cheminement = getCheminement(actuel);
            Projet& projet = getAndRemoveProjet(&cheminement);
            if(cheminement.size() == 0){
                projetManager.eraseItem(projet.getTitre());
            }
            else{
                std::string titreTache = getNomTacheAndRemoveTache(&cheminement);
                if(cheminement.size() == 0){
                    projet.supprimerTache(titreTache);
                }
                else{
                    unsigned int* taille = new unsigned int;
                    std::cout << "depuis la fenetre ;-) titre ; " << titreTache << std::endl; // -> test
                    std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
                    projet.supprimerTacheChemin(chaine, *taille, titreTache);

                }
            }
            FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            fenetrePrincipale.getZoneCentrale()->getFenetreEDT()->loadWeek();
            afficherTreeWidget(0, projetManager, tree);
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Suppression d'un élément", e.what());
        }
    }
}

void FenetreGestionProjet::consulterUnElemment(){
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    if(actuel == 0){
        QMessageBox::warning(this, "Consulter un élément", "Veuillez d'abord sélectionner un élément pour le consulter.");
    }
    else{
        try{
            cheminement = getCheminement(actuel);
            Projet& projet = getAndRemoveProjet(&cheminement);
            if(cheminement.size() == 0){
                // il s'agit d'un projet
                // il faut afficher le projet
                if(informationsProjet !=0){
                    delete informationsProjet;
                    informationsProjet = 0;
                }
                informationsProjet = new InformationsProjet(projet);
                informationsProjet->show();
                fenetrePrincipale.hide();
            }
            else{
                // il s'agit d'une tache
                std::string titreTache = getNomTacheAndRemoveTache(&cheminement);
                unsigned int* taille = new unsigned int;
                std::string * chaine = recupCheminDepuisProjet(cheminement, taille);
                try{
                    TacheComposite& tacheComposite = projet.accederTacheComposite(chaine, *taille, titreTache);
                    if(informationsTacheComposite !=0){
                        delete informationsTacheComposite;
                        informationsTacheComposite = 0;
                    }
                    informationsTacheComposite = new InformationsTacheComposite(tacheComposite);
                    informationsTacheComposite->show();
                    fenetrePrincipale.hide();
                }
                catch(ProjetException& e){
                    try{
                        TacheSimplePreemptive& tacheSimplePreemptive = projet.accederTacheSimplePreemptive(chaine, *taille, titreTache);
                        if(informationsTacheSimplePreemptive!=0){
                            delete informationsTacheSimplePreemptive;
                            informationsTacheSimplePreemptive = 0;
                        }
                        informationsTacheSimplePreemptive = new InformationsTacheSimplePreemptive(tacheSimplePreemptive);
                        informationsTacheSimplePreemptive->show();
                        fenetrePrincipale.hide();
                    }
                    catch(ProjetException& e){
                        try{
                            TacheSimpleNonPreemptive& tacheSimpleNonPreemptive = projet.accederTacheSimpleNonPreemptive(chaine, *taille, titreTache);
                            if(informationsTacheSimpleNonPreemptive!=0){
                                delete informationsTacheSimpleNonPreemptive;
                                informationsTacheSimpleNonPreemptive = 0;
                            }
                            informationsTacheSimpleNonPreemptive = new InformationsTacheSimpleNonPreemptive(tacheSimpleNonPreemptive);
                            informationsTacheSimpleNonPreemptive->show();
                            fenetrePrincipale.hide();
                        }catch(ProjetException& e){
                            QMessageBox::warning(this, "Consulter un élément", "Veuillez réitérer.");
                        }
                    }
                }
            }
            // FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
            // fenetrePrincipale.getZoneCentrale()->getFenetreEDT()->loadWeek();
            // afficherTreeWidget(0, projetManager, tree);
        }
        catch (std::logic_error& e){
            QMessageBox::warning(this, "Suppression d'un élément", e.what());
        }
    }
}

// récupération du projet et gestion du cas d'erreur
Projet& FenetreGestionProjet::getAndRemoveProjet(QList<QString>* chemin){
    if(chemin->isEmpty()){
        throw FenetreGestionProjetException("Veuillez sélectionner un élément et réitérer");
    }
    ProjetManager& projetManager = ProjetManager::getInstance();
    QString& titreProjet = chemin->first();
    chemin->removeFirst();
    return projetManager.getProjet(titreProjet.toStdString());
}

// récupération du projet et gestion du cas d'erreur
void FenetreGestionProjet::removeTache(QList<QString>* chemin){
    if(chemin->isEmpty()){
        throw FenetreGestionProjetException("Veuillez sélectionner une tâche et réitérer");
    }
    else{
        chemin->removeLast();
    }
}

// récupération du projet et gestion du cas d'erreur
std::string FenetreGestionProjet::getNomTacheStd(QList<QString> chemin){
    if(chemin.isEmpty()){
        throw FenetreGestionProjetException("Veuillez sélectionner une tâche et réitérer");
    }
    QString& titreTache = chemin.last();
    std::string titreTacheStd = titreTache.toStdString();
    // std::cout << "Mon titre : " << titreTacheStd << std::endl;
    return titreTacheStd;
}

// récupération du projet et gestion du cas d'erreur
std::string FenetreGestionProjet::getNomTacheAndRemoveTache(QList<QString>* chemin){
    if(chemin->isEmpty()){
        throw FenetreGestionProjetException("Veuillez sélectionner une tâche et réitérer");
    }
    std::string titreProjetStd = getNomTacheStd(*chemin);
    removeTache(chemin);
    return titreProjetStd;
}

std::string* FenetreGestionProjet::recupCheminDepuisProjet(QList<QString> chemin, unsigned int* taille){
    *taille = (unsigned int)chemin.size();
    std::string* cheminFinal = new std::string[*taille];
    unsigned int i = 0;
    for(QList<QString>::iterator it = chemin.begin() ; it != chemin.end() ; ++it){
        cheminFinal[i] = (*it).toStdString();
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
    return cheminement;
}
