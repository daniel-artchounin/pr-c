#ifndef PROGRAMMATIONTACHESIMPLEPREEMPTIVE_H
#define PROGRAMMATIONTACHESIMPLEPREEMPTIVE_H
#include "programmationtachesimple.h"
#include "tachesimplepreemptive.h"

class TacheSimplePreemptive;

class ProgrammationTacheSimplePreemptive : public ProgrammationTacheSimple {
protected :
    unsigned int pourcentage; /*!< pourcentage de la durée que l'on va programmer */
    TacheSimplePreemptive* tacheSimplePreemtive; /*!< pointeur vers la tache simple préemptive que l'on programme */

public:
    /*!
     * \brief ProgrammationTacheSimplePreemptive constructeur
     * \param dateD date de programmation
     * \param heureD horaire de programmation
     * \param pourc pourcentage de la durée que l'on va programmer
     * \param tacheSimpleP référence vers la tache simple préemptive que l'on programme
     */
    ProgrammationTacheSimplePreemptive(const Date& dateD, const Horaire& heureD, unsigned int pourc, TacheSimplePreemptive& tacheSimpleP);

    void updateProgrammationTacheSimplePreemptive(const Date& dateD, const Horaire& heureD, unsigned int pourc) {
        dateProg=dateD;
        horaireProg=heureD;
        //on retire l'ancienne valeur de pourcentage
        tacheSimplePreemtive->addPourcentageDejaProgramme(-pourcentage);
        //puis on ajoute la nouvelle valeur
        pourcentage=pourc;
        tacheSimplePreemtive->addPourcentageDejaProgramme(pourcentage);
    }

    /*!
     * \brief getTacheSimple accesseur
     * \return référence vers la tâche simple préemptive que l'on programme
     */
    virtual const TacheSimplePreemptive & getTacheSimple() const;

    /*!
     * \brief getDuree accesseur
     * \return duree de la programmation
     */
    virtual Duree getDuree()const;

    virtual std::string getNom() const;

    /*!
     * \brief ~ProgrammationTacheSimplePreemptive destructeur
     */
    virtual ~ProgrammationTacheSimplePreemptive();

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream);

    unsigned int getPourcentage()const{
        return pourcentage;
    }
};
#endif // PROGRAMMATIONTACHESIMPLEPREEMPTIVE_H



