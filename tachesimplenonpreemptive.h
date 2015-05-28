#ifndef TACHESIMPLENONPREEMPTIVE_H
#define TACHESIMPLENONPREEMPTIVE_H
# include "tachesimple.h"
# include "tachesimplenonpreemptiveexception.h"
# include "programmationtachesimplenonpreemptive.h"

/**\class TacheSimpleNonPreemptive
 * \brief Classe permettant de manipuler des tâches non préemptives
 */
class ProgrammationTacheSimpleNonPreemptive;
class TacheSimpleNonPreemptive : public TacheSimple
{
    /**
     * \brief dureeValide
     * \param duree duree d'une tache
     * \return true si la duree est valide ou non sinon
     */
protected :
    ProgrammationTacheSimpleNonPreemptive* programmationTacheSimpleNonPreemptive;
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
    void setProgrammation(ProgrammationTacheSimpleNonPreemptive* programmationTacheSimpleNonP);
    virtual bool hasProgrammation()const;

    virtual bool isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const;

};

#endif // TACHESIMPLENONPREEMPTIVE_H
