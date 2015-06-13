#ifndef FENETREGESTIONPROJET_H
#define FENETREGESTIONPROJET_H

#include <QWidget>
# include <projetmanager.h>
# include <QTreeWidget>
# include <QHBoxLayout>
# include <QMenu>
# include "creertachecomposite.h"
# include "creertachesimplepreemptive.h"
# include "creertachesimplenonpreemptive.h"
# include "programmertachesimplenonpreemptive.h"
# include "programmertachesimplepreemptive.h"
# include "ajouterprecedence.h"
# include "supprimerprecedence.h"
# include "informationselement.h"
# include "informationstache.h"
# include "informationstachesimple.h"
# include "informationstachesimplenonpreemptive.h"
# include "informationstachesimplepreemptive.h"
# include "informationstachecomposite.h"
# include "informationsprojet.h"
# include <string>
# include <stdexcept>

/*!
 * \class FenetreGestionProjet
 * \brief Classe permettant de gérer l'interface de gestion de projet
 */
class CreerTacheComposite;
class CreerTacheSimplePreemptive;
class CreerTacheSimpleNonPreemptive;
class FenetreGestionProjet : public QWidget
{
    Q_OBJECT

protected:
    QTreeWidget * tree; /*!< tree view contenant l'ensemble des projet */
    QHBoxLayout* hBox; /*!< QHBoxLayout pour le placement du tree view */
    QAction * creationTacheComposite; /*!< action de création de tâche composite */
    QAction * creationTacheSimplePreemptive; /*!< action de création de tâche simple préemptive */
    QAction * creationTacheSimpleNonPreemptive; /*!< action de création de tâche simple non préemptive */
    QAction * programmationTacheSimplePreemptive; /*!< action de programmation de tâche simple préemptive */
    QAction * programmationTacheSimpleNonPreemptive; /*!< action de programmation de tâche simple non préemptive */
    QAction * consulterElement; /*!< action de consultation d'un élément*/
    QAction * supprimerElement; /*!< action de supression d'un élément*/
    QAction * ajouterPrecedence; /*!< action d'ajout de contrainte de précédence */
    QAction * supprimerPrecedence; /*!< action de suppression de contrainte de précédence */
    CreerTacheComposite* creerTacheComposite; /*!< pointeur vers l'interface de création de tâche composite */
    CreerTacheSimplePreemptive* creerTacheSimplePreemptive; /*!< pointeur vers l'interface de création de tâche simple préemptive */
    CreerTacheSimpleNonPreemptive* creerTacheSimpleNonPreemptive; /*!< pointeur vers l'interface de création de tâche simple non préemptive */
    ProgrammerTacheSimplePreemptive* programmerTacheSimplePreemptive; /*!< pointeur vers l'interface de programmation de tâche simple préemptive */
    ProgrammerTacheSimpleNonPreemptive* programmerTacheSimpleNonPreemptive; /*!< pointeur vers l'interface de programmation de tâche simple non préemptive */
    AjouterPrecedence* ajoutPrecedence;  /*!< pointeur vers l'interface d'e création de tâche composite ajout de contrainte de précédence */
    SupprimerPrecedence* suppressionPrecedence; /*!< pointeur vers l'interface de suppression de contrainte de précédence */
    InformationsTacheSimplePreemptive *informationsTacheSimplePreemptive; /*!< pointeur vers l'interface de consultation d'informations sur une tâche simple préemptive */
    InformationsTacheSimpleNonPreemptive *informationsTacheSimpleNonPreemptive; /*!< pointeur vers l'interface de consultation d'informations sur une tâche simple non préemptive */
    InformationsTacheComposite *informationsTacheComposite; /*!< pointeur vers l'interface de consultation d'informations sur une tâche composite */
    InformationsProjet *informationsProjet;  /*!< pointeur vers l'interface de consultation d'informations sur un projet */

public:
    /*!
     * \brief FenetreGestionProjet constructeur
     * \param parent widget parent
     */
    explicit FenetreGestionProjet(QWidget *parent = 0);

    /*!
     * \brief afficherTreeWidget
     * permet d'afficher le tree view
     * \param profondeur de l'algorithme récursif
     * \param projetManager référence vers l'instance de ProjetManager
     * \param arbre pointeur vers le tree view
     * \param actuel pointeur vers le QTreeWidgetItem auquel on souhaite ajouter des items (on doit négliger ce paramètre lors de l'appel de la méthode)
     * \param element pointeur vers l'Element que l'on souhaite afficher (on doit négliger ce paramètre lors de l'appel de la méthode)
     */
    void afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel=0, Element * element=0);

    /*!
     * \brief getTree accesseur
     * \return un pointeur sur le tree view
     */
    QTreeWidget* getTree()const{
        return tree;
    }

    /*!
     * \brief getCheminement
     * \param actuel pointeur vers le QTreeWidgetItem sélectionner par l'utilisateur
     * \return un QList<QString> contenant le cheminement de l'élement sélectionné par l'utilisateur
     */
    static QList<QString> getCheminement(QTreeWidgetItem * actuel);

    /*!
     * \brief removeTache
     * Permet de supprimer la tâche du cheminement.
     * \param chemin pointeur sur QList<QString> correspondant au cheminement vers un élément
     */
    static void removeTache(QList<QString>* chemin);

    /*!
     * \brief getNomTacheStd
     * \param chemin pointeur sur QList<QString> correspondant au cheminement vers un élément
     * \return le nom de la tâche
     */
    static std::string getNomTacheStd(QList<QString> chemin);

    /*!
     * \brief getNomTacheAndRemoveTache
     * Permet de supprimer la tâche feuille et de récupérer le nom de cette dernière.
     * \param chemin pointeur sur QList<QString> correspondant au cheminement vers un élément
     * \return le nom de la tâche feuille supprimée
     */
    static std::string getNomTacheAndRemoveTache(QList<QString>* chemin);

    /*!
     * \brief recupCheminDepuisProjet
     * \param chemin pointeur sur QList<QString> correspondant au cheminement vers un élément
     * \param taille pointeur vers un entier qui contiendra la taille du cheminement
     * \return le cheminement de tâche composite sous la forme d'un tableau de std::string
     */
    static std::string* recupCheminDepuisProjet(QList<QString> chemin, unsigned int * taille);

    /*!
     * \brief getAndRemoveProjet
     * Permet de supprimer le projet du cheminement et de récupérer le nom de ce dernier.
     * \param chemin pointeur sur QList<QString> correspondant au cheminement vers un élément
     * \return le nom du projet supprimé du cheminement
     */
    static Projet& getAndRemoveProjet(QList<QString>* chemin);

signals:

public slots:

    /*!
     * \brief showContextMenu
     * Slot permettant d'afficher un menu contextuel
     */
    void showContextMenu(const QPoint&);

    /*!
     * \brief fenetreCreerTacheComposite
     * Slot permettant d'afficher une interface de création de tâche composite.
    */
    void fenetreCreerTacheComposite();

    /*!
     * \brief fenetreCreerTacheSimplePreemptive
     * Slot permettant d'afficher une interface de création de tâche simple préemptive.
     */
    void fenetreCreerTacheSimplePreemptive();

    /*!
     * \brief fenetreCreerTacheSimpleNonPreemptive
     * Slot permettant d'afficher une interface de création de tâche simple non préemptive.
     */
    void fenetreCreerTacheSimpleNonPreemptive();

    /*!
     * \brief fenetreProgrammerTacheSimplePreemptive
     * Slot permettant d'afficher une interface de programmation de tâche simple préemptive.
     */
    void fenetreProgrammerTacheSimplePreemptive();

    /*!
     * \brief fenetreProgrammerTacheSimpleNonPreemptive
     * Slot permettant d'afficher une interface de programmation de tâche simple non préemptive.
     */
    void fenetreProgrammerTacheSimpleNonPreemptive();

    /*!
     * \brief fenetreAjouterPrecedence
     * Slot permettant d'afficher une interface d'ajout de contrainte de précédence.
     */
    void fenetreAjouterPrecedence();

    /*!
     * \brief fenetreSupprimerPrecedence
     * Slot permettant d'afficher une interface de suppression de contrainte de précédence.
     */
    void fenetreSupprimerPrecedence();

    /*!
     * \brief supprimerUnElemment
     * Slot permettant de supprimer un élément.
     */
    void supprimerUnElemment();

    /*!
     * \brief consulterUnElemment
     * Slot permettant d'afficher une interface de consultation d'informations sur un élément.
     */
    void consulterUnElemment();
};

#endif // FENETREGESTIONPROJET_H
