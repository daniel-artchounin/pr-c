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
        typedef std::map<std::string, Tache*> TPMap;
        TPMap tachesPrecedentes; /*!< map de taches */
        /**
         * \brief trouverTachePrecedente
         * permet de trouver la tâche précédente envoyée en paramètre
         * parmi les contraintes de precedence de la tâche actuelle
         * \param tachePotentPrecedente titre de la tache potentiellement précédente
         * \return retourne un pointeur vers la tâche précédente si elle l'est vraiment
         * ou 0 sinon
         */
        Tache* trouverTachePrecedente(const std::string& titre) const;
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
         * \brief isTachePrecedente
         * permet de savoir si une tâche envoyée en paramètre précède la tâche courante
         * \param tachePotentPrecedente titre d'une potentielle tache précédente
         * \return retourne un booléen (en fonction du statut de la tache par rapport à la tâche actuelle)
         */
        bool isTachePrecedente(const std::string& titre) const;

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

        typedef typename TPMap::iterator tp_iterator;
        typedef typename TPMap::const_iterator tp_const_iterator;

        /*!
         * \brief tPBegin
         * \return iterator sur le début de la map
         */
        tp_iterator tPBegin() { return tachesPrecedentes.begin(); }

        /*!
         * \brief tPEnd
         * \return iterator sur la fin de la map
         */
        tp_iterator tPEnd() { return tachesPrecedentes.end(); }

        /*!
         * \brief tPBegin
         * \return const_iterator sur le début de la map
         */
        tp_const_iterator tPBegin() const{ return const_cast<Tache *>(this)->tPBegin(); }
        /*!
         * \brief tPEnd
         * \return const_iterator sur la fin de la map
         */
        tp_const_iterator tPEnd() const{ return const_cast<Tache *>(this)->tPEnd(); }


        /*!
         * \brief checkProgrammationCoherente
         * permet de savoir si les tâches précédent ma tâche ont
         * toutes été programmés et si fin de la programmation est
         * antérieure à la programmation de ma tâche
         * \param dateProg date de programmation
         * \param horaireProg horaire de programmation
         * \param tacheActuelle pointeur sur la tâche actuelle dans la boucle récursive
         * (ne doit pas être utilisé par le client)
         * \return vrai si la programmation est correcte ou faux sinon
         */
        bool checkProgrammationCoherente(const Date& dateProg, const Horaire& horaireProg, const Tache* tacheActuelle=0)const;
};

#endif // TACHE_H
