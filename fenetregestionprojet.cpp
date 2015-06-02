#include "fenetregestionprojet.h"
# include "tachecomposite.h"
# include "projet.h"
# include "tachecomposite.h"
# include <QDate>
# include <QDebug>
FenetreGestionProjet::FenetreGestionProjet(QWidget *parent) :
    QWidget(parent)
{
    ProjetManager& projetManager = ProjetManager::getInstance();
    tree = new QTreeWidget(this);
    hBox = new QHBoxLayout;
    afficherTreeWidget(0, projetManager, tree);
    tree->show();
    hBox->addWidget(tree);
    this->setLayout(hBox);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    monAction = new QAction("Test",this);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));
    connect(monAction, SIGNAL(triggered()),this, SLOT(test()));

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
    myMenu.addAction("Créer une tâche composite");
    myMenu.addAction("Créer une tâche simple non préemptive");
    myMenu.addAction("Créer une tâche simple préemptive");
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

