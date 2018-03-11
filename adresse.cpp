#include "adresse.h"



Adresse::Adresse()
{
    adrStrAdresse = "";
    adrStrVille = "";
    adrEntCodePostale = 0;
}

Adresse::Adresse(QString strAdresse, QString strVille, qint32 EntCodePostale)
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

