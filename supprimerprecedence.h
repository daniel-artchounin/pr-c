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
# include <QListWidget>
# include <QListWidgetItem>

class SupprimerPrecedence : public GestionPrecedence
{
    Q_OBJECT
protected :
    QListWidget* listeDeTaches;
    std::string* fromQStringListToStdStringArray(QStringList chemin, unsigned int* taille);
    void afficherListeTacheWidget();
public:
    explicit SupprimerPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
public slots:
    void retourFenetrePrincipaleValider();

};
#endif // SUPPRIMERPRECEDENCE_H
