#ifndef PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
#define PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
#include "programmationtachesimple.h"

class TacheSimpleNonPreemptive;

/*! \class ProgrammationTacheSimpleNonPreemptive
 * \brief Permet de gérer la programmation des tâches simples non préemptives
 */
class ProgrammationTacheSimpleNonPreemptive : public ProgrammationTacheSimple
{
protected :
    TacheSimpleNonPreemptive* tacheSimpleNonPreemptive; /*!< pointeur vers la tache simple non préemptive que l'on programme */

public:
    /*!
     * \brief ProgrammationTacheSimpleNonPreemptive
     *
     * Constructeur
     *
     * \param dateD date de programmation
     * \param heureD horaire de programmation
     * \param tacheSimpleNonP référence vers une TacheSimpleNonPreemptive
     */
    ProgrammationTacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, TacheSimpleNonPreemptive& tacheSimpleNonP);

    /*!
     * \brief updateProgrammationTacheSimpleNonPreemptive
     *
     * Met à jour la programmation actuelle avec la date, l'horaire et la durée donnés
     *
     * \param dateD
     * \param heureD
     */
    void updateProgrammationTacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD) {
        dateProg=dateD;
        horaireProg=heureD;
    }

    /*!
     * \brief getTacheSimple accesseur
     * \return référence vers la tâche simple non préemptive que l'on programme
     */
    virtual const TacheSimpleNonPreemptive& getTacheSimple() const;

    /*!
     * \brief getDuree accesseur
     * \return duree de la programmation
     */
    virtual Duree getDuree()const;

    /*!
     * \brief getNom
     * \return nom de l'évènement
     */
    virtual std::string getNom() const;

    /*!
     * \brief ~ProgrammationTacheSimpleNonPreemptive destructeur
     */
    virtual ~ProgrammationTacheSimpleNonPreemptive();

    /*!
     * \brief exportTo
     *
     * Permet d'exporter les données dans un fichier XML via le streamwriter
     *
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream);
};

#endif // PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
