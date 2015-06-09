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
    hBox1 = new QHBoxLayout;
    label = new QLabel();
    hBox1->addWidget(label);
    hBox2 = new QHBoxLayout;
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

