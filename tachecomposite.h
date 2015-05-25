#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
# include "tache.h"
# include "tachecompositeexception.h"
# include "tachesimplenonpreemptive.h"
# include "tachesimplepreemptive.h"
# include "manager.h"
# include <string>
# include "tachecompositeexception.h"

/**\class TacheComposite
 * \brief Classe permettant de manipuler des tâches composites
 * elle est responsable du cycle de vie de ses sous-tâches
 */

class TacheComposite : public Manager <Tache>, public Tache
{
public:
    /**
     * \brief TacheComposite Constructeur
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     */
    TacheComposite(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
          const Horaire& heureEcheance,const std::string & titre);
    /**
     * \brief getSsTaches accesseur
     * \return retourne un pointeur vers un tableau de pointeur
     * vers les sous tâches de la tâche actuelle
     */
    // Tache** getSsTaches() const;
    /**
     * \brief getnbSsTaches accesseur
     * \return retourne le nombre de sous tâche de la tâche courante
     */
    // int getnbSsTaches();
    /**
     * \brief getnbSsTachesMax accesseur
     * \return retourne la taille du tableau de pointeurs ssTaches
     */
    // int getnbSsTachesMax();
    /**
     * \brief trouverSsTache
     * permet de trouver une sous tâche de la tâche courante
     * \param nomTache nom de la sous tâche
     * \return retourne un pointeur vers la tâche trouvée ou 0
     * sinon
     */
    Tache* trouverSsTache(const std::string& nomTache)const;
    /**
     * \brief trouverIndiceSsTache
     * permet de trouver l'indice d'une sous tâche de la tâche courante
     * dans le tableau de pointeurs ssTaches
     * \param nomTache nom de la sous tâche
     * \return retourne l'indice de la sous-tâche ou
     * 0 sinon
     */
    int trouverIndiceSsTache(const std::string& nomTache)const;
    /**
     * \brief ajouterSsTache
     * permet de créer et d'ajouter une sous-tâche à la tache actuelle
     * génère une exception si le titre de cette tâche est déjà une sous tâche
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     * \return retourne une référence sur la tâche créée
     */
    Tache& ajouterSsTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                        const Horaire& heureEcheance,const std::string & titre,const Duree & dur, bool preemptive);
    /**
     * \brief getSsTache
     * permet de trouver une sous tâche de la tâche courante
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la sous tâche
     * \return retourne une référence sur la tâche
     */
    Tache& getSsTache(const std::string& titre);
    /**
     * \brief getSsTache méthode const (elle sera utilisé par les références
     * const ou les pointeurs const)
     * permet de trouver une sous tâche de la tâche courante
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la sous tâche
     * \return retourne une référence sur la tâche
     */
    const Tache& getSsTache(const std::string& titre)const;
    /**
     * \brief supprimerSsTache
     * supprime la tâche dont le titre est renseigné en paramètre
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la sous tâche
     */
    void supprimerSsTache(const std::string& titre);
    /**
     * \brief isTermine
     * \return retourne true si la toutes les sous tâches sont terminées ou
     * false sinon
     */
    bool isTermine()const;

};

#endif // TACHECOMPOSITE_H
