#ifndef FENETREGESTIONPROJETEXCEPTION_H
#define FENETREGESTIONPROJETEXCEPTION_H

/*!
 * \class FenetreGestionProjetException
 * Permet de générer des exceptions pour la fenetre de gestion de projet
 * Hérite de la classe Logic_error
 */
class FenetreGestionProjetException : public std::logic_error{

public:
    /*!
     * \brief Constructeur
     * Crée une exception avec une information sur celle-ci.
     * \param m information sur l'exception
     */
    FenetreGestionProjetException(const std::string& m):logic_error(m) {}
};
#endif // FENETREGESTIONPROJETEXCEPTION_H
