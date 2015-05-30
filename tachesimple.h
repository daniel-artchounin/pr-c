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
        /*!
         * \brief hasProgrammation
         * \return vrai si la taĉhe a au moins une programmtion ou faux sinon
         */
        virtual bool hasProgrammation()const=0;
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

        /*!
         * \brief isEndProgrammationOk permet de vérifier que
         * la tâche a été programmée intégralement et que la fin de la programmation
         * précéde celle transmise en paramètre
         * \param dateProg date de début de la programmation
         * \param horaireProg horaire de début de la programmation
         * \return vrai si la tâche a été programmé intégralement et que la fin de la programmation
         * précédè celle transmise en paramètre ou faux sinon
         */
        virtual bool isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg) const=0;
};

#endif // TACHESIMPLE_H
