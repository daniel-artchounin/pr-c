#ifndef TACHE_H
#define TACHE_H
#include "date.h"
#include "horaire.h"
#include "element.h"
#include <string>
#include <map>

/**\class Tache
 * \brief Classe permettant de manipuler des taches
 * Cette classe est abstraite
 */

class Tache : public Element {
    protected:
        typedef std::map<std::string, Tache*> Map2;
        Map2 tachesPrecedentes; /*!< map de taches */
        // ajouter un iterateur
    public:
        /**
         * \brief Constructeur
         * \param dateD date de disponiblité
         * \param heureD heure de disponiblité
         * \param dateEcheance date d'échéance
         * \param heureEcheance heure d'échéance
         * \param titre titre de la tache
         */
        Tache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
              const Horaire& heureEcheance,const std::string & titre);

        /**
         * \brief getTachesPrecedentes
         * accesseur
         * \return retourne un pointeur sur le premier élément d'un tableau
         * de pointeur vers les taches précédents la tache
         */

       // Tache** getTachesPrecedentes()const;

        /**
         * \brief getNbTachesPrecedentes
         * accesseur
         * \return retourne le nombre de taches précédentes
         */

        // size_type getNbTachesPrecedentes() const;

        /**
         * \brief getNbTachesPrecedentesMax
         * accesseur
         * \return retourne la taille du tableau dynamique tachesPrecedentes
         */
        // int getNbTachesPrecedentesMax() const;

        /**
         * \brief isTermine
         * méthode virutelle pure
         * \return retourne un booléen (en fonction de la terminaison de la tache)
         */

        virtual bool isTermine() const = 0;
        /**
         * \brief finTachesPrecedentes
         * \return retourne un booléen (en fonction de la terminaison des tâches précédentes)
         */

        bool finTachesPrecedentes() const;
        /**
         * \brief isTachePrecedente
         * permet de savoir si une tâche envoyée en paramètre précède la tâche courante
         * \param tachePotentPrecedente référence sur une potentielle tache précédente
         * \return retourne un booléen (en fonction du statut de la tache par rapport à la tâche actuelle)
         */

        bool isTachePrecedente(const Tache& tachePotentPrecedente) const;
        /**
         * \brief trouverTachePrecedente
         * permet de trouver la tâche précédente envoyée en paramètre
         * parmi les contraintes de precedence de la tâche actuelle
         * \param tachePotentPrecedente référence sur une tache potentiellement précédente
         * \return retourne un pointeur vers la tâche précédente si elle l'est vraiment
         * ou 0 sinon
         */
        Tache* trouverTachePrecedente(const Tache& tachePotentPrecedente) const;
        /**
         * \brief ajouterTachePrecedente
         * ajoute une tâche précédente à la tâche courante
         * \param tachePrecedente référence sur une tache à ajouter
         */
        void ajouterTachePrecedente(Tache & tachePrecedente);
        /**
         * \brief supprimerTachesPrecedente
         * supprime une contrainte de précedence
         * \param tachePrecedente référence sur une tache à supprimer
         */
        void supprimerTachesPrecedente(const Tache & tachePrecedente);

        typedef typename Map2::iterator iterator2;
        typedef typename Map2::const_iterator const_iterator2;
        /*!
         * \brief begin
         * \return iterator sur le début de la map
         */
        iterator2 tPBegin() { return tachesPrecedentes.begin(); }
        /*!
         * \brief end
         * \return iterator sur la fin de la map
         */
        iterator2 tPEnd() { return tachesPrecedentes.end(); }

        /*!
         * \brief begin
         * \return iterator sur le début de la map
         */
        const_iterator2 tPBegin() const{ return const_cast<Tache *>(this)->tPBegin(); }
        /*!
         * \brief end
         * \return iterator sur la fin de la map
         */
        const_iterator2 tPEnd() const{ return const_cast<Tache *>(this)->tPEnd(); }
};

#endif // TACHE_H
