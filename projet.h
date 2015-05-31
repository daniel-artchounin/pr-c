#ifndef PROJET_H
#define PROJET_H
#include "manager.h"
#include "tache.h"
#include "tachecomposite.h"
#include "element.h"
# include "tachesimplepreemptive.h"
# include "tachesimplenonpreemptive.h"
# include "typeinfo"
# include "projetexception.h"

/*! \class Projet
 * \brief Classe permettant de manipuler des projets
 * elle est responsable du cycle de vie de ses tâches (tâches à la racine du projet)
 */
class Projet : public Manager<Tache>, public Element {
protected :
    /**
     * \brief trouverTache
     * permet de trouver une tâche à la racine du projet
     * \param nomTache nom de la tâche
     * \return retourne un pointeur vers la tâche trouvée ou 0
     * sinon
     */
    Tache* trouverTache(const std::string& nomTache)const;

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
    bool verifierContraintesRespectees(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD,
                                       const Horaire& heureD, const Date& dateF, const Horaire& heureF, const Duree& dur)const;

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
                        const Horaire& heureEcheance,const std::string & titre,bool preemptive,
                      bool composite,const Duree& dur = 0);
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

    /*!
     * \brief ajouterPrecedence
     * permet d'ajouter une contrainte de précénde entre deux tâches
     * soulève une exception si cet ajout n'est pas possible
     * \param nomsTachesComposites1 tableau de chaines de caractères contenant les titres
     * des taches composites (correspond au cheminement pour parvenir à la tache 1)
     * \param nbTaches1 taille du tableau nomsTachesComposites1
     * \param nomTache1 nom de la tâche 1 (celle qui doit précéder)
     * \param nomsTachesComposites2 tableau de chaines de caractères contenant les titres
     * des taches composites (correspond au cheminement pour parvenir à la tache 2)
     * \param nbTaches2 taille du tableau nomsTachesComposites2
     * \param nomTache2 nom de la tâche 2 (celle qui doit succéder)
     */
    void ajouterPrecedence(const std::string * nomsTachesComposites1, unsigned int nbTaches1,const std::string& nomTache1,
                           const std::string * nomsTachesComposites2, unsigned int nbTaches2,const std::string& nomTache2);

    /*!
     * \brief supprimerPrecedence
     * permet de supprimer une contrainte de précénde entre deux tâches
     * soulève une exception si cette suppression n'est pas possible
     * \param nomsTachesComposites1 tableau de chaines de caractères contenant les titres
     * des taches composites (correspond au cheminement pour parvenir à la tache 1)
     * \param nbTaches1 taille du tableau nomsTachesComposites1
     * \param nomTache1 nom de la tâche 1 (celle qui précéde)
     * \param nomsTachesComposites2 tableau de chaines de caractères contenant les titres
     * des taches composites (correspond au cheminement pour parvenir à la tache 2)
     * \param nbTaches2 taille du tableau nomsTachesComposites2
     * \param nomTache2 nom de la tâche 2 (celle qui succède)
     */
    void supprimerPrecedence(const std::string * nomsTachesComposites1, unsigned int nbTaches1,const std::string& nomTache1,
                             const std::string * nomsTachesComposites2, unsigned int nbTaches2,const std::string& nomTache2);

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
    Tache& accederTache(const std::string * nomsTachesComposites, unsigned int nbTaches,const std::string& nomTache,
                              unsigned int profondeur = 0, const TacheComposite* tacheCourante = 0)const;

    TacheSimplePreemptive& accederTacheSimplePreemptive(const std::string * nomsTachesComposites, unsigned int nbTaches,const std::string& nomTache)const{
        Tache& maTache = accederTache(nomsTachesComposites, nbTaches, nomTache);
        try{
            dynamic_cast <TacheSimplePreemptive&>(maTache);
        }
        catch(std::bad_cast e){
            throw ProjetException("La tache "+maTache.getTitre()+" n'est pas une tache simple préemptive");
        }
        return dynamic_cast <TacheSimplePreemptive&>(maTache);;

    }

    TacheSimpleNonPreemptive& accederTacheSimpleNonPreemptive(const std::string * nomsTachesComposites, unsigned int nbTaches,const std::string& nomTache)const{
        Tache& maTache = accederTache(nomsTachesComposites, nbTaches, nomTache);
        try{
            dynamic_cast <TacheSimpleNonPreemptive&>(maTache) ;
        }
        catch(std::bad_cast e){
            throw ProjetException("La tache "+maTache.getTitre()+" n'est pas une tache simple non préemptive");
        }
        return dynamic_cast <TacheSimpleNonPreemptive&>(maTache) ;
    }


    /*!
     * \brief creerAjouterTache
     * \param nomsTaches tableau de chaines de caractères contenant les titres
     * des taches composites (correspond au cheminement pour parvenir à la tache qui va probablement
     * etre créée)
     * \param nbTaches taille du tableau nomsTaches
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateF dateEcheance date d'échéance
     * \param heureF heure d'échéance
     * \param titre
     * \param preemptive
     * \param composite
     * \param dur
     */
    void creerAjouterTache(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD,
                           const Horaire& heureD, const Date& dateF, const Horaire& heureF,
                                   const std::string& titre, bool preemptive, bool composite, const Duree & dur=0);

    void exportTo(QXmlStreamWriter& stream);

    std::string genererChemin(const std::string * nomsTachesComposites1, unsigned int nbTaches1,const std::string& nomTache1);

    /*!
     *\brief Destructeur
     */
    ~Projet(){

    }
};

#endif // PROJET_H
