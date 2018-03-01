#include "adresse.h"



Adresse::Adresse()
{
    adrStrAdresse = "";
    adrStrVille = "";
    adrEntCodePostale = 0;
}

Adresse::Adresse(string strAdresse, string strVille, int EntCodePostale)
{
    adrStrAdresse = strAdresse;
    adrStrVille = strVille;
    adrEntCodePostale = EntCodePostale;
}

Adresse::Adresse(Adresse const & adresse)
{
    adrStrAdresse = adresse.adrStrAdresse;
    adrStrVille = adresse.adrStrVille;
    adrEntCodePostale = adresse.adrEntCodePostale;
}


Adresse::~Adresse()
{
}

void Adresse::adrAfficheAdresse()
{
    cout << "Adresse Patient" << endl;
    cout << "Libelle : " << this->adrStrAdresse << endl;
    cout << "Ville : " << this->adrStrVille << endl;
    cout << "Code Postale : " << this->adrEntCodePostale << endl;
    cout << "-------------------------------------------------------------" << endl;
}
