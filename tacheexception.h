#ifndef TACHEEXCEPTION_H
#define TACHEEXCEPTION_H
#include <stdexcept>

/*!
 * \class TacheException
 * Permet de générer des exceptions pour les Tache
 * Hérite de la classe Exception
 */
class TacheException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    TacheException(const std::string& m):logic_error(m) {}
};
#endif // TACHEEXCEPTION_H
