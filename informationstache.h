#ifndef INFORMATIONSTACHE_H
#define INFORMATIONSTACHE_H
# include "informationselement.h"
# include "tache.h"
# include <QTableWidget>
# include <QTableWidgetItem>

/*!
 * \class InformationsTache
 * \brief Classe permettant d'afficher des informations sur une tâche
 */
class InformationsTache : public InformationsElement
{
public:

    QTableWidget* precendentTableWidget; /*!< contiendra l'ensemble des tâches précédant la tâche nous intéressant */
    QTableWidget* suivantTableWidget; /*!< contiendra l'ensemble des tâches succédant la tâche nous intéressant */
    QHBoxLayout* hBoxPrecedent; /*!< pour optimiser la position des contraintes de précédence */
    QHBoxLayout* hBoxSuivant; /*!< pour optimiser la position des contraintes de "suivance"*/
    QVBoxLayout* vBoxPrecedence; /*!< pour optimser la position des blocs matérialisant les contraintes de précédence */

    /*!
     * \brief InformationsTache
     * Constructeur.
     * \param tache référence vers la tâche nous intéressant
     * \param parent widget parent
     */
    InformationsTache(const Tache& tache, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHE_H
