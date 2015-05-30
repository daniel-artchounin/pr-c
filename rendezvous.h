#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

/*! \class RendezVous
 * \brief Classe permettant de manipuler un rendez-vous en définissant un lieu et un motif. Hérite de la classe Evenement.
 */
class RendezVous : public Evenement {
protected:
    std::string lieu; /*!< lieu du rendez-vous */
    std::string motif; /*!< motif du rendez-vous */

public:
    /*!
     * \brief Constructeur
     * \param n nom du rendez-vous
     * \param l lieu du rendez-vous
     * \param m motif du rendez-vous
     */
    RendezVous(const std::string n, const std::string l, const std::string m):Evenement(n), lieu(l), motif(m) {}

    /*!
     * \brief getLieu
     * \return lieu du rendez-vous
     */
    std::string getLieu() const {
        return lieu;
    }

    /*!
     * \brief getMotif
     * \return motif du rendez-vous
     */
    std::string getMotif() const {
        return motif;
    }
};

#endif // RENDEZVOUS_H
