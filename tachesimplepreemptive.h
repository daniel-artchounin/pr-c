#ifndef TACHESIMPLEPREEMPTIVE_H
#define TACHESIMPLEPREEMPTIVE_H
#include "tachesimple.h"
# include <vector>
# include <programmationmanager.h>

class ProgrammationTacheSimplePreemptive;

/*! \class TacheSimplePreemptive
 * \brief Classe permettant de manipuler des tâches simples préemptives.
 */
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
    virtual bool hasProgrammation()const;

    /**
     * \brief setPourcentageDejaProgramme mutateur
     * Soulève une TacheSimplePreemptiveException en cas d'incohérence.
     * \param prt le nouveau pourcentage programmé
     */
    void setPourcentageDejaProgramme(int prt);

    /*!
     * \brief addPourcentageDejaProgramme
     * Augmente le pourcentage déjà programmé de la tâche.
     * \param prt
     */
    void addPourcentageDejaProgramme(int prt);

    /*!
     * \brief addProgrammation
     * Ajoute une nouvelle programmation à la tâche préemptive actuelle.
     * \param pgrm pointeur vers la programmtion de tâche simple préemptive
     */
    void addProgrammation(ProgrammationTacheSimplePreemptive * pgrm);

    /*!
     * \brief eraseProgrammation
     * Permet d'effacer le lien entre la tâche simple préemptive et une de ses programmations.
     * \param dateProgrammation date de programmation
     * \param horaireProgrammation horaire de programmation
     */
    void eraseProgrammation(const Date& dateProgrammation, const Horaire& horaireProgrammation);

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
     * \brief getDureeProgrammationViaPourcentage
     * Accesseur.
     * Calcule la durée de la tâche correspondant au pourcentage transmis en paramètre.
     * \param pourcentage pourcentage dont on souhaite connaitre la durée correspondante
     * \return la durée de la tâche correspondant au pourcentage transmis en paramètre
     */
    Duree getDureeProgrammationViaPourcentage(unsigned int pourcentage)const{
        return Duree((pourcentage * getDuree().getDureeEnMinutes())/100);
    }

    typedef typename PVector::iterator p_iterator;
    typedef typename PVector::const_iterator p_const_iterator;

    /*!
     * \brief pSize
     * \return la taille du vector des programmations de tâche simple préemtive
     */
    int pSize()const{
        return int(programmationsTachesSimplesPreemptives.size());
    }

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
     * \return iterator const sur le début du vector
     */
    p_const_iterator pBegin() const{ return const_cast<TacheSimplePreemptive *>(this)->pBegin(); }

    /*!
     * \brief pEnd
     * \return iterator const sur la fin du vector
     */
    p_const_iterator pEnd() const{ return const_cast<TacheSimplePreemptive *>(this)->pEnd(); }

    /*!
     * \brief getProgrammation
     * Permet de trouver une programmation de notre
     * tâche simple préemptive à partir d'une date et d'un horaire.
     * \param dateDebut date de la programmation à trouver
     * \param horaireDebut horaire de la programmation à trouver
     * \return pointeur vers un objet de type ProgrammationTacheSimplePreemptive si trouvé, 0 sinon
     */
    ProgrammationTacheSimplePreemptive* getProgrammation(const Date&  dateDebut, const Horaire& horaireDebut) const;

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter.
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream);

    void exportProgrammations(QXmlStreamWriter& stream);

    /*!
     * \brief ~TacheSimplePreemptive
     * Destructeur.
     */
    virtual ~TacheSimplePreemptive();
};

#endif // TACHESIMPLEPREEMPTIVE_H
