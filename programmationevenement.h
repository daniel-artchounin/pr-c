#ifndef PROGRAMMATIONEVENEMENT_H
#define PROGRAMMATIONEVENEMENT_H
#include "programmation.h"
#include "horaire.h"
#include "date.h"
#include "duree.h"

/*! \class ProgrammationEvenement
   * \brief Classe permettant de programmer un évènement. Hérite de la classe Programmation
   */
class ProgrammationEvenement : public Programmation
{
protected:
    Duree duree; /*!< duree de la programmation */
public:
    /*!
     * \brief ProgrammationEvenement
     * \param date date de début de la programmation
     * \param horaire horaire de début de la programmation
     * \param dur duree de l'evènement programmé
     */
    ProgrammationEvenement(const Date date, const Horaire horaire, const Duree dur):Programmation(date, horaire), duree(dur) {}
    /*!
     * \brief getDuree
     * \return duree de la programmation
     */
    const Duree& getDuree() {
        return duree;
    }
};

#endif // PROGRAMMATIONEVENEMENT_H