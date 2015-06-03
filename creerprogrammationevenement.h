#ifndef CREERPROGRAMMATIONEVENEMENT_H
#define CREERPROGRAMMATIONEVENEMENT_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CreerProgrammationEvenement: public QWidget
{
    Q_OBJECT
protected :

private :
    QFormLayout* formlayout;
    QLineEdit* nom; /*!< nom de l'évènement */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QSpinBox* duree; /*!< duree */
    QPushButton* valider;  /*!< bouton valider */
    QPushButton* annuler;  /*!< bouton annuler */
    QHBoxLayout* hBox;
    QVBoxLayout* vBox;
public:
    explicit CreerProgrammationEvenement(QWidget *parent = 0);

signals:

public slots:
    void closeEvent(QCloseEvent *event);
    void programmer();
    void quitter();
};

#endif // CREERPROGRAMMATIONEVENEMENT_H
