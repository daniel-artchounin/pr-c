#include "fenetregestionprojet.h"
# include "tachecomposite.h"
# include "projet.h"
# include "tachecomposite.h"
# include <QDate>
# include <QDebug>

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
    monAction = new QAction("Test",this);
    creationTacheComposite = new QAction("Creer une tâche composite",this);;
    creationTacheSimplePreemptive = new QAction("Creer une tâche simple préemptive",this);;
    creationTacheSimpleNonPreemptive = new QAction("Créer une tâche simple non préemptive",this);
    programmationTacheSimplePreemptive = new QAction("Programmer une tâche simple préemptive",this);
    programmationTacheSimpleNonPreemptive = new QAction("Programmer une tâche simple non préemptive",this);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));
    connect(monAction, SIGNAL(triggered()),this, SLOT(test()));
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
    myMenu.addAction("Créer un projet");
    myMenu.addAction(creationTacheComposite);
    myMenu.addAction(creationTacheSimplePreemptive);
    myMenu.addAction(creationTacheSimpleNonPreemptive);
    myMenu.addAction(programmationTacheSimplePreemptive);
    myMenu.addAction(programmationTacheSimpleNonPreemptive);
    myMenu.addAction(monAction);
    // myMenu.addAction("Programmer une tâche simple non préemptive");
    // myMenu.addAction("Programmer une tâche simple préemptive");
    QAction* selectedItem = myMenu.exec(globalPos);
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

void FenetreGestionProjet::fenetreCreerTacheComposite(){
    if(creerTacheComposite !=0){
        delete creerTacheComposite;
        creerTacheComposite = 0;
    }
    QTreeWidgetItem * actuel = tree->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        // afficher un message
        qDebug() << "bonjour";
    }
    else{
        do{
            // qDebug() << actuel; -> test
            cheminement.prepend(actuel->data(0,0).toString());
            // qDebug() << actuel; -> test
            actuel = actuel->parent();
            // qDebug() << actuel; -> test
        }while(actuel != 0);
    }
    for(QList<QString>::iterator it = cheminement.begin() ; it != cheminement.end() ; ++it){
        qDebug() << *it;

    }

    // QString sel_projet = selection[0]->data(0, 0).toString();
    // QStringList arg;
    // QString user = "/U=******";
    // QString mdp = "/P=" + motDePasse->text();
    // qDebug() << sel_projet;
    creerTacheComposite = new CreerTacheComposite;
    creerTacheComposite->show();
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.hide();
}

void FenetreGestionProjet::fenetreCreerTacheSimplePreemptive(){
    if(creerTacheSimplePreemptive !=0){
        delete creerTacheSimplePreemptive;
        creerTacheSimplePreemptive = 0;
    }
    creerTacheSimplePreemptive = new CreerTacheSimplePreemptive;
    creerTacheSimplePreemptive->show();
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.hide();
}

void FenetreGestionProjet::fenetreCreerTacheSimpleNonPreemptive(){
    if(creerTacheSimpleNonPreemptive !=0){
        delete creerTacheSimpleNonPreemptive;
        creerTacheSimpleNonPreemptive = 0;
    }
    creerTacheSimpleNonPreemptive = new CreerTacheSimpleNonPreemptive;
    creerTacheSimpleNonPreemptive->show();
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.hide();
}

void FenetreGestionProjet::fenetreProgrammerTacheSimplePreemptive(){
    if(programmerTacheSimplePreemptive !=0){
        delete programmerTacheSimplePreemptive;
        programmerTacheSimplePreemptive = 0;
    }
    programmerTacheSimplePreemptive = new ProgrammerTacheSimplePreemptive;
    programmerTacheSimplePreemptive->show();
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.hide();
}

void FenetreGestionProjet::fenetreProgrammerTacheSimpleNonPreemptive(){
    if(programmerTacheSimpleNonPreemptive !=0){
        delete programmerTacheSimpleNonPreemptive;
        programmerTacheSimpleNonPreemptive = 0;
    }
    programmerTacheSimpleNonPreemptive = new ProgrammerTacheSimpleNonPreemptive;
    programmerTacheSimpleNonPreemptive->show();
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.hide();
}

