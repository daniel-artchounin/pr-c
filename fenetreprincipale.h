#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QtWidgets>
#include "zonecentrale.h"

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
private:
    ZoneCentrale* zoneCentrale;
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QToolBar *barrreOutils;
public:
    explicit FenetrePrincipale(QWidget *parent = 0);

signals:

public slots:

};

#endif // FENETREPRINCIPALE_H
