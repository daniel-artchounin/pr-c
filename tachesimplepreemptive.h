#ifndef TACHESIMPLEPREEMPTIVE_H
#define TACHESIMPLEPREEMPTIVE_H
# include "tachesimple.h"
# include "duree.h"

/**\class TacheSimplePreemptive
 * \brief Classe permettant de manipuler des tâches préemptives
 */

class TacheSimplePreemptive : public TacheSimple
{
protected:
    unsigned int pourcentageComplete;

public:
    /**
     * \brief TacheSimpleNonPreemptive Constructeur
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     * \param dur durée de la tache
     */
    TacheSimplePreemptive(const Date& dateD,
                          const Horaire& heureD,
                          const Date& dateEcheance,
                          const Horaire& heureEcheance,
                          const std::string & titre,
                          const Duree & dur);
    /**
     * \brief getPourcentageComplete accesseur
     * \return retourne le pourcentage complété de la tâche préemptive
     */
    unsigned int getPourcentageComplete()const;
    /**
     * \brief setPourcentageComplete mutateur
     * \param prt le nouveau pourcentage complete
     */
    void setPourcentageComplete(int prt);
};

#endif // TACHESIMPLEPREEMPTIVE_H
