#ifndef TACHESIMPLE_H
#define TACHESIMPLE_H

#include "duree.h"
#include "date.h"
# include "horaire.h"
# include "tache.h"
/**\class TacheSimple
 * \brief Classe permettant de manipuler des tâches simples
 */
class TacheSimple : public Tache{
    protected:
        bool termine;
    public:
        /**
         * \brief TacheSimple Constructeur
         * \param dateD date de disponiblité
         * \param heureD heure de disponiblité
         * \param dateEcheance date d'échéance
         * \param heureEcheance heure d'échéance
         * \param titre titre de la tache
         * \param duree de la tache
         */
        TacheSimple(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                    const Horaire& heureEcheance,const std::string & titre,const Duree & dur);

        /**
         * \brief isTermine
         * \return retourne true si la tâche est terminé ou
         * false sinon
         */
        /**
         * \brief setTermine mutateur
         * \param state le nouvel état de la tâche (true : terminé / false : non terminé)
         */
        virtual bool hasProgrammation()const=0;
        virtual bool isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg) const=0;


};

#endif // TACHESIMPLE_H
