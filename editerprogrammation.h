#ifndef MODIFIERPROGRAMMATIONEVENEMENT_H
#define MODIFIERPROGRAMMATIONEVENEMENT_H

#include <QListWidget>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include "fenetreannulervalider.h"

class EditerProgrammation : public QWidget {
    Q_OBJECT

protected :

    QListWidget* list;
    QHBoxLayout* hBox;
    QHBoxLayout* hBoxButton;
    QVBoxLayout* vBox;
    QPushButton* select;
    QPushButton* suppr;
    FenetreAnnulerValider* form;

public:

    explicit EditerProgrammation(QWidget *parent = 0);
    void updateListe();

signals:

public slots:

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget
     * \param event évènement
     */
    void closeEvent(QCloseEvent *event);

    void selectionner();

    void supprimer();
};

#endif // MODIFIERPROGRAMMATIONEVENEMENT_H
