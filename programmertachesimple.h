#ifndef PROGRAMMERTACHESIMPLE_H
#define PROGRAMMERTACHESIMPLE_H
# include "fenetreannulervalider.h"
# include "projet.h"
# include <QDateEdit>
# include <QFormLayout>
# include <QLabel>
#include "programmationtachesimple.h"

/*!
 * \class ProgrammerTacheSimple
 * \brief Classe abstraite contenant les champs permettant de programmer une tâche simple
 */
class ProgrammerTacheSimple : public FenetreAnnulerValider
{
protected:

    Projet* nomProjet; /*!< pointeur vers le projet de la tâche à programmer */
    std::string * chemin; /*!< cheminement vers la tâche à programmer */
    unsigned int* tailleChemin; /*!< taille du tableau chemin */
    std::string titreTache; /*!< titre de la tâche à programmer */
    QDateEdit* dateProgrammation; /*!< date de programmation*/
    QTimeEdit* horaireProgrammation; /*!< horaire de programmation */
    QLabel *titre; /*!< label : titre de la tâche*/
    QLabel *dateDebut; /*!< label : date de disponibilité */
    QLabel *horaireDebut; /*!< label : horaire de disponibilité */
    QLabel *dateEcheance; /*!< label : date d'échéance */
    QLabel *heureEcheance; /*!< label : horaire d'échéance */
    QLabel *duree; /*!< label : duree */
    QFormLayout* formlayout; /*!< formulaire */
    ProgrammationTacheSimple* progTache; /*!< pointeur vers la programmation de tâche*/

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget.
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);
public:

    /*!
     * \brief ProgrammerTacheSimple
     * Constructeur.
     * \param projet pointeur vers le projet de la tâche à programmer
     * \param chaine cheminement vers la tâche à programmer
     * \param taille taille du tableau chemin
     * \param titreT titre de la tâche à programmer
     * \param parent widget parent
     */
    ProgrammerTacheSimple(Projet *projet, std::string * chaine, unsigned int* taille, const std::string &titreT, QWidget *parent = 0);

    ProgrammerTacheSimple(ProgrammationTacheSimple* prog, QWidget *parent = 0);

};

#endif // PROGRAMMERTACHESIMPLE_H
