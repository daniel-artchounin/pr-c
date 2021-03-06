#ifndef ELEMENT_H
#define ELEMENT_H
#include "date.h"
#include "horaire.h"
#include "elementexception.h"
#include <QXmlStreamWriter>

/*! \class Element
* \brief Classe possédant un titre ainsi que des dates et horaires de début et de fin.
*/
class Element {

protected:

    std::string titre; /*!< titre de l'élément */
    Date dateDebut; /*!< date de début */
    Horaire horaireDebut; /*!< horaire de début */
    Date dateFin; /*!< date de fin */
    Horaire horaireFin; /*!< horaire de fin */
    Duree duree; /*!< la duree minimale du projet (en supposant que les tâches se succèdent sans espace)*/

public:

    /*!
     * \brief estDansIntervalle
     * Permet de vérifier si une programmation se situe bien dans l'intervalle autorisé (après la disponibilité et avant échéance).
     * \param dateProg date de programmation
     * \param horaireProg horaire de programmation
     * \param pourcentage le pourcentage que l'on va programmer
     * \return vrai si la programmation se trouve dans l'intervalle ou faux sinon
     */
    bool estDansIntervalle(const Date& dateProg, const Horaire& horaireProg, unsigned int pourcentage = 100) const;

    /*!
     * \brief Element
     * \param t titre
     * \param dateD date de début
     * \param horaireD horaire de début
     * \param dateF date de fin
     * \param horaireF horaire de fin
     * \param dur durée
     */
    Element(const std::string& t, const Date& dateD, const Horaire& horaireD, const Date& dateF, const Horaire& horaireF,const Duree& dur=0):
        titre(t), dateDebut(dateD), horaireDebut(horaireD), dateFin(dateF), horaireFin(horaireF),duree(dur) {
        if( (dateF-dateD)*24*60+(horaireF-horaireD) < (int)(dur.getDureeEnMinutes()) ){
            throw ElementException("Erreur : la durée est supérieure à l'intervalle entre la disponibilité et l'échéance.");
        }
    }

    /*!
     * \brief Desctructeur
     * Destructeur virtuel pur.
     */
    virtual ~Element()=0;

    /*!
     * \brief getTitre
     * Accesseur.
     * \return titre de l'élément
     */
    const std::string& getTitre() const {
        return titre;
    }

    /*!
     * \brief getDateDebut
     * Accesseur.
     * \return date de début
     */
    const Date& getDateDebut() const {
        return dateDebut;
    }

    /*!
     * \brief getHoraireDebut
     * Accesseur.
     * \return horaire de début
     */
    const Horaire& getHoraireDebut() const {
        return horaireDebut;
    }

    /*!
     * \brief getDateFin
     * Accesseur.
     * \return date de fin
     */
    const Date& getDateFin() const {
        return dateFin;
    }

    /*!
     * \brief getHoraireFin
     * Accesseur.
     * \return horaire de fin
     */
    const Horaire& getHoraireFin() const {
        return horaireFin;
    }

    /*!
     * \brief getDuree
     * Accesseur.
     * \return retourne un pointeur vers la tâche trouvée ou 0
     */
    const Duree & getDuree()const;

    /*!
     * \brief setDuree
     * Mutateur : permet de mettre à jour la durée de l'élément.
     * \param dur a nouvelle durée
     */
    void setDuree(const Duree& dur){
        duree = dur;
    }

    /*!
     * \brief addDure
     * Permet d'ajouter une durée à la durée de notre élément.
     * \param duree la durée ajoutée
     */
    void addDuree(const Duree& duree){
        setDuree(getDuree()+duree);
    }

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter.
     * \param stream
     */
    virtual void exportTo(QXmlStreamWriter& stream);
};

#endif // ELEMENT_H
