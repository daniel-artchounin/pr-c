#ifndef ELEMENTEXCEPTION_H
#define ELEMENTEXCEPTION_H

/*!
 * \class ElementException
 *
 * Permet de générer des exceptions pour les éléments
 * Hérite de la classe Logic_error
 */
class ElementException : public std::logic_error{
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    ElementException(const std::string& m):logic_error(m) {}
};
#endif // ELEMENTEXCEPTION_H
