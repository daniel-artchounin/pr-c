#ifndef TACHE_H
#define TACHE_H
#include "date.h"
#include "horaire.h"
#include "element.h"
#include <string>
#include <map>
# include "tacheexception.h"
# include "duree.h"
# include <typeinfo>
/**\class Tache
 * \brief Classe permettant de manipuler des taches
 * Cette classe est abstraite
 */

class TacheComposite;
class TacheSimple;
class TacheSimpleNonPreemptive;
class TacheSimplePreemptive;
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
              const Horaire& heureEcheance,const std::string & titre,const Duree& dur=0);

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

        /**
         * \brief finTachesPrecedentes
         * \return retourne un booléen (en fonction de la terminaison des tâches précédentes)
         */

        /**
         * \brief isTachePrecedente
         * permet de savoir si une tâche envoyée en paramètre précède la tâche courante
         * \param tachePotentPrecedente titre d'une potentielle tache précédente
         * \return retourne un booléen (en fonction du statut de la tache par rapport à la tâche actuelle)
         */
        bool isTachePrecedente(const std::string& titre) const;
        /**
         * \brief trouverTachePrecedente
         * permet de trouver la tâche précédente envoyée en paramètre
         * parmi les contraintes de precedence de la tâche actuelle
         * \param tachePotentPrecedente titre de la tache potentiellement précédente
         * \return retourne un pointeur vers la tâche précédente si elle l'est vraiment
         * ou 0 sinon
         */
        Tache* trouverTachePrecedente(const std::string& titre) const;

        /**
         * \brief getTachePrecedente
         * permet de trouver une tâche précédente de la tâche courante
         * déclenche une exception si la tâche n'est pas trouvée
         * \param titre nom de la sous tâche
         * \return retourne une référence sur la tâche
         */
        Tache& getTachePrecedente(const std::string& titre){

            Tache* t=trouverTachePrecedente(titre);
            if (!t) {
                throw TacheException("erreur : tache inexistante");
            }
            return *t;
        }
        /**
         * \brief getTachePrecedente méthode const (elle sera utilisé par les références
         * const ou les pointeurs const)
         * permet de trouver une tâche précédente de la tâche courante
         * déclenche une exception si la tâche n'est pas trouvée
         * \param titre nom de la tâche
         * \return retourne une référence sur la tâche
         */
        const Tache& getTachePrecedente(const std::string& titre)const{
            return const_cast<Tache*>(this)->getTachePrecedente(titre);
        }
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
        void supprimerTachesPrecedente(const std::string& tachePrecedente);


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

        // getDateFin -> erreur dans l'UML
        // getHeureFin -> erreur dans l'UML
        // fonction permettant de savoir siles tâches précédentes sont toutes programmés
        // et que la programmation de la fin soit antérieure à ma programmation

        bool checkProgrammationCoherente(const Date& dateProg, const Horaire& horaireProg, const Tache* tacheActuelle=0)const;
};

#endif // TACHE_H
