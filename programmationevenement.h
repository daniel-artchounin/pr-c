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

    /*!
     * \brief programmerReunion
     * Permet de créer une réunion avec un nom, un lieu et un motif.
     * La réunion sera programmé à la programmation actuelle.
     * Si un évènement avait déjà été programmé, alors une exception sera soulevée.
     * \param nom
     * \param lieu
     * \param motif
     * \return evenement qui a été programmé
     */
    Evenement& programmerReunion(const std::string nom, const std::string lieu, const std::string motif);

    /*!
     * \brief programmerRendezVous
     * Permet de créer une réunion avec un nom, un lieu et un motif.
     * La réunion sera programmé à la programmation actuelle.
     * Si un évènement avait déjà été programmé alors déclenchera une exception.
     * \param nom
     * \param lieu
     * \param motif
     * \return evenement qui a été programmé
     */
    Evenement& programmerRendezVous(const std::string nom, const std::string lieu, const std::string motif);

    /*!
     * \brief updateProgrammationEvenement
     * Met à jour la programmation actuelle avec la date, l'horaire et la durée donnés
     * \param date
     * \param horaire
     * \param dur
     */
    virtual void updateProgrammationEvenement(const Date date, const Horaire horaire, const Duree dur){
        dateProg=date;
        horaireProg=horaire;
        duree=dur;
    }

    /*!
     * \brief getDuree
     * \return duree de la programmation
     */
    virtual Duree getDuree() const;

    /*!
     * \brief getNom
     * \return nom de l'évènement
     */
    virtual std::string getNom() const;

    /*!
     * \brief getEvenement
     * \return evenement programmé
     */
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
