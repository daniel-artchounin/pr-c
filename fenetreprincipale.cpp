# include "fenetreprincipale.h"
# include "programmationmanager.h"
# include "creerprojet.h"
# include <QMenuBar>
# include <QMessageBox>
# include <QFileDialog>
# include <QCloseEvent>
# include <QApplication>
# include <QString>
# include <QDebug>
# include "fenetregestionprojet.h"
# include "fenetregestionprojetexception.h"

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
    creerProjet = 0;
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
    actionPrevious = new QAction("Semaine précédente", this);
    actionNext = new QAction("Semaine suivante", this);
    actionExportSemaine = new QAction("Exporter la semaine actuelle", this);
    actionExportProjet = new QAction("Exporter le projet sélectionné", this);
    actionEnregistrerProjet = new QAction("Enregistrer le projet sélectionné", this);
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
    actionPrevious->setIcon(QIcon("../pr-c/images/previous.png"));
    actionNext->setIcon(QIcon("../pr-c/images/next.png"));
    actionExportSemaine->setIcon(QIcon("../pr-c/images/export_semaine.png"));
    actionExportProjet->setIcon(QIcon("../pr-c/images/export_projet.png"));
    actionEnregistrerProjet->setIcon(QIcon("../pr-c/images/enregistrer_projet.png"));

    // ajouts des actions à la barre de menus
    menuGestion->addAction(actionSave);
    menuGestion->addAction(actionLoad);
    menuGestion->addAction(actionCreerProjet);
    menuGestion->addAction(actionExportSemaine);
    menuGestion->addAction(actionExportProjet);
    menuGestion->addAction(actionEnregistrerProjet);
    menuFenetre->addAction(actionQuitter);


    // ajouts des actions à la barre d'outils
    barrreOutils->addAction(actionLoad);
    barrreOutils->addAction(actionSave);
    barrreOutils->addAction(actionCreerProjet);
    barrreOutils->addAction(actionExportSemaine);
    barrreOutils->addAction(actionExportProjet);
    barrreOutils->addAction(actionEnregistrerProjet);
    barrreOutils->addAction(actionPrevious);
    barrreOutils->addAction(actionNext);

    // instanciation et définition de la zone centrale
    zoneCentrale = new ZoneCentrale(this);
    setCentralWidget(zoneCentrale);
    // connections
    connect(actionSave, SIGNAL(triggered()), this, SLOT(sauverFichier()));
    connect(actionLoad, SIGNAL(triggered()), this, SLOT(chargerFichier()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionCreerProjet, SIGNAL(triggered()), this, SLOT(fenetreCreerProjet()));
    connect(actionPrevious, SIGNAL(triggered()), this, SLOT(goToPreviousWeek()));
    connect(actionNext, SIGNAL(triggered()), this, SLOT(goToNextWeek()));
    connect(actionExportProjet, SIGNAL(triggered()), this, SLOT(exporterUnProjet()));
    connect(actionEnregistrerProjet, SIGNAL(triggered()), this, SLOT(enregistrerUnProjet()));
    connect(actionExportSemaine, SIGNAL(triggered()), this, SLOT(exporterUneSemaine()));
}


void FenetrePrincipale::chargerFichier(){
    if(creerProjet !=0){
        delete creerProjet;
        creerProjet = 0;
    }
    QString fichier;
    if(!dejaSauver){
            int reponse = QMessageBox::question(this, "Confirmation de chargement", "N'oubliez pas de sauvegarder votre travail en cours sinon les modifications en cours seront définitivement perdues. Etes-vous sur de vouloir charger un fichier de données ?", QMessageBox ::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {                    
                fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers XML (*.xml)");                
                qDebug() << fichier;
                if(!fichier.isEmpty()){
                    ProjetManager::libererInstance();
                    ProgrammationManager::libererInstance();
                    load(fichier);
                    zoneCentrale->getFenetreGestionProjet()->afficherTreeWidget(0,ProjetManager::getInstance(),zoneCentrale->getFenetreGestionProjet()->getTree());
                    QMessageBox::information(this, "Information", "Votre fichier de données "+fichier+" a bien été chargé");
                }

            }
            else if (reponse == QMessageBox::No)
            {
                QMessageBox::information(this, "Information", "Aucun fichier n'a été chargé");
            }
    }else{
        fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers XML (*.xml)");
        if(!fichier.isEmpty()){
            ProjetManager::libererInstance();
            ProgrammationManager::libererInstance();
            load(fichier);
            zoneCentrale->getFenetreGestionProjet()->afficherTreeWidget(0,ProjetManager::getInstance(),zoneCentrale->getFenetreGestionProjet()->getTree());
            QMessageBox::information(this, "Information", "Votre fichier de données "+fichier+" a bien été chargé");
            dejaSauver = false;
        }
    }
    zoneCentrale->getFenetreEDT()->loadWeek();
}

void FenetrePrincipale::sauverFichier(){
    if(creerProjet !=0){
        delete creerProjet;
        creerProjet = 0;
    }
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier XML (*.xml)");
    if(!fichier.isEmpty()){
        save(fichier);
        dejaSauver = true;
    }
}

void FenetrePrincipale::fenetreCreerProjet(){
    if(creerProjet !=0){
        delete creerProjet;
        creerProjet = 0;
    }    
    creerProjet = new CreerProjet;
    creerProjet->show();
    this->hide();
}


void FenetrePrincipale::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );
    zoneCentrale->getFenetreGestionProjet()->afficherTreeWidget(0,ProjetManager::getInstance(),zoneCentrale->getFenetreGestionProjet()->getTree());
}


void FenetrePrincipale::closeEvent(QCloseEvent *event)
{
    libererInstance();
    event->accept();

}

void FenetrePrincipale::goToPreviousWeek() {
    zoneCentrale->getFenetreEDT()->goToPreviousWeek();
}

void FenetrePrincipale::goToNextWeek() {
    zoneCentrale->getFenetreEDT()->goToNextWeek();
}

void FenetrePrincipale::updateEDT() {
    zoneCentrale->getFenetreEDT()->loadWeek();
}

void FenetrePrincipale::exporterUneSemaine(){
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier XML (*.xml)");
    if(!fichier.isEmpty()){
        zoneCentrale->getFenetreEDT()->saveWeek(fichier);
    }
}

void FenetrePrincipale::exporterUnProjet(){
    QTreeWidgetItem * actuel = zoneCentrale->getFenetreGestionProjet()->getTree()->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Exporter un projet", "Veuillez d'abord sélectionner un élément pour exporter un projet.");
    }
    else{
        try{
            cheminement = zoneCentrale->getFenetreGestionProjet()->getCheminement(actuel);
            const std::string& titreProjet = zoneCentrale->getFenetreGestionProjet()->getAndRemoveProjet(&cheminement).getTitre();
            QMessageBox::information(this, "Exporter un projet", "Votre export du projet " + QString::fromStdString(titreProjet) + " a bien été réalisé.");
        }
        catch (FenetreGestionProjetException& e){
            QMessageBox::warning(this, "Exporter un projet", e.what());
        }
    }
}

void FenetrePrincipale::enregistrerUnProjet(){
    QTreeWidgetItem * actuel = zoneCentrale->getFenetreGestionProjet()->getTree()->currentItem();
    QList<QString> cheminement;
    if(actuel == 0){
        QMessageBox::warning(this, "Enregistrer un projet", "Veuillez d'abord sélectionner un élément pour enregistrer un projet.");
    }
    else{
        try{
            cheminement = zoneCentrale->getFenetreGestionProjet()->getCheminement(actuel);
            const std::string& titreProjet = zoneCentrale->getFenetreGestionProjet()->getAndRemoveProjet(&cheminement).getTitre();
            QMessageBox::information(this, "Enregistrer un projet", "Votre enregistrement du projet " + QString::fromStdString(titreProjet) + " a bien été réalisé.");
        }
        catch (FenetreGestionProjetException& e){
            QMessageBox::warning(this, "Enregistrer un projet", e.what());
        }
    }
}

