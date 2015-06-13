#ifndef TOOLS_H
#define TOOLS_H
#include <QString>
#include <QXmlStreamReader>
#include <vector>
#include "projet.h"

/*!
 * \brief save
 *
 * Permet d'exporter les données dans le fichier spécifié
 *
 * \param file
 */
void save(const QString &file);

/*!
 * \brief saveContraintes
 *
 * Permet d'exporter les programmations comprises entre dateDebut et dateFin
 *
 * \param file
 * \param dateDebut
 * \param dateFin
 */
void saveContraintes(const QString& file, const Date& dateDebut, const Date& dateFin);

/*!
 * \brief saveProjet
 *
 * Permet d'exporter le projet donné
 *
 * \param file
 * \param projet
 */
void saveProjet(const QString& file, Projet &projet);

/*!
 * \brief saveProjetProgrammations
 *
 * Permet d'exporter les programmations d'un projet donné
 *
 * \param file
 * \param projet
 */
void saveProjetProgrammations(const QString& file, Projet& projet);

/*!
 * \brief load
 *
 * Permet d'importer les données depuis le fichier spécifié
 *
 * \param file
 */
void load(const QString &file);

/*!
 * \brief loadProjet
 * \param file
 */
void loadProjet(const QString &file);

/*!
 * \brief toQString
 *
 * Converti string en QString
 *
 * \param str string
 * \return QString
 */
QString toQString(const std::string &str);

/*!
 * \brief toQString
 *
 * Converti int en QString
 *
 * \param entier int
 * \return QString
 */
QString toQString(const int entier);

/*!
 * \brief toString
 *
 * Converti QString en string
 *
 * \param str Qtring
 * \return string
 */
std::string toString(const QString &str);

#endif // TOOLS_H
