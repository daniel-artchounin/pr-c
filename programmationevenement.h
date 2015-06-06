#ifndef PROGRAMMATIONEVENEMENT_H
#define PROGRAMMATIONEVENEMENT_H
#include "programmation.h"
#include "evenement.h"

/*! \class ProgrammationEvenement
 * \brief Classe permettant de programmer un évènement. Hérite de la classe Programmation
 */
class ProgrammationEvenement : public Programmation {
protected:
    Duree duree; /*!< duree de la programmation */
    Evenement* evenement;
public:
    /*!
     * \brief ProgrammationEvenement
     * \param date date de début de la programmation
     * \param horaire horaire de début de la programmation
     * \param dur duree de l'evènement programmé
     */
    ProgrammationEvenement(const Date date, const Horaire horaire, const Duree dur):Programmation(date, horaire), duree(dur), evenement(0) {}

    Evenement& programmerReunion(const std::string nom, const std::string lieu, const std::string motif);

    Evenement& programmerRendezVous(const std::string nom, const std::string lieu, const std::string motif);

    /*!
     * \brief getDuree
     * \return duree de la programmation
     */
    virtual Duree getDuree() const;

    virtual std::string getNom() const;

    Evenement* getEvenement() {
        return evenement;
    }

    /*!
     * \brief ~ProgrammationEvenement destructeur
     */
    virtual ~ProgrammationEvenement();

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream);
    /*!
     * \brief loadFrom
     * Permet d'importer les données depuis un fichier XML via le streamreader
     * \param xml
     */
    void loadFrom(QXmlStreamReader &xml);
};

#endif // PROGRAMMATIONEVENEMENT_H
