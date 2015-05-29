#ifndef TACHESIMPLEPREEMPTIVE_H
#define TACHESIMPLEPREEMPTIVE_H
# include "tachesimple.h"
# include "duree.h"
# include <vector>
# include "tachesimplepreemptiveexception.h"
# include "programmationtachesimple.h"
# include "programmationtachesimplepreemptive.h"
/**\class TacheSimplePreemptive
 * \brief Classe permettant de manipuler des tâches préemptives
 */

class ProgrammationTacheSimplePreemptive;
class TacheSimplePreemptive : public TacheSimple
{
protected:
    unsigned int pourcentageComplete;
    std::vector <ProgrammationTacheSimplePreemptive*> programmationstachessimplespreemptives;

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
    virtual bool hasProgrammation()const{
        return !programmationstachessimplespreemptives.empty();
    }
    virtual bool isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const;
    void addPourcentageComplete(int prt){
        if (prt+pourcentageComplete>100){
            throw TacheSimplePreemptiveException("addPourcentageComplete : Le pourcentage est supérieur à 100 !");
        }
        setPourcentageComplete(getPourcentageComplete()+prt);
    }
    void addProgrammation(ProgrammationTacheSimplePreemptive * pgrm){
        programmationstachessimplespreemptives.push_back(pgrm);
    }

    Duree getDureeProgrammationViaPourcentage(unsigned int pourcentage)const{
        return Duree((pourcentage * getDuree().getNbMinutes())/100);
    }
};

#endif // TACHESIMPLEPREEMPTIVE_H
