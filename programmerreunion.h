#ifndef PROGRAMMERREUNION_H
#define PROGRAMMERREUNION_H

#include <QWidget>
#include "programmerevenement.h"

class ProgrammerReunion : public ProgrammerEvenement
{
    Q_OBJECT
public:
    explicit ProgrammerReunion(QWidget *parent = 0);

    explicit ProgrammerReunion(ProgrammationEvenement* prog, QWidget *parent = 0);
signals:

public slots:
    void retourFenetrePrincipaleValider();
};

#endif // PROGRAMMERREUNION_H
