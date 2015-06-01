#include "fenetreprincipale.h"
# include "programmationmanager.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent)
{
    dejaSauver = false;
    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");
    barrreOutils = addToolBar("BarreOutils");
    actionSave = new QAction("&Sauver", this);
    actionLoad = new QAction("&Charger", this);
    actionSave->setShortcut(QKeySequence("Ctrl+S"));
    actionLoad->setShortcut(QKeySequence("Ctrl+L"));
    actionSave->setIcon(QIcon("../pr-c/images/enregistrer.png"));
    actionLoad->setIcon(QIcon("../pr-c/images/charger.png"));
    zoneCentrale = new ZoneCentrale(this);
    setCentralWidget(zoneCentrale);
    barrreOutils->addAction(actionLoad);
    barrreOutils->addAction(actionSave);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(sauverFichier()));
    connect(actionLoad, SIGNAL(triggered()), this, SLOT(chargerFichier()));
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

