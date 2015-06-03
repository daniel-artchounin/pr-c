#include "fenetreedt.h"
#include <QDate>
#include <string>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include "fenetreprincipale.h"

FenetreEDT::FenetreEDT(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene;
    this->setScene(scene);
    creerActions();
    creerProgEvt=0;
    week=0;
}

void FenetreEDT::creerActions() {
    progEvt = new QAction(tr("Programmer un évènement"), this);
    progEvt->setShortcuts(QKeySequence::Cut);
    progEvt->setStatusTip(tr("Permet de programmer un évènement"));
    connect(progEvt, SIGNAL(triggered()), this, SLOT(creerProgrammationEvenement()));
}

Date FenetreEDT::weekBegining(const QDate& date) {
    int day = date.dayOfWeek();
    return Date(toString((date.addDays(1-day)).toString("dd/MM/yyyy")));
}

Date FenetreEDT::weekEnd(const QDate& date) {
    int day = date.dayOfWeek();
    return Date(toString((date.addDays(7-day)).toString("dd/MM/yyyy")));
}

void FenetreEDT::drawForeground(QPainter* painter, const QRectF& rect)
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
    loadWeek((QDate::currentDate()).addDays(7*week));
}

void FenetreEDT::loadWeek(const QDate& date) {
    ProgrammationManager& pgm = ProgrammationManager::getInstance();

    for(ProgrammationManager::iterator it = pgm.constraint_begin(weekBegining(date)); it!=pgm.constraint_end(weekEnd(date)); ++it) {
        drawProgrammation(it->second->getDateProgrammation(), it->second->getHoraireProgrammation(), it->second->getDateFin(), it->second->getHoraireFin(), it->second->getDuree(), QBrush(QColor(128, 128, 255, 128)));
    }
}

void FenetreEDT::drawProgrammation(Date ddebut, Horaire hdebut, Date dfin, Horaire hfin, Duree duree, QBrush brush) {
    int x = toPositionX(ddebut);
    int y = toPositionY(hdebut);
    int height = toHeight(duree);

    QPainter painter(this->viewport());
    painter.setWorldMatrixEnabled(true);

    if(ddebut==dfin) {
        painter.fillRect(x,y,getWidthDay(),height,brush);
    }else {
        painter.fillRect(x,y,getWidthDay(),maxY()-minY(),brush);
        Date next = ddebut.demain();
        int day = toDay(next);
        while(day<=7 && !(next==dfin)) {
            painter.fillRect(toPositionX(next),minY(),getWidthDay(),maxY(),brush);
            next = next.demain();
            day++;
        }
        if(day<=7) {
            painter.fillRect(toPositionX(next),minY(),getWidthDay(),(hfin.getHeure()+hfin.getMinute()/60.0)*getHeightHour(),brush);
        }
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
    return rect().left()+(QDate::fromString(toQString(date.toString()),toQString("dd/MM/yyyy")).day()-1)*getWidthDay();
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

int FenetreEDT::toDay(const Date& date) {
    return QDate::fromString(toQString(date.toString()),toQString("dd/MM/yyyy")).day();
}

void FenetreEDT::creerProgrammationEvenement(){
    if(creerProgEvt !=0){
        delete creerProgEvt;
        creerProgEvt = 0;
    }
    creerProgEvt = new CreerProgrammationEvenement;
    creerProgEvt->show();
    FenetrePrincipale& fp = FenetrePrincipale::getInstance();
    fp.hide();
}

void FenetreEDT::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction(progEvt);
    menu.exec(event->globalPos());
}
