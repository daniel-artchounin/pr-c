#ifndef TACHESIMPLENONPREEMPTIVE_H
#define TACHESIMPLENONPREEMPTIVE_H
# include "tachesimple.h"
# include "tachesimplenonpreemptiveexception.h"
# include "programmationtachesimplenonpreemptive.h"

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
    void setProgrammation(ProgrammationTacheSimpleNonPreemptive* programmationTacheSimpleNonP){
        programmationTacheSimpleNonPreemptive = programmationTacheSimpleNonP;
    }
    virtual bool hasProgrammation()const{
        if(programmationTacheSimpleNonPreemptive==0){
            return false;
        }
        return true;
    }

    virtual bool isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const{
        if(!hasProgrammation()){
            // la tache ne possède pas encore de programmation
            return false;
        }else{
            // récupération de la programmation
            if(programmationTacheSimpleNonPreemptive->getDateFin()<= dateProg ||
                    (programmationTacheSimpleNonPreemptive->getDateFin()== dateProg && programmationTacheSimpleNonPreemptive->getHoraireFin() <= horaireProg) ){
                return true;
            }
            // la programmation ne sera pas terminée avant le début de notre prévision de programmation
            return false;

        }

    }

};

#endif // TACHESIMPLENONPREEMPTIVE_H
