#ifndef PROJET_H
#define PROJET_H

#include "projetexception.h"
#include <string>
# include "tache.h"
# include "manager.h"
# include "tachecomposite.h"

/**\class Projet
 * \brief Classe permettant de manipuler des projets
 * elle est responsable du cycle de vie de ses tâches (tâches à la racine du projet)
 */
class Projet : public Manager<Tache>, public Element
{

protected :
    /**
     * \brief trouverTache
     * permet de trouver une tâche à la racine du projet
     * \param nomTache nom de la tâche
     * \return retourne un pointeur vers la tâche trouvée ou 0
     * sinon
     */
    Tache* trouverTache(const std::string& nomTache)const;
public:
    /**
     * \brief Projet Constructeur
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     */
    Projet(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
          const Horaire& heureEcheance,const std::string & titre);
    /**
     * \brief getTaches accesseur
     * \return retourne un pointeur vers un tableau de pointeur
     * vers les tâches à la racine du projet
     */
    // Tache** getTaches()const;
    /**
     * \brief getNbTaches accesseur
     * \return retourne le nombre de tâches à la racine du projet
     */
    // unsigned int getNbTaches()const;
    /**
     * \brief getNbTachesMax accesseur
     * \return retourne la taille du tableau de pointeurs de tâches à la racine du projet
     */
    // unsigned int getNbTachesMax()const;

    /**
     * \brief ajouterTache
     * permet de créer et d'ajouter une tâche à la racine du projet
     * génère une exception si le titre de cette tâche est déjà une tâche
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     * \param preemptive booleen permettant de savoir
     *  si la tache à créer est preemptive
     * \param composite booleen permettant de savoir
     * si la tache à créer est composite
     * \param dur duree de la tache
     * \return retourne une référence sur la tâche créée
     */
    void ajouterTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                        const Horaire& heureEcheance,const std::string & titre,bool preemptive, bool composite,const Duree & dur = 0);
    /**
     * \brief getTache
     * permet de trouver une tâche du projet actuel
     * déclenche une exception si la tache n'est pas trouvée
     * \param titre nom de la tâche
     * \return retourne une référence sur la tâche
     */
    Tache& getTache(const std::string& titre);
    /**
     * \brief getTache méthode const (elle sera utilisé par les références
     * const ou les pointeurs const)
     * permet de trouver une tâche du projet actuel
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la tâche
     * \return retourne une référence sur la tâche
     */
    const Tache& getTache(const std::string& titre)const;
    /**
     * \brief supprimerTache
     * supprime la tâche dont le titre est renseigné en paramètre
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la sous tâche
     */
    void supprimerTache(const std::string& titre);
    /**
     * \brief isPrecedence
     * permet de vérifier si une tache est bien précédente d'une autre
     * \param tachePrecedente référence sur la tache potentiellement précédente
     * \param tacheSuivante référence sur la tache potentiellement suivante
     * \return retourne un booléen
     */
    bool isPrecedence( const Tache & tachePrecedente, const Tache& tacheSuivante)const{
        return const_cast<Tache &>(tacheSuivante).isTachePrecedente(tachePrecedente.getTitre());
    }
    /**
     * \brief accederTache
     * permet d'accéder à une tache
     * déclenche une exception si la tentative d'accès n'abouti pas
     * \param nomsTachesComposites tableau de chaines de caractères contenant les titres
     * des taches composites (correspond au cheminement pour parvenir à la tache)
     * \param nbTaches taille du tableau nomsTachesComposites
     * \param nomTache titre de la tache auquel on souhaite accéder
     * \param profondeur à laquelle on se trouve dans la récursion (correspond à
     * l'indice dans le tableau nomsTachesComposites) -> à ne pas compléter à l'appel de la
     * méthode
     * \param tacheCourante correspond à la tache courante à laquelle on s'intéresse dans la
     * boucle récursif -> à ne pas compléter à l'appel de la
     * méthode
     * \return retourne une référence vers la tache à laquelle on souhaitait accéder
     */
    const Tache& accederTache(const std::string * nomsTachesComposites, unsigned int nbTaches,const std::string& nomTache,
                              unsigned int profondeur = 0, const TacheComposite* tacheCourante = 0);
    /**
     * \brief verifierContraintesRespectees
     * permet de vérifier si la date de début, l'heure de début, la date de fin et l'heure de fin
     * de la tache qui peut etre ultérieurement créée sont cohérentes avec ses potentielles taches composites
     * mères et son potentiel projet père
     * \param nomsTaches tableau de chaines de caractères contenant les titres
     * des taches composites (correspond au cheminement pour parvenir à la tache qui va probablement
     * etre créée)
     * \param nbTaches taille du tableau nomsTaches
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateF dateEcheance date d'échéance
     * \param heureF heure d'échéance
     * \return retourne un booleen permettant de savoir si les contraintes sont respectées
     */
    bool verifierContraintesRespectees(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD
                                       ,const Horaire& heureD,const Date& dateF, const Horaire& heureF, const Duree & dur)const;

    // verifierTachesPrecedentesTerminees -> à voir mercredi matin
    void creerAjouterTache(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD
                                       ,const Horaire& heureD,const Date& dateF, const Horaire& heureF,
                                   const std::string& titre, bool preemptive, bool composite,const Duree & dur=0);

};

#endif // PROJET_H
