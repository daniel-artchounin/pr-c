#ifndef PROGRAMMATIONTACHESIMPLE_H
#define PROGRAMMATIONTACHESIMPLE_H
#include "programmation.h"
#include "date.h"
#include "horaire.h"

/*! \class ProgrammationTacheSimple
 * \brief Classe permettant de manipuler de gérer des programmations de TacheSimple. Hérite de la classe Programmation.
 */
class ProgrammationTacheSimple : public Programmation{
public:
    /*!
     * \brief ProgrammationTacheSimple constructeur
     * \param dateDebut date de début de le programmation
     * \param horaireDebut horaire de début de la programmation
     */
    ProgrammationTacheSimple(const Date&  dateDebut, const Horaire& horaireDebut):Programmation(dateDebut, horaireDebut){}



    /*!
     * \brief getTacheSimple accesseur vers la tâche simple que l'on programme
     * méthode virtuelle pure
     * \return une tâche simple
     */
    // virtual const TacheSimple& getTacheSimple() const=0;

    /*!
     * \brief ~ProgrammationTacheSimple destructeur
     */
    virtual ~ProgrammationTacheSimple();
};

#endif // PROGRAMMATIONTACHESIMPLE_H




