#include "personne.h"



Personne::Personne()
{
    perStrNom = "";
    perStrPrenom = "";
    perEntTelephone = 0;
    perEntId = 0;
}

Personne::Personne(int entId ,string strNom, string strPrenom, int entTelephone)
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

void Personne::perAffichePersonne()
{
    cout << "Identifiant : " << perEntId << endl;
    cout << "Nom : " << this->perStrNom << endl;
    cout << "PreNom : " << this->perStrPrenom << endl;
    cout << "Num Tel  : " << this->perEntTelephone << endl;
    cout << "-------------------------------------------------------------" << endl;
}
