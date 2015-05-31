#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <string>
#include <QXmlStreamWriter>

/*! \class Evenement
 * \brief Classe possédant un nom. Correspond à un évènement traditionnel.
 */
class Evenement {
protected:
    std::string nom; /*!< nom de l'évènement */
    std::string lieu; /*!< lieu de l'évenement */
    std::string motif; /*!< motif de l'évenement */
public:
    /*!
     * \brief Constructeur
     * \param n nom de l'évènement
     */
    Evenement(const std::string n, const std::string l, const std::string m):nom(n), lieu(l), motif(m){}

    /*!
     * \brief Desctructeur
     * Destructeur virtual pure.
     */
    virtual ~Evenement()=0;

    /*!
     * \brief getNom
     * \return nom de l'évènement
     */
    std::string getNom() const{
        return nom;
    }

    /*!
     * \brief getLieu
     * \return lieu de la réunion
     */
    std::string getLieu() const {
        return lieu;
    }

    /*!
     * \brief getMotif
     * \return motif de la réunion
     */
    std::string getMotif() const {
        return motif;
    }

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter
     * \param stream
     */
    virtual void exportTo(QXmlStreamWriter& stream);
};

#endif // EVENEMENT_H
