#include "programmertachesimplepreemptive.h"
#include "fenetreprincipale.h"
# include <QCloseEvent>

ProgrammerTacheSimplePreemptive::ProgrammerTacheSimplePreemptive(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent):
    QWidget(parent), nomProjet(projet)
{
    titreTache = titreT;
    std::cout << "titre byzarre" << std::endl ;
    std::cout << titreTache << std::endl ;
    chemin = chaine;
    tailleChemin = taille;
    dateProgrammation = new QDateEdit;
    horaireProgrammation = new QTimeEdit();
    pourcentage = new QSpinBox;
    formlayout = new QFormLayout;
    formlayout->addRow("Date de début de programmation",dateProgrammation);
    formlayout->addRow("Horaire de début de programmation",horaireProgrammation);
    formlayout->addRow("Pourcentage de programmation",pourcentage);
    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauver");
    hBox = new QHBoxLayout;
    hBox->addWidget(annuler);
    hBox->addWidget(sauver);
    vBox = new QVBoxLayout(this);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBox);
    connect(annuler,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleAnnuler()));
    connect(sauver,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleSauver()));
}

void ProgrammerTacheSimplePreemptive::retourFenetrePrincipaleAnnuler(){
    this->close();
}

void ProgrammerTacheSimplePreemptive::retourFenetrePrincipaleSauver(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    std::cout << "titre de tâche depuis interface : " << titreTache << std::endl;
    try{
        TacheSimplePreemptive& myTacheSimplePreemptive = nomProjet.accederTacheSimplePreemptive(
                    chemin,
                    *tailleChemin,
                    titreTache
                    );
        programmationManager.addProgrammationTacheSimplePreemptive(
                    Date(dateProgrammation->date().day(), dateProgrammation->date().month(), dateProgrammation->date().year()),
                    Horaire(horaireProgrammation->time().hour(), horaireProgrammation->time().minute()),
                    pourcentage->value(),
                    myTacheSimplePreemptive
                    );
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Création de tâche tâche simple préemptive", e.what());
    }
    this->close();
}

void ProgrammerTacheSimplePreemptive::closeEvent(QCloseEvent *event){
    if(chemin!=0){
        delete[] chemin;
        chemin = 0;
    }
    if(tailleChemin!=0){
        delete tailleChemin;
        tailleChemin = 0;
    }
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.show();
    event->accept();
}

