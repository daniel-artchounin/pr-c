#include "evenement.h"
#include "tools.h"

Evenement::~Evenement(){}

void Evenement::exportTo(QXmlStreamWriter& stream) {
    stream.writeTextElement("nom",toQString(nom));
    stream.writeTextElement("lieu",toQString(lieu));
    stream.writeTextElement("motif",toQString(motif));
}
