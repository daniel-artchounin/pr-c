#ifndef INFORMATIONSTACHECOMPOSITE_H
#define INFORMATIONSTACHECOMPOSITE_H
# include "tachecomposite.h"
# include "informationstache.h"

/*!
 * \class InformationsTacheComposite
 * \brief Classe permettant d'afficher des informations sur une tâche composite
 */
class InformationsTacheComposite : public InformationsTache
{
public:

    /*!
     * \brief InformationsTacheComposite
     * Constructeur.
     * \param tacheComposite référence vers la tâche composite nous intéressant.
     * \param parent widget parent
     */
    InformationsTacheComposite(const TacheComposite& tacheComposite, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHECOMPOSITE_H
