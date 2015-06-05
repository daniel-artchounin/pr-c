#include "tools.h"
#include <QFile>
#include "toolsexception.h"
#include <QXmlStreamWriter>
#include "projetmanager.h"
#include "programmationmanager.h"
#include <vector>
#include "tachecompositeexception.h"

void save(const QString& file){
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw ToolsException("XmlParser erreur : impossible d'ouvrir le fichier !");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("root");
    ProjetManager::getInstance().exportTo(stream);
    ProgrammationManager::getInstance().exportTo(stream);
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void saveContraintes(const QString& file, const Date& dateDebut, const Date& dateFin) {
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw ToolsException("XmlParser erreur : impossible d'ouvrir le fichier !");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    ProgrammationManager::getInstance().exportContraintes(stream,dateDebut,dateFin);
    stream.writeEndDocument();
    newfile.close();
}

void saveProjet(const QString& file, const Projet& projet) {
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw ToolsException("XmlParser erreur : impossible d'ouvrir le fichier !");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    projet.exportTo(stream);
    stream.writeEndDocument();
    newfile.close();
}

void load(const QString &file) {
    QFile oldFile(file);
    if (!oldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw ToolsException("Erreur ouverture fichier");
    }
    QXmlStreamReader xml(&oldFile);

    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "root") continue;
            if(xml.name() == "ProjetManager") {
                ProjetManager::getInstance().loadFrom(xml);
            }
            if(xml.name() == "ProgrammationManager") {
                ProgrammationManager::getInstance().loadFrom(xml);
            }
        }
    }
    ProgrammationManager& pgm = ProgrammationManager::getInstance();
    ProjetManager& pm = ProjetManager::getInstance();
    if(xml.hasError()) {
        throw ToolsException("Erreur lecteur fichier taches, parser xml. " + toString(xml.errorString()));
    }
    xml.clear();
}

QString toQString(const std::string& str) {
    return QString::fromStdString(str);
}

QString toQString(const int entier) {
    return QString::number(entier);
}

std::string toString(const QString& str) {
    return str.toStdString();
}
