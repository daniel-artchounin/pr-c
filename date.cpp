#include <ctime>
#include <iomanip>
#include <sstream>
#include <QString>
#include "date.h"
#include "dateexception.h"

void Date::setDate(unsigned short int j, unsigned short int m, unsigned int a) {
    // initialisation de la date, renvoie vrai si la date est valide
    //if (a>=0&&a<=3000) annee=a;
    if (a<=3000) annee=a;
    else throw DateException("erreur: annee invalide");
    if (m>=1&&m<=12) mois=m;
    else throw DateException("erreur: mois invalide");
    switch(m) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (j>=1 && j<=31) jour=j;
        else throw DateException("erreur: jour invalide");
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (j>=1 && j<=30) jour=j;
        else throw DateException("erreur: jour invalide");
        break;
    case 2:
        if (j>=1 && (j<=29 || (j==30 && a%4==0))) jour=j;
        else throw DateException("erreur: jour invalide");
        break;
    }
}

void Date::setDateAujourdhui() {
    // initialisation de la date avec la date d'aujourd'hui
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    jour=timeinfo->tm_mday;
    mois=timeinfo->tm_mon+1;
    annee=timeinfo->tm_year+1900;
}

void Date::afficher(std::ostream& f) const {
    // affiche le date sous le format JJ/MM/AAAA
    f<<std::setfill('0')<<std::setw(2)<<jour<<"/"<<std::setw(2)<<mois<<"/"<<annee<<std::setfill(' ');
}

bool Date::operator==(const Date& d) const {
    if (annee<d.annee) return false;
    if (annee>d.annee) return false;
    if (mois<d.mois) return false;
    if (mois>d.mois) return false;
    if (jour<d.jour) return false;
    if (jour>d.jour) return false;
    return true;
}

bool Date::operator<(const Date& d) const {
    if (annee<d.annee) return true;
    if (annee>d.annee) return false;
    if (mois<d.mois) return true;
    if (mois>d.mois) return false;
    if (jour<d.jour) return true;
    if (jour>d.jour) return false;
    return false;
}

bool Date::operator>(const Date& d) const {
    return d<*this;
}

bool Date::operator<=(const Date& d) const {
    return !(d<*this);
}

bool Date::operator>=(const Date& d) const {
    return !(*this < d);
}

int operator-(const Date& d1, const Date&d2 ){
    int n=(d1.getAnnee()-d2.getAnnee())*365+(d1.getAnnee()-d2.getAnnee())/4;
    n+=int((d1.getMois()-d2.getMois())*30.5);
    n+=d1.getJour()-d2.getJour();
    return n;
}

Date Date::demain() const {
    Date d=*this;
    d.jour+=1;
    switch(d.mois) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (d.jour>31) {
            d.jour=1;
            d.mois++;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (d.jour>30) {
            d.jour=1;
            d.mois++;
        }
        break;
    case 2:
        if (d.jour>28 && d.annee%4>0) {
            d.jour=1;
            d.mois++;
        }
        if (d.jour>29) {
            d.jour=1;
            d.mois++;
        }
        break;
    }
    if (d.mois==13) {
        d.annee++;
        d.mois=1;
    }
    return d;
}

Date Date::operator+(unsigned int nb_jours) const {
    Date d=*this;
    while(nb_jours>0) {
        d=d.demain();
        nb_jours--;
    }
    return d;
}

std::string Date::formatAAAAMMJJ() const {
    std::stringstream ss;
    ss<<std::setfill('0')<<annee<<std::setw(2)<<mois<<std::setw(2)<<jour;
    return ss.str();
}

QString Date::toQString() const {
    std::stringstream ss;
    ss<<*this;
    return QString::fromStdString(ss.str());
}

Date Date::addDuree(const Duree duree) const{
    Date date = *this;
    return date+(duree.getHeure()/24);
}

std::ostream& operator<<(std::ostream& f, const Date& x) {
    x.afficher(f);
    return f;
}

std::istream& operator>>(std::istream& flot, Date& date) {
    unsigned int short j,m,a;
    bool ok=true;
    flot>>j;
    if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
    else ok=false;

    if (!flot) ok=false;

    if(flot.peek()=='/') {
        flot.ignore();
        flot>>m;
        if (!flot) ok=false;
    } else {
        ok=false;
    }
    if(flot.peek()=='/') {
        flot.ignore();
        flot>>a;
        if (!flot) ok=false;
    } else {
        ok=false;
    }

    if (ok) date=Date(j,m,a);
    else flot.clear(std::ios::failbit);
    return flot;
}
