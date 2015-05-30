#include "tools.h"
#include <QFile>
#include "toolsexception.h"
#include <QXmlStreamWriter>
#include "projetmanager.h"

void save(const QString& file){
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw ToolsException("XmlParser erreur : impossible d'ouvrir le fichier !");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    ProjetManager::getInstance().exportTo(stream);
    stream.writeEndDocument();
    newfile.close();
}

QString toQString(const std::string& str) {
    return QString::fromStdString(str);
}

std::string toString(const QString& str) {
    return str.toStdString();
}
