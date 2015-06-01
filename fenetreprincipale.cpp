#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent)
{
    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");
    barrreOutils = addToolBar("BarreOutils");
    zoneCentrale = new ZoneCentrale(this);
    setCentralWidget(zoneCentrale);
}
