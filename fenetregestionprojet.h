#ifndef FENETREGESTIONPROJET_H
#define FENETREGESTIONPROJET_H

#include <QWidget>
# include <projetmanager.h>
# include <QTreeWidget>
# include <QHBoxLayout>

class FenetreGestionProjet : public QWidget
{
    Q_OBJECT
private:
    QTreeWidget * tree;
    QHBoxLayout* hBox;
public:
    explicit FenetreGestionProjet(QWidget *parent = 0);
    void afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel=0, Element * element=0);

signals:

public slots:

};

#endif // FENETREGESTIONPROJET_H
