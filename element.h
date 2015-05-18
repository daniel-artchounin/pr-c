#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include "objetavecdebut.h"
#include "date.h"
#include "horaire.h"

/*! \class Element
   * \brief Classe possédant une date et un horaire de fin ainsi qu'un titre
   * Hérite de la classe ObjetAvecDebut afin de gérer une date et horaire de début.
   */
class Element : public ObjetAvecDebut
{
protected:
    std::string titre; /*!< titre de l'élément */
    Date dateFin; /*!< date de fin de l'élément */
    Horaire horaireFin; /*!< horaire de fin de l'élément */
public:
    /*!
     * \brief Constructeur
     * \param dd date de début
     * \param hd horaire de début
     * \param t titre
     * \param df date de fin
     * \param hf horaire de fin
     */
    Element(const Date& dd, const Horaire& hd, const std::string& t, const Date& df, const Horaire& hf):ObjetAvecDebut(dd, hd), titre(t), dateFin(df), horaireFin(hf) {}
    /*!
     * \brief getTitre
     * \return titre de l'élément
     */
    const std::string& getTitre() const {
        return titre;
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
