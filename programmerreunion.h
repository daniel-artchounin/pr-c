#ifndef PROGRAMMERREUNION_H
#define PROGRAMMERREUNION_H

#include <QWidget>
#include "programmerevenement.h"

class ProgrammerReunion : public ProgrammerEvenement
{
    Q_OBJECT
public:
    explicit ProgrammerReunion(QWidget *parent = 0);

signals:

public slots:
    virtual void retourFenetrePrincipaleValider();
};

#endif // PROGRAMMERREUNION_H
