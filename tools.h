#ifndef TOOLS_H
#define TOOLS_H
#include <QString>

void save(const QString &file);
void load(const QString &file);

QString toQString(const std::string &str);
std::string toString(const QString &str);

#endif // TOOLS_H
