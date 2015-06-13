#ifndef CREERTACHE_H
#define CREERTACHE_H
# include "creerprojettache.h"
# include "projet.h"

/*!
 * \class CreerTache
 * \brief Classe contenant les champs permettant la création d'une tâche
 */
class CreerTache : public CreerProjetTache
{
protected:

    Projet& nomProjet; /*!< référence vers le projet de la tâche à créer */
    std::string * chemin; /*!< cheminement vers la tâche à créer */
    unsigned int* tailleChemin; /*!< taille du tableau chemin */

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);

public:

    /*!
     * \brief CreerTache
     * Constructeur.
     * \param projet référence vers le nom du projet de la tâche à créer
     * \param chaine cheminement vers la tâche à créer
     * \param taille taille du tableau chaine
     * \param parent widget parent
     */
    CreerTache(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);
};

#endif // CREERTACHE_H
