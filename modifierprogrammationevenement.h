#ifndef MODIFIERPROGRAMMATIONEVENEMENT_H
#define MODIFIERPROGRAMMATIONEVENEMENT_H

#include <QListWidget>
#include <QHBoxLayout>
#include "programmationevenement.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include "programmerevenement.h"

class ModifierProgrammationEvenement : public QWidget {
    Q_OBJECT
protected :
    QListWidget* list;
    QHBoxLayout* hBox;
    QVBoxLayout* vBox;
    QPushButton* select;
    ProgrammerEvenement* form;

    void initialiseListe();
public:
    explicit ModifierProgrammationEvenement(QWidget *parent = 0);

signals:

public slots:
    void closeEvent(QCloseEvent *event);

    void quitter();

    void selectionner();
};

#endif // MODIFIERPROGRAMMATIONEVENEMENT_H
