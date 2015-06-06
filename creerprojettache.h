#ifndef CREERPROJETTACHE_H
#define CREERPROJETTACHE_H
# include "fenetreannulervalider.h"
# include <QFormLayout>
# include <QLineEdit>
# include <QDateEdit>
# include <QTimeEdit>

class CreerProjetTache : public FenetreAnnulerValider
{
public:
    CreerProjetTache(QWidget *parent = 0);
protected:
    QFormLayout* formlayout;
    QLineEdit* titre; /*!< titre de l'élément */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QDateEdit* dateFin; /*!< date de fin */
    QTimeEdit* horaireFin; /*!< horaire de fin */
};

#endif // CREERPROJETTACHE_H
