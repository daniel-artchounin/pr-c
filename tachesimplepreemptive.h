#ifndef TACHESIMPLEPREEMPTIVE_H
#define TACHESIMPLEPREEMPTIVE_H
# include "tachesimple.h"
# include "duree.h"
# include <vector>
# include "tachesimplepreemptiveexception.h"
# include "programmationtachesimple.h"
# include "programmationtachesimplepreemptive.h"
# include "date.h"
# include "horaire.h"
/**\class TacheSimplePreemptive
 * \brief Classe permettant de manipuler des tâches préemptives
 */

class ProgrammationTacheSimplePreemptive;
class TacheSimplePreemptive : public TacheSimple
{
    friend class ProgrammationTacheSimplePreemptive;

protected:
    unsigned int pourcentageDejaProgramme;/*!< le pourcentage déjà programmé de la tâche*/
    typedef std::vector <ProgrammationTacheSimplePreemptive*> PVector;
    PVector programmationsTachesSimplesPreemptives;  /*!< vector contenant des pointeurs vers les programmations de la tâche simple préemptive */

    /*!
     * \brief hasProgrammation
     * \return vrai si la taĉhe a au moins une programmtion ou faux sinon
     */
    virtual bool hasProgrammation()const{
        return !programmationsTachesSimplesPreemptives.empty();
    }

    /**
     * \brief setPourcentageDejaProgramme mutateur
     * Soulève une exception en cas d'incohérence
     * \param prt le nouveau pourcentage programmé
     */
    void setPourcentageDejaProgramme(int prt);

    /*!
     * \brief addPourcentageDejaProgramme
     * augment le pourcentage déjà programmé de la tâche
     * \param prt
     */
    void addPourcentageDejaProgramme(int prt){
        setPourcentageDejaProgramme(getPourcentageDejaProgramme()+prt);
    }

    /*!
     * \brief addProgrammation
     * ajoute une nouvelle programmation à la tâche préemptive actuelle
     * \param pgrm pointeur vers la programmtion de tâche simple préemptive
     */
    void addProgrammation(ProgrammationTacheSimplePreemptive * pgrm){
        programmationsTachesSimplesPreemptives.push_back(pgrm);
    }

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
                          const Duree& dur);

    /**
     * \brief getPourcentageDejaProgramme accesseur
     * \return retourne le pourcentage programmé de la tâche préemptive
     */
    unsigned int getPourcentageDejaProgramme()const;

    /*!
     * \brief isEndProgrammationOk permet de vérifier que
     * la tâche a été programmée intégralement et que la fin de la programmation
     * précède celle transmise en paramètre
     * \param dateProg date de début de la programmation
     * \param horaireProg horaire de début de la programmation
     * \return vrai si la tâche a été programmée intégralement et que la fin de la programmation
     * précéde celle transmise en paramètre ou faux sinon
     */
    virtual bool isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const;

    /*!
     * \brief getDureeProgrammationViaPourcentage accesseur
     * calcule la durée de la tâche correspondant au pourcentage transmis en paramètre
     * \param pourcentage pourcentage dont on souhaite connaitre la durée correspondante
     * \return la durée de la tâche correspondant au pourcentage transmis en paramètre
     */
    Duree getDureeProgrammationViaPourcentage(unsigned int pourcentage)const{
        return Duree((pourcentage * getDuree().getDureeEnMinutes())/100);
    }

    typedef typename PVector::iterator p_iterator;
    typedef typename PVector::const_iterator p_const_iterator;

    /*!
     * \brief pBegin
     * \return iterator sur le début du vector
     */
    p_iterator pBegin() { return programmationsTachesSimplesPreemptives.begin(); }

    /*!
     * \brief pEnd
     * \return iterator sur la fin du vector
     */
    p_iterator pEnd() { return programmationsTachesSimplesPreemptives.end(); }

    /*!
     * \brief pBegin
     * \return iterator sur le début du vector
     */
    p_const_iterator pBegin() const{ return const_cast<TacheSimplePreemptive *>(this)->pBegin(); }
    /*!
     * \brief pEnd
     * \return iterator sur la fin du vector
     */
    p_const_iterator pEnd() const{ return const_cast<TacheSimplePreemptive *>(this)->pEnd(); }

    /*!
     * \brief getItem
     * \param dateDebut date de la programmation à trouver
     * \param horaireDebut horaire de la programmation à trouver
     * \return item si trouvé, 0 sinon
     */
    ProgrammationTacheSimplePreemptive* getProgrammation(const Date&  dateDebut, const Horaire& horaireDebut) const;
};

#endif // TACHESIMPLEPREEMPTIVE_H
