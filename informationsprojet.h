#ifndef INFORMATIONSPROJET_H
#define INFORMATIONSPROJET_H
# include "projet.h"
# include "informationselement.h"

/*!
 * \class InformationsProjet
 * \brief Classe permettant d'afficher des informations sur un projet
 */
class InformationsProjet : public InformationsElement
{
public:

    /*!
     * \brief InformationsProjet
     * Constructeur.
     * \param projet référence vers le projet nous intéressant
     * \param parent widget parent
     */
    InformationsProjet(const Projet& projet, QWidget *parent = 0);
};

#endif // INFORMATIONSPROJET_H
