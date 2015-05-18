#ifndef TACHECOMPOSITEEXCEPTION_H
#define TACHECOMPOSITEEXCEPTION_H
#include <stdexcept>

/*!
 * \class TacheCompositeException
 * Permet de générer des exceptions pour les TacheComposite
 * Hérite de la classe Exception
 */
class TacheCompositeException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    TacheCompositeException(const std::string& m):logic_error(m) {}
};
#endif // TACHECOMPOSITEEXCEPTION_H


