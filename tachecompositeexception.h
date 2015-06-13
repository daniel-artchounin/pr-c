#ifndef TACHECOMPOSITEEXCEPTION_H
#define TACHECOMPOSITEEXCEPTION_H

/*! \class TacheCompositeException
 *
 * Permet de générer des exceptions pour les TacheComposite
 * Hérite de la classe Logic_error
 */
class TacheCompositeException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    TacheCompositeException(const std::string& m):logic_error(m) {}
};
#endif // TACHECOMPOSITEEXCEPTION_H


