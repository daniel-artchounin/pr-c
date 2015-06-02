#ifndef FENETREGESTIONPROJET_H
#define FENETREGESTIONPROJET_H

#include <QWidget>
# include <projetmanager.h>
# include <QTreeWidget>
# include <QHBoxLayout>
# include <QMenu>

class FenetreGestionProjet : public QWidget
{
    Q_OBJECT
private:
    QTreeWidget * tree;
    QHBoxLayout* hBox;
    QAction * monAction;
public:
    explicit FenetreGestionProjet(QWidget *parent = 0);
    void afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel=0, Element * element=0);
    QTreeWidget* getTree()const{
        return tree;
    }
signals:

public slots:
    void showContextMenu(const QPoint&);
    void test();


};

#endif // FENETREGESTIONPROJET_H
