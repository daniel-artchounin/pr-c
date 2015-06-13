#ifndef TACHEEXCEPTION_H
#define TACHEEXCEPTION_H

/*! \class TacheException
 *
 * Permet de générer des exceptions pour les Tache
 * Hérite de la classe Logic_error
 */
class TacheException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    TacheException(const std::string& m):logic_error(m) {}
};
#endif // TACHEEXCEPTION_H

