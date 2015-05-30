#ifndef PROGRAMMATIONMANAGER_H
#define PROGRAMMATIONMANAGER_H
#include "programmation.h"
#include "tachesimplenonpreemptive.h"
#include "tachesimplepreemptive.h"
#include "manager.h"

/*! \class ProgrammationManager
 * \brief Classe permettant de manipuler des Programmations. Hérite de la classe Manager. Utilise le design pattern singleton
 */
class ProgrammationManager : public Manager<Programmation> {
private:
    //design pattern singleton
    static ProgrammationManager * instance; /*!< instance unique de ProgrammationManager */

    /*!
     * \brief Constructeur
     * Constructeur privé afin d'empêcher la duplication
     */
    ProgrammationManager(): Manager<Programmation>(){}

    /*!
     *\brief Destructeur
     * Destructeur privé
     */
    ~ProgrammationManager() {}

    /*!
     * \brief Contructeur par recopie
     * Constructeur par recopie privé
     * \param pm ProgrammationManager
     */
    ProgrammationManager(const ProgrammationManager& pm);

    /*!
     * \brief Operateur d'affectation
     * Opérateur d'affectation privé
     * \param pm ProgrammationManager
     */
    ProgrammationManager& operator=(const ProgrammationManager& pm);

    /*!
     * \brief inclus
     * permet de savoir si une programmation potentielle est compris entre deux bornes
     * \param dateProg date de programmation
     * \param horaireProg horaire de programmation
     * \param dateFin date de fin de la programmation
     * \param horaireFin horaire de fin de la programmation
     * \param date date à tester
     * \param horaire horaire à tester
     * \return true si newDate et newHoraire sont compris entre dateProg, horaireProg et dateFin, horaireFin, false sinon
     */
    bool inclus(const Date& dateProg, const Horaire& horaireProg, const Date& dateFin, const Horaire& horaireFin, const Date& date, const Horaire& horaire) const;

    /*!
     * \brief hasIntersection
     * \param dateProg date de programmation
     * \param horaireProg horaire de programmation
     * \param dateFin date de fin de la programmation
     * \param horaireFin horaire de fin de la programmation
     * \param newDate date de la programmation à ajouter
     * \param newHoraire horaire de la programmation à ajouter
     * \param newDuree duree de la programmation à ajouter
     * \return true si newDate et newHoraire sont compris entre dateProg, horaireProg et dateFin, horaireFin ou inversement, false sinon
     */
    bool hasIntersection(const Date& dateProg, const Horaire& horaireProg, const Date& dateFin, const Horaire& horaireFin, const Date& newDate, const Horaire& newHoraire, const Duree& newDuree) const;

    /*!
     * \brief isValid
     * \param date date de la programmation à ajouter
     * \param horaire horaire de la programmation à ajouter
     * \param duree duree de la programmation à ajouter
     * \return true si la nouvelle programmation n'a pas d'intersection avec celles existantes, false sinon
     */
    bool isValid(const Date& date, const Horaire& horaire, const Duree& duree);

    /*!
     * \brief getKeyFrom
     * \param date date de la programmation
     * \param horaire horaire de la programmation
     * \return clé de la forme aaaammjjhhmm
     */
    std::string getKeyFrom(const Date& date, const Horaire& horaire);

public:
    //design pattern singleton
    /*!
     * \brief getInstance
     * \return instance unique de ProgrammationManager
     */
    static ProgrammationManager& getInstance();

    /*!
     * \brief libererInstance
     * Détruit l'instance unique de ProgrammationManager
     */
    static void libererInstance();

    /*!
     * \brief addProgrammationEvenement
     * Génère une exception ProgrammationManagerException si la nouvelle programmation n'est pas valide
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \param duree duree de la programmation
     * \return Programmation ajoutée si elle est valide
     */
    Programmation& addProgrammationEvenement(const Date& dateProg, const Horaire& horaireProg, const Duree& duree);

    /*!
     * \brief addProgrammationTacheSimpleNonPreemptive
     * Génère une exception ProgrammationManagerException si la nouvelle programmation n'est pas valide
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \param tache référence vers une TacheSimpleNonPreemptive
     * \return Programmation ajoutée si elle est valide
     */
    Programmation& addProgrammationTacheSimpleNonPreemptive(const Date& dateProg, const Horaire& horaireProg, TacheSimpleNonPreemptive& tache);

    /*!
     * \brief addProgrammationTacheSimplePreemptive
     * Génère une exception ProgrammationManagerException si la nouvelle programmation n'est pas valide
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \param pourcentage pourcentage de la programmation que l'on souhaite programmer
     * \param tache référence vers une TacheSimplePreemptive
     * \return Programmation ajoutée si elle est valide
     */
    Programmation& addProgrammationTacheSimplePreemptive(const Date& dateProg, const Horaire& horaireProg, unsigned int pourcentage, TacheSimplePreemptive& tache);

    /*!
     * \brief getProgrammation
     * Génère une exception ProgrammationManagerException si la programmation n'existe pas
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \return programmation débutant à dateProg horaireProg
     */
    Programmation& getProgrammation(const Date& dateProg, const Horaire& horaireProg);

    /*!
     * \brief getProgrammation
     * Génère une exception ProgrammationManagerException si la programmation n'existe pas
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \return const programmation débutant à dateProg horaireProg
     */
    const Programmation& getProgrammation(const Date& dateProg, const Horaire& horaireProg) const;
};

#endif // PROGRAMMATIONMANAGER_H
