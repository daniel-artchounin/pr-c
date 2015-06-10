#include "fenetreedt.h"
#include <QDate>
#include <string>
#include <QMenu>
#include "fenetreprincipale.h"
#include <QGraphicsRectItem>
#include "tools.h"
#include <QDebug>

FenetreEDT::FenetreEDT(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene;
    this->setScene(scene);
    creerActions();
    progRdv=0;
    progReunion=0;
    editProg=0;
    week=0;
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene->setSceneRect(0,0,width(),height());
}

void FenetreEDT::creerActions() {
    actionProgRendezVous = new QAction("Programmer un rendez-vous", this);
    connect(actionProgRendezVous, SIGNAL(triggered()), this, SLOT(programmerRendezVous()));
    actionProgReunion = new QAction("Programmer une réunion", this);
    connect(actionProgReunion, SIGNAL(triggered()), this, SLOT(programmerReunion()));
    actionEditProg = new QAction("Editer une programmation", this);
    connect(actionEditProg, SIGNAL(triggered()), this, SLOT(editerProgrammation()));
}

Date FenetreEDT::weekBegining() {
    QDate date = (QDate::currentDate()).addDays(7*week);
    int day = date.dayOfWeek();
    return Date(toString((date.addDays(1-day)).toString("dd/MM/yyyy")));
}

Date FenetreEDT::weekEnd() {
    QDate date = (QDate::currentDate()).addDays(7*week);
    int day = date.dayOfWeek();
    return Date(toString((date.addDays(7-day)).toString("dd/MM/yyyy")));
}

void FenetreEDT::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->setWorldMatrixEnabled(true);
    painter->setPen(QPen(Qt::gray));
    QFont font = painter->font();
    font.setPointSize(14);
    painter->setFont(font);

    QVarLengthArray<QLineF, 100> linesX;
    int day=1;
    for (qreal x = rect.left(); x < rect.right(); x += getWidthDay()) {
        if(day<=7) {
            drawText(*painter, QPointF(x+getWidthDay()/2.0, rect.top()+getHeightHour()), Qt::AlignHCenter, QDate::longDayName(day++));
        }
        linesX.append(QLineF(x, rect.top(), x, rect.bottom()));
    }

    font.setPointSize(8);
    painter->setFont(font);
    int heure=0;
    QVarLengthArray<QLineF, 100> linesY;
    for (qreal y = rect.top(); y < rect.bottom(); y += getHeightHour()) {
        if(heure<24) {
            painter->drawText(rect.left(), y+getHeightHour()*3/2, QString::number(heure++)+":00");
        }
        linesY.append(QLineF(rect.left(), y, rect.right(), y));
    }

    painter->drawLines(linesX.data(), linesX.size());
    painter->drawLines(linesY.data(), linesY.size());
}

void FenetreEDT::loadWeek() {
    scene->clear();
    ProgrammationManager& pgm = ProgrammationManager::getInstance();

    for(ProgrammationManager::iterator it = pgm.constraint_begin(weekBegining()); it!=pgm.constraint_end(weekEnd()); ++it) {
        drawProgrammation(it->second->getNom(), it->second->getDateProgrammation(), it->second->getHoraireProgrammation(), it->second->getDateFin(), it->second->getHoraireFin(), it->second->getDuree());
    }
    drawDates();
}

void FenetreEDT::drawProgrammation(std::string titre, Date ddebut, Horaire hdebut, Date dfin, Horaire hfin, Duree duree) {
    int x = toPositionX(ddebut);
    int y = toPositionY(hdebut);
    QBrush brush = QBrush(QColor(128, 128, 255, 128));
    QGraphicsRectItem *item;
    if(ddebut==dfin) {
        int height = toHeight(duree);
        item = scene->addRect(x,y,getWidthDay(),height,QPen(Qt::blue), brush);
        drawNames(titre,x,y);
    }else {
        scene->addRect(x,y,getWidthDay(),maxY()-minY(),QPen(Qt::blue),brush);
        drawNames(titre,x,y);
        Date next = ddebut.demain();
        int day = dayOfWeek(next);
        while(day<=7 && !(next==dfin)) {
            QGraphicsRectItem *item = scene->addRect(toPositionX(next),minY(),getWidthDay(),maxY(),QPen(Qt::blue),brush);
            item->setData(101, toQString(ddebut.toString()));
            item->setData(102, toQString(hdebut.toString()));
            drawNames(titre,toPositionX(next),minY());
            next = next.demain();
            day++;
        }
        if(day<=7 && next==dfin && !(hfin==Horaire(0,0))) {
            scene->addRect(toPositionX(next),minY(),getWidthDay(),(hfin.getHeure()+hfin.getMinute()/60.0)*getHeightHour(),QPen(Qt::blue),brush);
            drawNames(titre,toPositionX(next),minY());
        }
    }
    item->setData(101, toQString(ddebut.toString()));
    item->setData(102, toQString(hdebut.toString()));
}

void FenetreEDT::drawNames(std::string titre, int x, int y) {
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(x,y);
    QFont font(io->font());
    font.setPointSize(getWidthDay()*8/168);
    io->setFont(font);
    io->setPlainText(toQString(titre));
    scene->addItem(io);
}

void FenetreEDT::drawDates() {
    QGraphicsTextItem * io;
    Date date = weekBegining();
    for(int i=0; i<7; i++) {
        io = new QGraphicsTextItem;
        io->setPos(toPositionX(date),-5);
        QFont font(io->font());
        font.setPointSize(getWidthDay()*8/168);
        io->setFont(font);
        io->setPlainText(toQString(date.toString()));
        date=date.demain();
        scene->addItem(io);
    }
}

void FenetreEDT::drawText(QPainter & painter, const QPointF & point, int flags, const QString & text, QRectF * boundingRect) {
    const qreal size = 32767.0;
    QPointF corner(point.x(), point.y() - size);
    if (flags & Qt::AlignHCenter) corner.rx() -= size/2.0;
    else if (flags & Qt::AlignRight) corner.rx() -= size;
    if (flags & Qt::AlignVCenter) corner.ry() += size/2.0;
    else if (flags & Qt::AlignTop) corner.ry() += size;
    else flags |= Qt::AlignBottom;
    QRectF rect(corner, QSizeF(size, size));
    painter.drawText(rect, flags, text, boundingRect);
}

int FenetreEDT::getWidthDay() {
    return (rect().right() - rect().left())/7;
}

int FenetreEDT::getHeightHour() {
    return (rect().bottom() - rect().top())/25;
}

int FenetreEDT::toPositionX(const Date& date) {
    return rect().left()+(QDate::fromString(toQString(date.toString()),toQString("dd/MM/yyyy")).dayOfWeek()-1)*getWidthDay();
}

int FenetreEDT::toPositionY(const Horaire& horaire) {
    return minY()+(horaire.getHeure() + horaire.getMinute()/60.0)*getHeightHour();
}

int FenetreEDT::toHeight(const Duree& duree) {
    return duree.getDureeEnHeures()*getHeightHour();
}

int FenetreEDT::minX() {
    return rect().left();
}

int FenetreEDT::minY() {
    return rect().top()+getHeightHour();
}

int FenetreEDT::maxY() {
    return minY() + 25*getHeightHour();
}

int FenetreEDT::dayOfWeek(const Date& date) {
    return QDate::fromString(toQString(date.toString()),toQString("dd/MM/yyyy")).dayOfWeek();
}

void FenetreEDT::programmerRendezVous(){
    if(progRdv !=0){
        delete progRdv;
        progRdv = 0;
    }
    progRdv = new ProgrammerRendezVous;
    progRdv->show();
    masquerFenetrePrincipale();
}

void FenetreEDT::programmerReunion(){
    if(progReunion !=0){
        delete progReunion;
        progReunion = 0;
    }
    progReunion = new ProgrammerReunion;
    progReunion->show();
    masquerFenetrePrincipale();
}

void FenetreEDT::editerProgrammation(){
    if(editProg !=0){
        delete editProg;
        editProg = 0;
    }
    editProg = new EditerProgrammation;
    editProg->show();
    masquerFenetrePrincipale();
}

void FenetreEDT::masquerFenetrePrincipale() {
    FenetrePrincipale& fp = FenetrePrincipale::getInstance();
    fp.hide();
}

void FenetreEDT::contextMenuEvent(QContextMenuEvent *event) {
    event->accept();
    QMenu menu(this);
    menu.addAction(actionProgRendezVous);
    menu.addAction(actionProgReunion);
    menu.addAction(actionEditProg);
    menu.exec(event->globalPos());
}

void FenetreEDT::saveWeek(const QString& file) {
    saveContraintes(file,weekBegining(),weekEnd());
}
