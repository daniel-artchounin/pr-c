#ifndef AJOUTERPRECEDENCE_H
#define AJOUTERPRECEDENCE_H

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
# include <QCloseEvent>
# include "fenetreannulervalider.h"
# include "gestionprecedence.h"

class AjouterPrecedence : public GestionPrecedence
{
    Q_OBJECT
protected:
    QTreeWidget * tree; // le tree-view
    void afficherTreeWidget(QTreeWidget* arbre, Element* element, QTreeWidgetItem * actuel=0);
public:
    static void removeProjet(QList<QString>* chemin);
    explicit AjouterPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
signals:
public slots:
    void retourFenetrePrincipaleValider();
};

#endif // AJOUTERPRECEDENCE_H
