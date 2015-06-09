#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include "date.h"
#include "horaire.h"
#include <QXmlStreamWriter>

/*! \class Programmation
 * \brief Classe permettant de programmer à une date et un horaire.
 */
class Programmation {
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
     * Desctructeur abstrait
     */
    virtual ~Programmation();

    /*!
     * \brief getDateProgrammation
     * \return date de programmation
     */
    Date getDateProgrammation()const{
        return dateProg;
    }

    /*!
     * \brief getHoraireProgrammation
     * \return horaire de programmation
     */
    Horaire getHoraireProgrammation()const{
        return horaireProg;
    }

    /*!
     * \brief getDuree
     * Devra être défini par les classes héritant de Programmation
     * \return duree de la programmation
     */
    virtual Duree getDuree()const=0;

    /*!
     * \brief getDateFin
     * \return date de fin de la programmation
     */
    Date getDateFin()const{
        return dateProg.addDuree(getDuree(), horaireProg);
    }

    /*!
     * \brief getHoraireFin
     * \return horaire de fin de la programmation
     */
    Horaire getHoraireFin()const{
        return horaireProg.addDuree(getDuree());
    }

    /*!
     * \brief getNom
     * Permet de récupérer le nom de l'évènement
     */
    virtual std::string getNom() const=0;

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter
     * \param stream
     */
    virtual void exportTo(QXmlStreamWriter& stream);
};

#endif // PROGRAMMATION_H
