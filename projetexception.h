#ifndef PROJETEXCEPTION_H
#define PROJETEXCEPTION_H
#include <stdexcept>

/*!
 * \class ProjetException
 * Permet de générer des exceptions pour les Projet
 * Hérite de la classe Exception
 */
class ProjetException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    ProjetException(const std::string& m):logic_error(m) {}
};
#endif // PROJETEXCEPTION_H