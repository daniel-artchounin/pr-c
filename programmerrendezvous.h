#ifndef PROGRAMMERRENDEZVOUS_H
#define PROGRAMMERRENDEZVOUS_H

#include <QWidget>
#include "programmerevenement.h"

class ProgrammerRendezVous : public ProgrammerEvenement
{
    Q_OBJECT
public:
    explicit ProgrammerRendezVous(QWidget *parent = 0);
    explicit ProgrammerRendezVous(ProgrammationEvenement* prog, QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipaleValider();
};

#endif // PROGRAMMERRENDEZVOUS_H
