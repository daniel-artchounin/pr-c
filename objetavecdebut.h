#ifndef OBJETAVECDEBUT_H
#define OBJETAVECDEBUT_H
#include "date.h"
#include "horaire.h"

/*! \class ObjetAvecDebut
   * \brief Classe abstraite possédant une date et un horaire de début
   */
class ObjetAvecDebut
{
protected:
    Date dateDebut; /*!< date de début */
    Horaire horaireDebut; /*!< horaire de début */
public:
    /*!
     * \brief Constructeur
     * \param d date de début
     * \param h horaire de début
     */
    ObjetAvecDebut(const Date& d, const Horaire& h):dateDebut(d),horaireDebut(h) {}
    /*!
     * \brief Desctructeur
     * Destructeur virtual pure.
     */
    virtual ~ObjetAvecDebut()=0;
    /*!
     * \brief getDateDebut
     * \return date de début
     */
    const Date& getDateDebut() const {
        return dateDebut;
    }
    /*!
     * \brief getHoraireDebut
     * \return horaire de début
     */
    const Horaire& getHoraireDebut() const {
        return horaireDebut;
    }
};

#endif // OBJETAVECDEBUT_H
