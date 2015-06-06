#include "programmertachesimple.h"

ProgrammerTacheSimple::ProgrammerTacheSimple(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent):
    FenetreAnnulerValider(parent), nomProjet(projet)
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
    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxAnnulerValider);
}

void ProgrammerTacheSimple::closeEvent(QCloseEvent *event){
    if(chemin!=0){
        delete[] chemin;
        chemin = 0;
    }
    if(tailleChemin!=0){
        delete tailleChemin;
        tailleChemin = 0;
    }
    FenetreAnnulerValider::closeEvent(event);
}
