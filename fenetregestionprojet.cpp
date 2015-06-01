#include "fenetregestionprojet.h"
# include "tachecomposite.h"
# include "projet.h"
# include "tachecomposite.h"
# include <QDate>
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
}

void FenetreGestionProjet::afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel, Element* element){
    if(profondeur==0){
        for(ProjetManager::iterator it= projetManager.begin(); it!=projetManager.end(); ++it){
            QTreeWidgetItem * topLevel = new QTreeWidgetItem();
            topLevel->setText(profondeur, QString::fromStdString(it->first)); // QString::fromStdString(it->second->getTitre())
            arbre->addTopLevelItem(topLevel);
            QString::fromStdString(it->second->getTitre());
            // std::cout<<it->second->getTitre();
           std::cout << it->second->getTitre()<< std::endl;
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
                std::cout << it->second->getTitre()<< std::endl;
                afficherTreeWidget(profondeur+1, projetManager, arbre, item,it->second);
            }
        }
        else{
            TacheComposite * tacheComposite = dynamic_cast<TacheComposite *>(element);
            if(tacheComposite!=0){
                // qDebug() << typeid(tacheComposite).name()<< QDate::currentDate();
                // qDebug() << typeid(*tacheComposite).name()<< QDate::currentDate();
                tacheComposite->getTitre();
                tacheComposite->begin();
                tacheComposite->end();
                for(TacheComposite::iterator it= tacheComposite->begin(); it!=tacheComposite->end(); ++it){
                    QTreeWidgetItem * item = new QTreeWidgetItem();
                    item->setText(0, QString::fromStdString((it->first)));
                    actuel->addChild(item);
                    std::cout << it->second->getTitre()<< std::endl;
                    afficherTreeWidget(profondeur+1, projetManager, arbre, item,it->second);
                }

            }
            else{
                std::cout << "tache de fin" <<std::endl;
            }

        }

    }
}
