#pragma once
#ifndef  ADRESSE_H
#define ADRESSE_H
#include <iostream>
#include <QString>
using namespace std;


class Adresse
{
private:
    QString adrStrAdresse;
    qint32 adrEntCodePostale;
    QString adrStrVille;
public:
    Adresse();
    Adresse(QString strAdresse , QString strVille, qint32 EntCodePostale);
    Adresse(Adresse const& adresse);
    ~Adresse();



    QString getADRAdresse() { return adrStrAdresse; }
    QString getADRVille() { return adrStrVille; }
    qint32 getADRCodePostale() { return adrEntCodePostale; }

    void setADRAdresse(QString strAdresse) { adrStrAdresse = strAdresse; }
    void setADRVille(QString strVille) { adrStrVille = strVille; }
    void setADRCodePostale(qint32 EntCodePostale) { adrEntCodePostale = EntCodePostale; }

};
#endif
