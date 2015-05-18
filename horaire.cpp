#include "horaire.h"
#include <QString>
#include <sstream>

bool Horaire::operator<(const Horaire& h) const {
    if (heure<h.heure) return true;
    if (heure>h.heure) return false;
    if (minute<h.minute) return true;
    if (minute>h.minute) return false;
    return true;
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

QString Horaire::toQString() const {
    std::stringstream ss;
    ss<<*this;
    return QString::fromStdString(ss.str());
}

std::ostream& operator<<(std::ostream& f, const Horaire & h) {
    h.afficher(f);
    return f;
}
