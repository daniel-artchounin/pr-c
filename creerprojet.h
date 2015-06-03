#ifndef CREERPROJET_H
#define CREERPROJET_H

#include <QWidget>
# include <QPushButton>
# include <QVBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QLineEdit>

class CreerProjet : public QWidget
{
    Q_OBJECT
protected :
    virtual void closeEvent(QCloseEvent *event);
private :
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
    explicit CreerProjet(QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipaleAnnuler();
    void retourFenetrePrincipaleSauver();
};

#endif // CREERPROJET_H
