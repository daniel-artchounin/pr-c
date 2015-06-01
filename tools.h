#ifndef TOOLS_H
#define TOOLS_H
#include <QString>
#include <QXmlStreamReader>
#include <vector>
#include "projet.h"

/*!
 * \brief save
 * Permet d'exporter les données dans le fichier spécifié
 * \param file
 */
void save(const QString &file);
/*!
 * \brief load
 * Permet d'importer les données depuis le fichier spécifié
 * \param file
 */
void load(const QString &file);

/*!
 * \brief toQString
 * Convertit string en QString
 * \param str string
 * \return QString
 */
QString toQString(const std::string &str);

/*!
 * \brief toQString
 * Convertit int en QString
 * \param entier int
 * \return QString
 */
QString toQString(const int entier);

/*!
 * \brief toString
 * Convertit QString en string
 * \param str Qtring
 * \return string
 */
std::string toString(const QString &str);

#endif // TOOLS_H
