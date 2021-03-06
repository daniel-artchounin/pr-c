#ifndef PROGRAMMATIONMANAGER_H
#define PROGRAMMATIONMANAGER_H
#include "manager.h"
#include "programmation.h"
#include "tachesimplenonpreemptive.h"
#include "tachesimplepreemptive.h"
# include "programmationevenement.h"

/*! \class ProgrammationManager
 * \brief Classe permettant de manipuler des Programmations. Hérite de la classe Manager. Utilise le design pattern singleton
 */

class ProgrammationTacheSimplePreemptive;
class ProgrammationTacheSimpleNonPreemptive;

class ProgrammationManager : public Manager<Programmation> {
private:
    //design pattern singleton
    static ProgrammationManager * instance; /*!< instance unique de ProgrammationManager */

    /*!
     * \brief Constructeur
     * Constructeur privé afin d'empêcher la duplication.
     */
    ProgrammationManager(): Manager<Programmation>(){}

    /*!
     *\brief Destructeur
     * Destructeur privé.
     */
    ~ProgrammationManager() {}

    /*!
     * \brief Contructeur par recopie
     * Constructeur par recopie privé.
     * \param pm ProgrammationManager
     */
    ProgrammationManager(const ProgrammationManager& pm);

    /*!
     * \brief Operateur d'affectation
     * Opérateur d'affectation privé.
     * \param pm ProgrammationManager
     */
    ProgrammationManager& operator=(const ProgrammationManager& pm);

    /*!
     * \brief inclus
     * Permet de savoir si une programmation potentielle est compris entre deux bornes.
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
    bool isValid(const Date& date, const Horaire& horaire, const Duree& duree, Programmation* old=0);

public:

    /*!
     * \brief getInstance
     * Design Pattern Singleton.
     * \return instance unique de ProgrammationManager
     */
    static ProgrammationManager& getInstance();

    /*!
     * \brief libererInstance
     * Design Pattern Singleton.
     * Détruit l'instance unique de ProgrammationManager.
     */
    static void libererInstance();

    /*!
     * \brief addProgrammationEvenement
     * Génère une exception ProgrammationManagerException si la nouvelle programmation n'est pas valide.
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \param duree duree de la programmation
     * \return Programmation ajoutée si elle est valide
     */
    ProgrammationEvenement& addProgrammationEvenement(const Date& dateProg, const Horaire& horaireProg, const Duree& duree);

    /*!
     * \brief updateProgrammationEvenement
     * Met à jour une programmation de type ProgrammationEvenement.
     * \param programmation
     * \param newDate
     * \param newHoraire
     * \param newDuree
     */
    void updateProgrammationEvenement(ProgrammationEvenement *programmation, const Date& newDate, const Horaire& newHoraire, const Duree& newDuree);

    /*!
     * \brief addProgrammationTacheSimpleNonPreemptive
     * Génère une exception ProgrammationManagerException si la nouvelle programmation n'est pas valide.
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \param tache référence vers une TacheSimpleNonPreemptive
     * \return Programmation ajoutée si elle est valide
     */
    ProgrammationTacheSimpleNonPreemptive& addProgrammationTacheSimpleNonPreemptive(const Date& dateProg, const Horaire& horaireProg, TacheSimpleNonPreemptive& tache);

    /*!
     * \brief updateProgrammationTacheSimpleNonPreemptive
     * Met à jour une programmation de type ProgrammationTacheSimpleNonPreemptive.
     * \param programmation
     * \param newDate
     * \param newHoraire
     */
    void updateProgrammationTacheSimpleNonPreemptive(ProgrammationTacheSimpleNonPreemptive& programmation, const Date& newDate, const Horaire& newHoraire);

    /*!
     * \brief addProgrammationTacheSimplePreemptive
     * Génère une exception ProgrammationManagerException si la nouvelle programmation n'est pas valide.
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \param pourcentage pourcentage de la programmation que l'on souhaite programmer
     * \param tache référence vers une TacheSimplePreemptive
     * \return Programmation ajoutée si elle est valide
     */
    ProgrammationTacheSimplePreemptive& addProgrammationTacheSimplePreemptive(const Date& dateProg, const Horaire& horaireProg, unsigned int pourcentage, TacheSimplePreemptive& tache);

    /*!
     * \brief updateProgrammationTacheSimplePreemptive
     * Met à jour une programmation de type ProgrammationTacheSimplePreemptive.
     * \param programmation
     * \param newDate
     * \param newHoraire
     * \param pourcentage
     */
    void updateProgrammationTacheSimplePreemptive(ProgrammationTacheSimplePreemptive &programmation, const Date& newDate, const Horaire& newHoraire, unsigned int pourcentage);

    /*!
     * \brief deleteProgrammation
     * Supprime la programmation donnée.
     * \param programmation
     */
    void deleteProgrammation(Programmation* programmation) {
        eraseItem(getKeyFrom(programmation->getDateProgrammation(),programmation->getHoraireProgrammation()));
     }

    /*!
     * \brief getProgrammation
     * Génère une exception ProgrammationManagerException si la programmation n'existe pas.
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \return programmation débutant à dateProg horaireProg
     */
    Programmation& getProgrammation(const Date& dateProg, const Horaire& horaireProg);

    /*!
     * \brief getProgrammation
     * Génère une exception ProgrammationManagerException si la programmation n'existe pas.
     * \param dateProg date de la programmation
     * \param horaireProg horaire de la programmation
     * \return const programmation débutant à dateProg horaireProg
     */
    const Programmation& getProgrammation(const Date& dateProg, const Horaire& horaireProg) const;

    /*!
     * \brief begin
     * \param date Date
     * \param horaire Horaire
     * \return iterator au premiers date et horaire étant supérieur à ceux donnés en paramètre
     */
    iterator constraint_begin(const Date& date, const Horaire& horaire=Horaire(0,0)) {
        return items.lower_bound(getKeyFrom(date,horaire));
    }

    /*!
     * \brief end
     * \param date Date
     * \param horaire Horaire
     * \return iterator au premiers date et horaire étant inférieur à ceux donnés en paramètre
     */
    iterator constraint_end(const Date& date, const Horaire& horaire=Horaire(23,59)) {
        return items.upper_bound(getKeyFrom(date,horaire));
    }

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter.
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream);

    /*!
     * \brief loadFrom
     * Permet d'importer les données depuis un fichier XML via le streamreader. Charge uniquement les ProgrammationEvenement.
     * \param xml
     */
    void loadFrom(QXmlStreamReader& xml);

    /*!
     * \brief loadListeProgrammations
     * Permet d'importer les données depuis un fichier XML via le streamreader. Charge les programmations des Taches.
     * \param xml
     * \param tache tache dont il faut charger les programmations
     * \param preemptive true si preemptive, false sinon
     */
    void loadListeProgrammations(QXmlStreamReader& xml, Tache& tache, bool preemptive);

    /*!
     * \brief exportContraintes
     * Permet d'exporter les données compris dans l'intervalle de dates et horaires données vers un fichier XML.
     * \param stream
     * \param dateDebut
     * \param dateFin
     * \param horaireDebut
     * \param horaireFin
     */
    void exportContraintes(QXmlStreamWriter& stream, const Date& dateDebut, const Date& dateFin, const Horaire &horaireDebut=Horaire(0,0), const Horaire& horaireFin=Horaire(23,59));

    /*!
     * \brief getKeyFrom
     * \param date date de la programmation
     * \param horaire horaire de la programmation
     * \return clé de la forme aaaammjjhhmm
     */
    static std::string getKeyFrom(const Date& date, const Horaire& horaire);
};

#endif // PROGRAMMATIONMANAGER_H
