# include "gestionprecedence.h"
# include "fenetreannulervalider.h"
# include <QTreeWidget>
# include <QLabel>
# include "fenetregestionprojetexception.h"
# include <QCloseEvent>

GestionPrecedence::GestionPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent):
    FenetreAnnulerValider(parent), nomProjet(projet)
{
    titreTache = titreT;
    chemin = chaine;
    tailleChemin = taille;
    chemin2 = 0;
    tailleChemin2 = 0;
    titreTache2 = "";
    tree = new QTreeWidget(this);
    tree->setHeaderLabel("Mes projets");
    afficherTreeWidget(tree, &nomProjet);
    tree->show();
    hBox1 = new QHBoxLayout;
    hBox1->addWidget(label);
    label = new QLabel();
    hBox2 = new QHBoxLayout;
    hBox2->addWidget(tree);
    vBox->addLayout(hBox1);
    vBox->addLayout(hBox2);
    vBox->addLayout(hBoxAnnulerValider);
}

void GestionPrecedence::afficherTreeWidget(QTreeWidget* arbre, Element* element, QTreeWidgetItem * actuel){
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
            // std::cout << it->second->getTitre()<< std::endl; -> test
            afficherTreeWidget(arbre, it->second, item);
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
                afficherTreeWidget(arbre, it->second, item);
            }

        }
        else{
            // std::cout << "tache de fin" <<std::endl; // -> test
        }

    }
}

void GestionPrecedence::removeProjet(QList<QString>* chemin){
    if(chemin->isEmpty()){
        throw FenetreGestionProjetException("Veuillez sélectionner un élément et réitérer");
    }
    chemin->removeFirst();
}

void GestionPrecedence::closeEvent(QCloseEvent *event){
    if(chemin!=0){
        delete[] chemin;
        chemin = 0;
    }
    if(tailleChemin!=0){
        delete tailleChemin;
        tailleChemin = 0;
    }
    if(chemin2!=0){
        delete[] chemin2;
        chemin2 = 0;
    }
    if(tailleChemin2!=0){
        delete tailleChemin2;
        tailleChemin2 = 0;
    }
    FenetreAnnulerValider::closeEvent(event);
}

