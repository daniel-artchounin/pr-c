#ifndef PROGRAMMEREVENEMENT
#define PROGRAMMEREVENEMENT

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
# include "fenetreannulervalider.h"
#include "programmationevenement.h"

/*!
 * \brief ProgrammerEvenement
 * Class permettant de créer un formulaire afin de créer ou modifier une programmation d'un évènement
 */
class ProgrammerEvenement: public FenetreAnnulerValider
{
    Q_OBJECT

protected :

    QFormLayout* formlayout; /*!< form */
    QLineEdit* nom; /*!< nom de l'évènement */
    QLineEdit* motif; /*!< motif de l'évènement */
    QLineEdit* lieu; /*!< lieu de l'évènement */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QSpinBox* dureeHeure; /*!< duree heure*/
    QSpinBox* dureeMinute; /*!< duree heure*/
    QHBoxLayout* duree; /*!< duree regroupant les spinbox */
    ProgrammationEvenement* progEvt; /*!< progEvt programmation à modifier */

    /*!
     * \brief initialiserFormulaire
     * Permet de créer le formulaire.
     */
    void initialiserFormulaire();

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget.
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);

public:

    /*!
     * \brief Constructeur
     * Crée le formulaire ProgrammerEvenement.
     * \param parent
     */
    explicit ProgrammerEvenement(QWidget *parent = 0);

    /*!
     * \brief ProgrammerEvenement
     * Crée le formulaire ProgrammerEvenement pré-rempli avec les données d'une programmation donnée.
     * \param prog programmation
     * \param parent
     */
    explicit ProgrammerEvenement(ProgrammationEvenement* prog, QWidget *parent = 0);

signals:

};

#endif // PROGRAMMEREVENEMENT

