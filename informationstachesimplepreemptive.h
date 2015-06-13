#ifndef INFORMATIONSTACHESIMPLEPREEMPTIVE_H
#define INFORMATIONSTACHESIMPLEPREEMPTIVE_H

# include "informationstachesimple.h"
# include "tachesimplepreemptive.h"

/*!
 * \class InformationsTacheSimplePreemptive
 * \brief Classe permettant d'afficher des informations sur une tâche simple préemptive.
 */
class InformationsTacheSimplePreemptive : public InformationsTacheSimple
{

protected :

    QTableWidget* programmationsTableWidget; /*!< contiendra les programmations de la tâche simple préemptive */
    QHBoxLayout* hBoxProgrammations; /*!< permet d'optimiser la position du tableau des programmations de la tâche simple préemptive */

public:

    /*!
     * \brief InformationsTacheSimplePreemptive
     * Constructeur
     * \param tacheSimplePreemptive référence vers la tâche simple préemptive nous intéressant
     * \param parent widget parent
     */
    InformationsTacheSimplePreemptive(const TacheSimplePreemptive& tacheSimplePreemptive, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHESIMPLEPREEMPTIVE_H
