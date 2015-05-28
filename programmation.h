#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include "date.h"
#include "horaire.h"
#include "duree.h"

/*! \class Programmation
   * \brief Classe permettant de programmer à une date et un horaire.
   */
class Programmation
{
protected:
    Date dateProg; /*!< date de programmation */
    Horaire horaireProg; /*!< horaire de programmation */
public:
    /*!
     * \brief Constructeur
     * \param date date de programmation
     * \param horaire horaire de programmation
     */
    Programmation(const Date& date, const Horaire& horaire):dateProg(date), horaireProg(horaire) {}
    /*!
     * \brief Destructeur
     * Desctructeur virtual
     */
    virtual ~Programmation(){

    }

    /*!
     * \brief getDateProgrammation
     * \return date de programmation
     */
    const Date& getDateProgrammation() {
        return dateProg;
    }
    /*!
     * \brief getHoraireProgrammation
     * \return horaire de programmation
     */
    const Horaire& getHoraireProgrammation() {
        return horaireProg;
    }
    /*!
     * \brief getDuree
     * Devra être défini par les classes héritant de Programmation
     * \return duree de la programmation
     */    
    virtual const Duree& getDuree()const=0;
    /*!
     * \brief getDateFin
     * \return date de fin de la programmation
     */
    const Date getDateFin() {
        return dateProg.addDuree(getDuree());
    }

    /*!
     * \brief getHoraireFin
     * \return horaire de fin de la programmation
     */
    const Horaire getHoraireFin() {
        return horaireProg.addDuree(getDuree());
    }
};

#endif // PROGRAMMATION_H
