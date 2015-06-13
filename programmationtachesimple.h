#ifndef PROGRAMMATIONTACHESIMPLE_H
#define PROGRAMMATIONTACHESIMPLE_H
#include "programmation.h"
#include "date.h"
#include "horaire.h"
# include "tachesimple.h"

/*! \class ProgrammationTacheSimple
 * \brief Classe permettant de manipuler de gérer des programmations de TacheSimple. Hérite de la classe Programmation.
 */
class ProgrammationTacheSimple : public Programmation{

public:

    /*!
     * \brief ProgrammationTacheSimple
     * Constructeur.
     * \param dateDebut date de début de le programmation
     * \param horaireDebut horaire de début de la programmation
     */
    ProgrammationTacheSimple(const Date&  dateDebut, const Horaire& horaireDebut):Programmation(dateDebut, horaireDebut){}

    /*!
     * \brief getTacheSimple
     * Accesseur vers la tâche simple que l'on programme
     * Méthode virtuelle pure.
     * \return une tâche simple
     */
    virtual TacheSimple& getTacheSimple() const=0;

    /*!
     * \brief ~ProgrammationTacheSimple
     * Destructeur
     */
    virtual ~ProgrammationTacheSimple();
};

#endif // PROGRAMMATIONTACHESIMPLE_H




