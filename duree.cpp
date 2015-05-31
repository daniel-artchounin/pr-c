#include "duree.h"
#include <sstream>

void Duree::setDuree(std::string duree) {
    std::istringstream iss(duree);
    iss>>*this;
}

std::string Duree::toString() const {
    std::stringstream ss;
    ss<<*this;
    return ss.str();
}

std::ostream& operator<<(std::ostream& f, const Duree & d) {
    d.afficher(f);
    return f;
}

std::istream& operator>>(std::istream& flot, Duree& duree) {
    unsigned int h,m;
    bool ok=true;
    flot>>h;
    if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
    else ok=false;

    if (!flot) ok=false;

    if(flot.peek()=='H') {
        flot.ignore();
        flot>>m;
        if (!flot) ok=false;
    } else {
        ok=false;
    }
    if (ok) duree=Duree(h,m);
    else flot.clear(std::ios::failbit);
    return flot;
}

bool operator<(const Duree& a, const Duree&b){
    return a.estPlusPetitQue(b);
}

bool operator>(const Duree& a, const Duree&b){
    return b.estPlusPetitQue(a);
}

bool operator<=(const Duree& a, const Duree&b){
    return !b.estPlusPetitQue(a);
}

bool operator>=(const Duree& a, const Duree&b){
    return !a.estPlusPetitQue(b);
}

Duree operator+(const Duree& duree1, const Duree& duree2){
    return duree1.addition(duree2);

}
