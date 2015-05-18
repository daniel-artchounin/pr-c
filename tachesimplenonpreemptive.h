#ifndef TACHESIMPLENONPREEMPTIVE_H
#define TACHESIMPLENONPREEMPTIVE_H
# include "tachesimple.h"
# include "tachesimplenonpreemptiveexception.h"

/**\class TacheSimpleNonPreemptive
 * \brief Classe permettant de manipuler des tâches non préemptives
 */
class TacheSimpleNonPreemptive : public TacheSimple
{
    /**
     * \brief dureeValide
     * \param duree duree d'une tache
     * \return true si la duree est valide ou non sinon
     */
    bool dureeValide(const Duree& duree);
public:
    /**
     * \brief TacheSimpleNonPreemptive Constructeur
     * peut générer une exception
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     * \param dur durée de la tache
     */
    TacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                             const Horaire& heureEcheance,const std::string & titre,const Duree & dur);
    // dureeValide()
};

#endif // TACHESIMPLENONPREEMPTIVE_H
