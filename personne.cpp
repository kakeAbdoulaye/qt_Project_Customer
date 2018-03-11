#include "personne.h"



Personne::Personne()
{
    perStrNom = "";
    perStrPrenom = "";
    perEntTelephone = 0;
    perEntId = 0;
}

Personne::Personne(qint32 entId ,QString strNom, QString strPrenom, qint32 entTelephone)
{
    perEntId = entId;
    perStrNom = strNom;
    perStrPrenom = strPrenom;
    perEntTelephone = entTelephone;
}

Personne::Personne(Personne const & personne)
{
    perEntId = personne.perEntId;
    perStrNom = personne.perStrNom;
    perStrPrenom = personne.perStrPrenom;
    perEntTelephone = personne.perEntTelephone;
}


Personne::~Personne()
{
}


