#ifndef TACHE_H
#define TACHE_H
#include "date.h"
#include "horaire.h"
#include "element.h"
#include <string>

class Tache : public Element {
    private:
        Tache ** tachesPrecedentes;
        unsigned int nbTachesPrecedentes;
        unsigned int nbTachesPrecedentesMax;
        // ajouter un iterateur
    public:
        Tache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
              const Horaire& heureEcheance,const std::string & titre);
        Tache** getTachesPrecedentes()const;
        int getNbTachesPrecedentes() const;
        virtual bool isTermine() const =0;
        bool finTachesPrecedentes() const;
        bool isTachePrecedente(const Tache& tachePotentPrecedente) const;
        void ajouterTachePrecedente(Tache & tachePrecedente);
        void supprimerTachesPrecedente(const Tache & tachePrecedente);

};

#endif // TACHE_H
