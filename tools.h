#ifndef TOOLS_H
#define TOOLS_H
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QString>
#include <string>
#include "projetmanager.h"
#include "element.h"
#include "projet.h"
#include "tachecomposite.h"
#include "tachesimplenonpreemptive.h"
#include "tachesimplepreemptive.h"

void save(const QString &file);
void load(const QString &file);

void exportProjetManager(QXmlStreamWriter& stream);
void exportElement(QXmlStreamWriter& stream, const Element &element);
void exportProjet(QXmlStreamWriter& stream, const Projet& projet);
void exportTache(QXmlStreamWriter& stream, const Tache& tache);
void exportTacheComposite(QXmlStreamWriter& stream, const TacheComposite& tache);
void exportTacheSimpleNonPreemptive(QXmlStreamWriter& stream, const TacheSimpleNonPreemptive& tache);
void exportTacheSimplePreemptive(QXmlStreamWriter& stream, const TacheSimplePreemptive& tache);
void castAndExportTache(QXmlStreamWriter& stream, Tache &tache);

QString toQString(const std::string &str);
std::string toString(const QString &str);

#endif // TOOLS_H
