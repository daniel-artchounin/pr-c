#ifndef SUPPRIMERPRECEDENCE_H
#define SUPPRIMERPRECEDENCE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QPushButton>
# include "projet.h"
# include <QTreeWidget>
# include <QLabel>
# include "fenetreannulervalider.h"
# include "gestionprecedence.h"

class SupprimerPrecedence : public GestionPrecedence
{
    Q_OBJECT
public:
    explicit SupprimerPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
public slots:
    void retourFenetrePrincipaleValider();
};
#endif // SUPPRIMERPRECEDENCE_H
