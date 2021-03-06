#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
#include "manager.h"
#include "tache.h"

/*! \class TacheComposite
 * \brief Classe permettant de manipuler des tâches composites
 * elle est responsable du cycle de vie de ses sous-tâches
 */
class TacheComposite : public Manager <Tache>, public Tache
{
    friend class Projet;

protected :

    /*!
     * \brief ajouterSsTache
     * Permet de créer et d'ajouter une sous-tâche à la tache actuelle.
     * Génère une exception si le titre de cette tâche est déjà une sous tâche.
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     * \param preemptive booléen permettant de savoir si la tâche est préemptive
     * \param composite booléen permettant de savoir si la tâche est composite
     * \param dur durée de la tâche
     */
    void ajouterSsTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                        const Horaire& heureEcheance,const std::string & titre,
                        bool preemptive, bool composite, const Duree& dur=0);
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
     * \brief trouverSsTache
     * Permet de trouver une sous tâche de la tâche courante.
     * \param nomTache nom de la sous tâche
     * \return retourne un pointeur vers la tâche trouvée ou 0
     * sinon
     */
    Tache* trouverSsTache(const std::string& nomTache)const;

    /**
     * \brief getSsTache
     * Permet de trouver une sous tâche de la tâche courante.
     * Déclenche une exception si la tâche n'est pas trouvée.
     * \param titre nom de la sous tâche
     * \return retourne une référence sur la tâche
     */
    Tache& getSsTache(const std::string& titre);

    /**
     * \brief getSsTache méthode const (elle sera utilisé par les références const ou les pointeurs const)
     * Permet de trouver une sous tâche de la tâche courante.
     * Déclenche une exception si la tâche n'est pas trouvée.
     * \param titre nom de la sous tâche
     * \return retourne une référence sur la tâche
     */
    const Tache& getSsTache(const std::string& titre)const;

    /**
     * \brief supprimerSsTache
     * Supprime la tâche dont le titre est renseigné en paramètre.
     * Déclenche une exception si la tâche n'est pas trouvée.
     * \param titre nom de la sous tâche
     */
    void supprimerSsTache(const std::string& titre);

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter.
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream);

    /*!
     * \brief exportProgrammations
     * Permet d'exporter les programmations des sous taches.
     * \param stream
     */
    void exportProgrammations(QXmlStreamWriter& stream);

    /*!
     * \brief
     * Destructeur.
     */
    ~TacheComposite() {

    }
};

#endif // TACHECOMPOSITE_H
