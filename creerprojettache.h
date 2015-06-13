#ifndef CREERPROJETTACHE_H
#define CREERPROJETTACHE_H
# include "fenetreannulervalider.h"
# include <QFormLayout>
# include <QLineEdit>
# include <QDateEdit>
# include <QTimeEdit>

/*!
 * \class CreerProjetTache
 * \brief Classe abstraite contenant les champs permettant la création d'un projet ou d'une tâche
 */
class CreerProjetTache : public FenetreAnnulerValider
{

public:

    /*!
     * \brief CreerProjetTache
     * Constructeur.
     * \param parent widget parent
     */
    CreerProjetTache(QWidget *parent = 0);

protected:

    QFormLayout* formlayout; /*!< formulaire */
    QLineEdit* titre; /*!< titre de l'élément */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QDateEdit* dateFin; /*!< date de fin */
    QTimeEdit* horaireFin; /*!< horaire de fin */
};

#endif // CREERPROJETTACHE_H
