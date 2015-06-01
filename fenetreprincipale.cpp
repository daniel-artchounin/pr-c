#include "fenetreprincipale.h"
# include "programmationmanager.h"

FenetrePrincipale * FenetrePrincipale::instance=0; //initialisation à null, pour la première vérification

void FenetrePrincipale::libererInstance(){
    if(instance != 0){
        delete instance;
        instance = 0;
    }

}

FenetrePrincipale& FenetrePrincipale::getInstance(){
    if(instance == 0){
        instance = new FenetrePrincipale();
    }
    return *instance;
}



FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent)
{
    dejaSauver = false;
    // creation de la barre de menus
    menuGestion = menuBar()->addMenu("&Gestion");
    menuFenetre = menuBar()->addMenu("&Fenêtre");
    menuAide = menuBar()->addMenu("&Aide");
    // creation de la barre d'outils
    barrreOutils = addToolBar("BarreOutils");
    // creation des actions
    actionSave = new QAction("&Sauver", this);
    actionLoad = new QAction("&Charger", this);
    actionCreerProjet = new QAction("Créer un &projet", this);
    actionQuitter = new QAction("&Quitter ProjectCalendar", this);
    // raccourcis des actions
    // actionSave->setShortcut(QKeySequence("Ctrl+S"));
    // actionLoad->setShortcut(QKeySequence("Ctrl+L"));
    // actionCreerProjet->setShortcut(QKeySequence("Ctrl+P"));
    // actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    // icones des actions
    actionSave->setIcon(QIcon("../pr-c/images/enregistrer.png"));
    actionLoad->setIcon(QIcon("../pr-c/images/charger.png"));
    actionCreerProjet->setIcon(QIcon("../pr-c/images/creer_projet.jpeg"));
    actionQuitter->setIcon(QIcon("../pr-c/images/quitter.png"));
    // ajouts des actions à la barre de menus
    menuGestion->addAction(actionSave);
    menuGestion->addAction(actionLoad);
    menuGestion->addAction(actionCreerProjet);
    menuFenetre->addAction(actionQuitter);
    // ajouts des actions à la barre d'outils
    barrreOutils->addAction(actionLoad);
    barrreOutils->addAction(actionSave);
    barrreOutils->addAction(actionCreerProjet);
    // instanciation et définition de la zone centrale
    zoneCentrale = new ZoneCentrale(this);
    setCentralWidget(zoneCentrale);
    // connections
    connect(actionSave, SIGNAL(triggered()), this, SLOT(sauverFichier()));
    connect(actionLoad, SIGNAL(triggered()), this, SLOT(chargerFichier()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void FenetrePrincipale::chargerFichier(){
    QString fichier;
    if(!dejaSauver){
            int reponse = QMessageBox::question(this, "Confirmation de chargement", "N'oubliez pas de sauvegarder votre travail en cours sinon les modifications en cours serons définitivement perdues. Etes-vous sur de vouloir charger un fichier de données ?", QMessageBox ::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes)

            {
                    fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers XML (*.xml)");
                    ProjetManager::libererInstance();
                    ProgrammationManager::libererInstance();
                    load(fichier);
                    zoneCentrale->getFenetreGestionProjet()->afficherTreeWidget(0,ProjetManager::getInstance(),zoneCentrale->getFenetreGestionProjet()->getTree());
                    QMessageBox::information(this, "Information", "Votre fichier de données "+fichier+" a bien été chargé");

            }

            else if (reponse == QMessageBox::No)

            {

                QMessageBox::information(this, "Information", "Aucun fichier n'a été chargé");

            }
    }else{
        fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers XML (*.xml)");
        ProjetManager::libererInstance();
        ProgrammationManager::libererInstance();
        load(fichier);
        zoneCentrale->getFenetreGestionProjet()->afficherTreeWidget(0,ProjetManager::getInstance(),zoneCentrale->getFenetreGestionProjet()->getTree());
        QMessageBox::information(this, "Information", "Votre fichier de données "+fichier+" a bien été chargé");
        dejaSauver = false;
    }
}

void FenetrePrincipale::sauverFichier(){
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier XML (*.xml)");
    save(fichier);
    dejaSauver = true;
}

void FenetrePrincipale::closeEvent(QCloseEvent *event)
{
    libererInstance();
    event->accept();

}
