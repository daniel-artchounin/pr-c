#ifndef CREERTACHECOMPOSITE_H
#define CREERTACHECOMPOSITE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QFormLayout>
# include <QLineEdit>
# include <QDateEdit>
# include <QPushButton>
# include <QCloseEvent>
# include "fenetreprincipale.h"
# include <QList>
# include <QString>
# include "creertache.h"

class CreerTacheComposite : public CreerTache
{
    Q_OBJECT

protected :

public:
    explicit CreerTacheComposite(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipaleValider();
};

#endif // CREERTACHECOMPOSITE_H
