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

class CreerTacheComposite : public QWidget
{
    Q_OBJECT
protected :
    virtual void closeEvent(QCloseEvent *event);
private :
    Projet& nomProjet;
    std::string * chemin;
    unsigned int* tailleChemin;
    QVBoxLayout* vBox;
    QHBoxLayout* hBox;
    QFormLayout* formlayout;
    QLineEdit* titre; /*!< titre de l'élément */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QDateEdit* dateFin; /*!< date de fin */
    QTimeEdit* horaireFin; /*!< horaire de fin */
    QPushButton* annuler;  /*!< bouton annuler */
    QPushButton* sauver;  /*!< bouton sauver */
public:
    explicit CreerTacheComposite(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipaleAnnuler();
    void retourFenetrePrincipaleSauver();
};

#endif // CREERTACHECOMPOSITE_H
