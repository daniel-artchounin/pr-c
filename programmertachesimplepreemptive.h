#ifndef PROGRAMMERTACHESIMPLEPREEMPTIVE_H
#define PROGRAMMERTACHESIMPLEPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QSpinBox>
# include <QFormLayout>
# include <QPushButton>
# include "projet.h"
# include "programmertachesimple.h"

class ProgrammerTacheSimplePreemptive : public ProgrammerTacheSimple
{
    Q_OBJECT
protected :
    QSpinBox * pourcentage;
public:
    explicit ProgrammerTacheSimplePreemptive(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
signals:

public slots:
    void retourFenetrePrincipaleValider();
};

#endif // PROGRAMMERTACHESIMPLEPREEMPTIVE_H
