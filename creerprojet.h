#ifndef CREERPROJET_H
#define CREERPROJET_H

#include <QWidget>
# include <QPushButton>
# include <QVBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QLineEdit>
# include "creerprojettache.h"

class CreerProjet : public CreerProjetTache
{
    Q_OBJECT
protected :

public:
    explicit CreerProjet(QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipaleValider();
};

#endif // CREERPROJET_H
