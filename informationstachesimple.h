#ifndef INFORMATIONSTACHESIMPLE_H
#define INFORMATIONSTACHESIMPLE_H
# include "informationstache.h"
# include "tachesimple.h"

/*!
 * \class InformationsTacheSimple
 * \brief Classe permettant d'afficher des informations sur une tâche simple
 */
class InformationsTacheSimple : public InformationsTache
{

protected:

public:

    /*!
     * \brief InformationsTacheSimple
     * Constructeur.
     * \param tacheSimple référence vers la tâche simple nous intéressant
     * \param parent widget parent
     */
    InformationsTacheSimple(const TacheSimple& tacheSimple, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHESIMPLE_H
