#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include "manager.h"
#include "projet.h"

/*! \class ProjetManager
 * \brief Classe permettant de manipuler des projets. Hérite de la classe Manager. Utilise le design pattern singleton
 */
class ProjetManager : public Manager<Projet> {
private:
    //design pattern singleton
    static ProjetManager * instance; /*!< instance unique de ProjetManager */

    /*!
     * \brief Constructeur
     * Constructeur privé afin d'empêcher la duplication
     */
    ProjetManager(): Manager<Projet>(){}
    /*!
     *\brief Destructeur
     * Destructeur privé
     */
    ~ProjetManager() {}
    /*!
     * \brief Contructeur par recopie
     * Constructeur par recopie privé
     * \param pm ProjetManager
     */
    ProjetManager(const ProjetManager& pm);
    /*!
     * \brief Operateur d'affectation
     * Opérateur d'affectation privé
     * \param pm ProjetManager
     */
    ProjetManager& operator=(const ProjetManager& pm);
public:
    //design pattern singleton
    /*!
     * \brief getInstance
     * \return instance unique de ProjetManager
     */
    static ProjetManager& getInstance();
    /*!
     * \brief libererInstance
     * Détruit l'instance unique de ProjetManager
     */
    static void libererInstance();
    /*!
     * \brief addProjet
     * Génère une exception ProjetManagerException si un projet ayant le même titre existe déjà
     * \param titre titre du projet
     * \param dateDebut date de début du projet
     * \param horaireDebut horaire de début du projet
     * \param dateFin date de fin du projet
     * \param horaireFin horaire de fin du projet
     * \return Projet si celui-ci a été ajouté
     */
    Projet& addProjet(const std::string& titre, const Date& dateDebut, const Horaire& horaireDebut, const Date& dateFin, const Horaire& horaireFin);
    /*!
     * \brief getProjet
     * Génère une exception ProjetManagerException si le projet n'a pas été trouvé
     * \param titre titre du projet à trouver
     * \return Projet si le projet existe
     */
    Projet& getProjet(const std::string& titre);
    /*!
     * \brief getProjet
     * Génère une exception ProjetManagerException si le projet n'a pas été trouvé
     * \param titre titre du projet à trouver
     * \return const Projet si le projet existe
     */
    const Projet& getProjet(const std::string& titre) const;
};

#endif // PROJETMANAGER_H
