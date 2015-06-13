#ifndef REUNION_H
#define REUNION_H
#include "evenement.h"

/*! \class Reunion
 * \brief Classe permettant de manipuler une réunion en définissant un lieu et un motif. Hérite de la classe Evenement.
 */
class Reunion : public Evenement {
public:
    /*!
     * \brief Constructeur
     * \param n nom de la réunion
     * \param l lieu de la réunion
     * \param m motif de la réunion
     */
    Reunion(const std::string n, const std::string l, const std::string m):Evenement(n, l, m) {}

    /*!
     * \brief exportTo
     *
     * Permet d'exporter les données dans un fichier XML via le streamwriter
     *
     * \param stream
     */
    void exportTo(QXmlStreamWriter& stream) {
        stream.writeStartElement("Reunion");
        Evenement::exportTo(stream);
        stream.writeEndElement();
    }
};

#endif // REUNION_H
