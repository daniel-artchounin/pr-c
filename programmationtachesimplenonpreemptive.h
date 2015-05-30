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
     * Constructeur
     * \param dateD date de programmation
     * \param heureD horaire de programmation
     * \param tacheSimpleNonP référence vers une TacheSimpleNonPreemptive
     */
    ProgrammationTacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, TacheSimpleNonPreemptive& tacheSimpleNonP);

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
     * \brief ~ProgrammationTacheSimpleNonPreemptive destructeur
     */
    virtual ~ProgrammationTacheSimpleNonPreemptive();

    void exportTo(QXmlStreamWriter& stream);
};

#endif // PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
