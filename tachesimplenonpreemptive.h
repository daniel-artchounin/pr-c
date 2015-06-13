#ifndef TACHESIMPLENONPREEMPTIVE_H
#define TACHESIMPLENONPREEMPTIVE_H
#include "tachesimple.h"
# include <programmationmanager.h>

class ProgrammationTacheSimpleNonPreemptive;

/*! \class TacheSimpleNonPreemptive
 * \brief Classe permettant de manipuler des tâches non préemptives
 */
class TacheSimpleNonPreemptive : public TacheSimple
{
    friend class ProgrammationTacheSimpleNonPreemptive;

protected :

    ProgrammationTacheSimpleNonPreemptive* programmationTacheSimpleNonPreemptive; /*!< pointeur vers la programmation de la tâche simple non préemptive */

    /**
     * \brief dureeValide
     * \param duree duree d'une tache
     * \return true si la duree est valide (si elle est inférieure à 12 h 00) ou non sinon
     */
    bool dureeValide(const Duree& duree)const;

    /*!
     * \brief hasProgrammation
     * \return vrai si la taĉhe a au moins une programmtion ou faux sinon
     */
    virtual bool hasProgrammation()const;

    /*!
     * \brief setProgrammation mutateur
     * \param programmationTacheSimpleNonP pointeur vers la programmation de la tâche
     */
    void setProgrammation(ProgrammationTacheSimpleNonPreemptive* programmationTacheSimpleNonP);

    /*!
     * \brief eraseProgrammation
     * Permet de mettre le pointeur vers la programmation de tâche simple non préemptive (déjà supprimée) à 0.
     */
    void eraseProgrammation();
public:
    /*!
     * \brief TacheSimpleNonPreemptive
     * Constructeur.
     * Peut générer une exception.
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     * \param dur durée de la tache
     */
    TacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                             const Horaire& heureEcheance,const std::string & titre,const Duree & dur);

    /*!
     * \brief isEndProgrammationOk permet de vérifier que
     * la tâche a été programmée intégralement et que la fin de la programmation
     * précéde celle transmise en paramètre.
     * \param dateProg date de début de la programmation
     * \param horaireProg horaire de début de la programmation
     * \return vrai si la tâche a été programmé intégralement et que la fin de la programmation
     * précédè celle transmise en paramètre ou faux sinon
     */
    virtual bool isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const;

    /*!
     * \brief getProgrammation accesseur
     * \return la programmation associée à la tâche ou 0 sinon
     */
    ProgrammationTacheSimpleNonPreemptive* getProgrammation() const;

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter.
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream);

    /*!
     * \brief exportProgrammations
     * Permet d'exporter les programmations de la tache preemptive.
     * \param stream
     */
    void exportProgrammations(QXmlStreamWriter& stream);

    /*!
     * \brief ~TacheSimpleNonPreemptive
     * Destructeur
     */
    virtual ~TacheSimpleNonPreemptive();
};

#endif // TACHESIMPLENONPREEMPTIVE_H
