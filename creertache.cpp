#include "creertache.h"

CreerTache::CreerTache(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent) :
    CreerProjetTache(parent), nomProjet(projet)
{
    chemin = chaine;
    tailleChemin = taille;
}

void CreerTache::closeEvent(QCloseEvent *event)
{
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
