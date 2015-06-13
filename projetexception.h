#ifndef PROJETEXCEPTION_H
#define PROJETEXCEPTION_H
#include <stdexcept>

/*! \class ProjetException
 * Permet de générer des exceptions pour les Projet.
 * Hérite de la classe Logic_error.
 */
class ProjetException : public std::logic_error {

public:
    /*!
     * \brief Constructeur
     * Crée une exception avec une information sur celle-ci.
     * \param m information sur l'exception
     */
    ProjetException(const std::string& m):logic_error(m) {}

};
#endif // PROJETEXCEPTION_H
