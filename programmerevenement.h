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

class ProgrammerEvenement: public FenetreAnnulerValider
{
    Q_OBJECT
protected :
    QFormLayout* formlayout;
    QLineEdit* nom; /*!< nom de l'évènement */
    QLineEdit* motif; /*!< motif de l'évènement */
    QLineEdit* lieu; /*!< lieu de l'évènement */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QSpinBox* dureeHeure; /*!< duree heure*/
    QSpinBox* dureeMinute; /*!< duree heure*/
    QHBoxLayout* duree;
    ProgrammationEvenement* progEvt;

    void initialiserFormulaire();
    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);

public:
    explicit ProgrammerEvenement(QWidget *parent = 0);
    explicit ProgrammerEvenement(ProgrammationEvenement* prog, QWidget *parent = 0);
signals:
};

#endif // PROGRAMMEREVENEMENT

