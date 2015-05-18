#ifndef PROJET_H
#define PROJET_H

#include "tache.h"
#include "projetexception.h"
#include "tachecomposite.h"

class Projet : public Element
{
    Tache ** taches;
    unsigned int nbTaches;
    unsigned int nbTachesMax;
    // l'écheance du projet est une borne sup de l'ensemble des tâches du projet -> à prendre en compte
    // la date de dispo d'un projet est une borne int de l'ensemble des tâches du projet -> à prendre en compte
    void addItem(Tache* t);
public:
    Projet(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
          const Horaire& heureEcheance,const std::string & titre);
    Tache** getTaches()const;
    unsigned int getNbTaches()const;
    unsigned int getNbTachesMax()const;
    Tache* trouverTache(const std::string& nomTache);
    int trouverIndiceTache(const std::string& nomTache);
    Tache& ajouterTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                        const Horaire& heureEcheance,const std::string & titre,const Duree & dur, bool preemptive, bool composite);
    Tache& getTache(const std::string& titre);
    const Tache& getTache(const std::string& titre)const;
    void supprimerTache(const std::string& titre);
    ~Projet();

    // accederTache
    // verifierTaches
    // verifierContraintesRespectees
    // isPrecedence

};

#endif // PROJET_H
