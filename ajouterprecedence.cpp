# include "ajouterprecedence.h"
# include "fenetreprincipale.h"
# include "fenetregestionprojetexception.h"

AjouterPrecedence::AjouterPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent) :
    QWidget(parent), nomProjet(projet)
{
    std::cout << "Bonjour" <<std::endl;
    titreTache = titreT;
    chemin = chaine;
    tailleChemin = taille;
    chemin2 = 0;
    tailleChemin2 = 0;
    titreTache2 = "";
    tree = new QTreeWidget(this);
    afficherTreeWidget(tree, &nomProjet);
    tree->show();
    label = new QLabel("Veuillez sélectionne la tâche que vous souhaitez imposer de finir avant de débuter votre tâche "); // << titreTache);
    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauver");
    hBox1 = new QHBoxLayout;
    hBox1->addWidget(label);
    hBox2 = new QHBoxLayout;
    hBox2->addWidget(tree);
    hBox3 = new QHBoxLayout;
    hBox3->addWidget(annuler);
    hBox3->addWidget(sauver);
    vBox = new QVBoxLayout(this);
    vBox->addLayout(hBox1);
    vBox->addLayout(hBox2);
    vBox->addLayout(hBox3);
    connect(annuler,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleAnnuler()));
    connect(sauver,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleSauver()));
    // QTreeWidget * tree; // le tree-view
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
void AjouterPrecedence::retourFenetrePrincipaleAnnuler(){
    this->close();
}

void AjouterPrecedence::retourFenetrePrincipaleSauver(){
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

void AjouterPrecedence::closeEvent(QCloseEvent *event){
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
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.show();
    event->accept();
}

void AjouterPrecedence::removeProjet(QList<QString>* chemin){
    if(chemin->isEmpty()){
        throw FenetreGestionProjetException("Veuillez sélectionner un élément et réitérer");
    }
    chemin->removeFirst();
}
