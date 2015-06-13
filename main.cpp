# include <QApplication>
# include <QPushButton>
# include <projetmanager.h>
# include <programmationmanager.h>
# include <string>
# include <fenetreprincipale.h>
# include "tools.h"
# include <QIcon>
# include <QCoreApplication>

int main(int argc, char * argv[]){
    QApplication myApp(argc, argv);
    QApplication::setWindowIcon(QIcon("../pr-c/images/application.png"));
    FenetrePrincipale& fenetrePrincipale = FenetrePrincipale::getInstance();
    fenetrePrincipale.showMaximized();
    QCoreApplication::setApplicationName("ProjectCalendar");
    return myApp.exec();
}
