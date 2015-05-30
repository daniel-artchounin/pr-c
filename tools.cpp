#include "tools.h"
#include <typeinfo>
#include "toolsexception.h"
#include <QFile>

void save(const QString& file){
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw ToolsException("XmlParser erreur : impossible d'ouvrir le fichier !");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    exportProjetManager(stream);
    stream.writeEndDocument();
    newfile.close();
}

void exportProjetManager(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProjetManager");
    ProjetManager& pm = ProjetManager::getInstance();
    for(ProjetManager::iterator it=pm.begin(); it!=pm.end(); ++it){
        exportProjet(stream, *it->second);
    }
    stream.writeEndElement();
}

void exportElement(QXmlStreamWriter& stream, const Element& element) {
    stream.writeTextElement("titre",toQString(element.getTitre()));
    stream.writeTextElement("dateDebut",toQString(element.getDateDebut().toString()));
    stream.writeTextElement("horaireDebut",toQString(element.getHoraireDebut().toString()));
    stream.writeTextElement("dateFin",toQString(element.getDateFin().toString()));
    stream.writeTextElement("horaireFin",toQString(element.getHoraireFin().toString()));
    stream.writeTextElement("duree",toQString(element.getDuree().toString()));
}

void exportProjet(QXmlStreamWriter& stream, const Projet& projet) {
    stream.writeStartElement("Projet");
    exportElement(stream, projet);
    for(Projet::const_iterator it=projet.begin(); it!=projet.end(); ++it){
        castAndExportTache(stream, *it->second);
    }
    stream.writeEndElement();
}

void exportTache(QXmlStreamWriter& stream, const Tache& tache) {
    exportElement(stream, tache);
    for(Tache::tp_const_iterator it=tache.tPBegin(); it!=tache.tPEnd(); ++it){
        castAndExportTache(stream, *it->second);
    }
}

void exportTacheComposite(QXmlStreamWriter& stream, const TacheComposite& tache) {
    stream.writeStartElement("TacheComposite");
    exportTache(stream, tache);
    for(TacheComposite::const_iterator it=tache.begin(); it!=tache.end(); ++it){
        castAndExportTache(stream, *it->second);
    }
    stream.writeEndElement();
}

void exportTacheSimpleNonPreemptive(QXmlStreamWriter& stream, const TacheSimpleNonPreemptive& tache) {
    stream.writeStartElement("TacheSimpleNonPreemptive");
    exportTache(stream, tache);
    stream.writeEndElement();
}

void exportTacheSimplePreemptive(QXmlStreamWriter& stream, const TacheSimplePreemptive& tache) {
    stream.writeStartElement("TachePreemptive");
    exportTache(stream, tache);
    stream.writeEndElement();
}

void castAndExportTache(QXmlStreamWriter& stream, Tache& tache) {
    const std::type_info& ti = typeid(tache);
    if(ti == typeid(TacheComposite)) {
        exportTacheComposite(stream, dynamic_cast<TacheComposite&>(tache));
    } else if(ti == typeid(TacheSimpleNonPreemptive)) {
        exportTacheSimpleNonPreemptive(stream, dynamic_cast<TacheSimpleNonPreemptive&>(tache));
    } else if (ti == typeid(TacheSimplePreemptive)) {
        exportTacheSimplePreemptive(stream, dynamic_cast<TacheSimplePreemptive&>(tache));
    } else {
        throw ToolsException("XmlParser erreur : type inconnu !");
    }
}

QString toQString(const std::string& str) {
    return QString::fromStdString(str);
}

std::string toString(const QString& str) {
    return str.toStdString();
}
