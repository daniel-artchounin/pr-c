#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include "date.h"
#include "horaire.h"

/*! \class Element
   * \brief Classe possédant un titre ainsi que des dates et horaires de début et de fin.
   */
class Element {
protected:
    std::string titre; /*!< titre de l'élément */
    Date dateDebut; /*!< date de début */
    Horaire horaireDebut; /*!< horaire de début */
    Date dateFin; /*!< date de fin */
    Horaire horaireFin; /*!< horaire de fin */
public:
    /*!
     * \brief Constructeur
     * \param t titre
     * \param dateD date de début
     * \param horaireD horaire de début
     * \param dateF date de fin
     * \param horaireF horaire de fin
     */
    Element(const std::string t, const Date dateD, const Horaire horaireD, const Date dateF, const Horaire horaireF): titre(t), dateDebut(dateD), horaireDebut(horaireD), dateFin(dateF), horaireFin(horaireF) {}
    /*!
     * \brief Desctructeur
     * Destructeur virtual pure.
     */
    virtual ~Element()=0;
    /*!
     * \brief getTitre
     * \return titre de l'élément
     */
    const std::string& getTitre() const {
        return titre;
    }
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
    /*!
     * \brief getDateFin
     * \return date de fin
     */
    const Date& getDateFin() const {
        return dateFin;
    }
    /*!
     * \brief getHoraireFin
     * \return horaire de fin
     */
    const Horaire& getHoraireFin() const {
        return horaireFin;
    }
};

#endif // ELEMENT_H
