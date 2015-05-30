#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H
#include "evenement.h"

/*! \class RendezVous
 * \brief Classe permettant de manipuler un rendez-vous en définissant un lieu et un motif. Hérite de la classe Evenement.
 */
class RendezVous : public Evenement {
public:
    /*!
     * \brief Constructeur
     * \param n nom du rendez-vous
     * \param l lieu du rendez-vous
     * \param m motif du rendez-vous
     */
    RendezVous(const std::string n, const std::string l, const std::string m):Evenement(n, l, m) {}
};

#endif // RENDEZVOUS_H
