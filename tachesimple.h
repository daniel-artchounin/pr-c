#ifndef TACHESIMPLE_H
#define TACHESIMPLE_H
#include "duree.h"
#include "date.h"
#include "horaire.h"
#include "tache.h"

/**\class TacheSimple
 * \brief Classe permettant de manipuler des tâches simples
 */

// c'est une classe abtraite (elle ne peut pas être instancié) -> je n'ai pas réussi à la rendre abstraite

class TacheSimple : public Tache
{
    Duree duree;
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
     * \brief getDuree accesseur
     * \return retourne un pointeur vers la tâche trouvée ou 0
     */
    const Duree & getDuree()const;
    // getDateFin -> erreur dans l'UML
    // getHeureFin -> erreur dans l'UML
    /**
     * \brief isTermine
     * \return retourne true si la tâche est terminé ou
     * false sinon
     */
    bool isTermine()const;
    /**
     * \brief setTermine mutateur
     * \param state le nouvel état de la tâche (true : terminé / false : non terminé)
     */
    void setTermine(bool state);
};

#endif // TACHESIMPLE_H
