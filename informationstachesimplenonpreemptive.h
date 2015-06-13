#ifndef INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
#define INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
# include "informationstachesimple.h"
# include "tachesimplenonpreemptive.h"

/*!
 * \class InformationsTacheSimpleNonPreemptive
 * \brief Classe permettant d'afficher des informations sur une tâche simple non préemptive
 */
class InformationsTacheSimpleNonPreemptive : public InformationsTacheSimple
{

protected:

    QLabel *dateDebutP; /*!< label : date de début de programmation */
    QLabel *horaireDebutP; /*!< label : horaire de début de programmation */
    QLabel *dateEcheanceP; /*!< label : date de fin programmation */
    QLabel *heureEcheanceP; /*!< label : horaire de fin de programmation */

public:

    /*!
     * \brief InformationsTacheSimpleNonPreemptive
     * Constructeur.
     * \param tacheSimpleNonPreemptive référence vers la tâche simple non préemptive nous intéressant.
     * \param parent widget parent
     */
    InformationsTacheSimpleNonPreemptive(const TacheSimpleNonPreemptive& tacheSimpleNonPreemptive, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
