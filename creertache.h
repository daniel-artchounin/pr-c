#ifndef CREERTACHE_H
#define CREERTACHE_H
# include "creerprojettache.h"
# include "projet.h"

class CreerTache : public CreerProjetTache
{
protected:
    virtual void closeEvent(QCloseEvent *event);
public:
    CreerTache(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);
    Projet& nomProjet;
    std::string * chemin;
    unsigned int* tailleChemin;
};

#endif // CREERTACHE_H
