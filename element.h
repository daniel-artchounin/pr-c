#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include "date.h"
#include "horaire.h"
# include "duree.h"

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
    Duree duree;
    bool estDansIntervalle(const Date& dateProg, const Horaire& horaireProg){
        if( ( dateProg>=dateDebut || (dateProg==dateDebut && horaireProg >= horaireDebut) )
              && ( (dateFin-dateProg)*24*60+(horaireFin-horaireProg)-duree.getNbMinutes()  >= 0) ){
            return true;
        }
        return false;
    }
public:
    /*!
     * \brief Constructeur
     * \param t titre
     * \param dateD date de début
     * \param horaireD horaire de début
     * \param dateF date de fin
     * \param horaireF horaire de fin
     */
    Element(const std::string t, const Date dateD, const Horaire horaireD, const Date dateF, const Horaire horaireF,const Duree& dur=0):
        titre(t), dateDebut(dateD), horaireDebut(horaireD), dateFin(dateF), horaireFin(horaireF),duree(dur) {}
    /*!
     * \brief Desctructeur
     * Destructeur virtual pure.
     */
    virtual ~Element()=0;
    /*!
     * \brief getTitre
     * \return titre de l'élément
     */
    const std::string& getTitre() const {
        return titre;
    }
    /*!
     * \brief getDateDebut
     * \return date de début
     */
    const Date& getDateDebut() const {
        return dateDebut;
    }
    /*!
     * \brief getHoraireDebut
     * \return horaire de début
     */
    const Horaire& getHoraireDebut() const {
        return horaireDebut;
    }
    /*!
     * \brief getDateFin
     * \return date de fin
     */
    const Date& getDateFin() const {
        return dateFin;
    }
    /*!
     * \brief getHoraireFin
     * \return horaire de fin
     */
    const Horaire& getHoraireFin() const {
        return horaireFin;
    }

    /**
     * \brief getDuree accesseur
     * \return retourne un pointeur vers la tâche trouvée ou 0
     */
    const Duree & getDuree()const;

    void setDuree(Duree duree1){
        duree = duree1;
    }

    void addDuree(const Duree& dureeBis){
        setDuree(getDuree()+dureeBis);
    }


};

#endif // ELEMENT_H
