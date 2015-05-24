#include "horaire.h"
#include <QString>
#include <sstream>

bool Horaire::operator<(const Horaire& h) const {
    if (heure<h.heure) return true;
    if (heure>h.heure) return false;
    if (minute<h.minute) return true;
    if (minute>h.minute) return false;
    return false;
}

bool Horaire::operator>(const Horaire& h) const {
    return h<*this;
}

bool Horaire::operator<=(const Horaire& h) const {
    return !(h<*this);
}

bool Horaire::operator>=(const Horaire& h) const {
    return !(*this < h);
}

std::string Horaire::formatHHMM() const {
    std::stringstream ss;
    ss<<std::setfill('0')<<std::setw(2)<<heure<<std::setfill('0')<<std::setw(2)<<minute;
    return ss.str();
}

QString Horaire::toQString() const {
    std::stringstream ss;
    ss<<*this;
    return QString::fromStdString(ss.str());
}

Horaire Horaire::addDuree(const Duree duree) const{
    Horaire horaire = *this;
    horaire.minute += duree.getMinute();
    horaire.heure += (duree.getHeure() + horaire.minute/60)%24;
    horaire.minute %=60;
    return horaire;
}

std::ostream& operator<<(std::ostream& f, const Horaire & h) {
    h.afficher(f);
    return f;
}
