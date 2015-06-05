#include "programmertachesimplenonpreemptive.h"
#include "fenetreprincipale.h"

ProgrammerTacheSimpleNonPreemptive::ProgrammerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent):
    QWidget(parent), nomProjet(projet)
{
    titreTache = titreT;
    std::cout << "titre byzarre" << std::endl ;
    std::cout << titreTache << std::endl ;
    chemin = chaine;
    tailleChemin = taille;
    dateProgrammation = new QDateEdit;
    horaireProgrammation = new QTimeEdit();
    formlayout = new QFormLayout;
    formlayout->addRow("Date de début de programmation",dateProgrammation);
    formlayout->addRow("Horaire de début de programmation",horaireProgrammation);
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

void ProgrammerTacheSimpleNonPreemptive::retourFenetrePrincipaleAnnuler(){
    this->close();
}

void ProgrammerTacheSimpleNonPreemptive::retourFenetrePrincipaleSauver(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    try{
        std::cout << "description : " << nomProjet.getTitre() << std::endl;
        std::cout << "description : " << *tailleChemin << std::endl;
        for(unsigned int i =0; i < *tailleChemin; i++){
            std::cout << "TC" << chemin[i]<<std::endl;
        }
        std::cout << "titreTache depuis fenetre sauver :" << std::endl ;
        std::cout << titreTache << std::endl ;

        TacheSimpleNonPreemptive& myTacheSimpleNonPreemptive = nomProjet.accederTacheSimpleNonPreemptive(
                    chemin,
                    *tailleChemin,
                    titreTache
                    );
        programmationManager.addProgrammationTacheSimpleNonPreemptive(
                    Date(dateProgrammation->date().day(), dateProgrammation->date().month(), dateProgrammation->date().year()),
                    Horaire(horaireProgrammation->time().hour(), horaireProgrammation->time().minute()),
                    myTacheSimpleNonPreemptive
                    );
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Création de tâche tâche simple non préemptive", e.what());
    }
    this->close();
}

void ProgrammerTacheSimpleNonPreemptive::closeEvent(QCloseEvent *event)
{
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
