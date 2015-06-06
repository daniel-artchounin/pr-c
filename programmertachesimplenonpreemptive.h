#ifndef PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
#define PROGRAMMERTACHESIMPLENONPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QPushButton>
# include <projet.h>
# include "programmertachesimple.h"
class ProgrammerTacheSimpleNonPreemptive : public ProgrammerTacheSimple
{
    Q_OBJECT
public:
    explicit ProgrammerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
signals:

public slots:
    void retourFenetrePrincipaleValider();
};

#endif // PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
