#pragma once
#ifndef  ADRESSE_H
#define ADRESSE_H
#include <iostream>
#include <string>
using namespace std;


class Adresse
{
private:
    string adrStrAdresse;
    int adrEntCodePostale;
    string adrStrVille;
public:
    Adresse();
    Adresse(string strAdresse , string strVille, int EntCodePostale);
    Adresse(Adresse const& adresse);
    ~Adresse();


    void adrAfficheAdresse();


    string getADRAdresse() { return adrStrAdresse; }
    string getADRVille() { return adrStrVille; }
    int getADRCodePostale() { return adrEntCodePostale; }

    void setADRAdresse(string strAdresse) { adrStrAdresse = strAdresse; }
    void setADRVille(string strVille) { adrStrVille = strVille; }
    void setADRCodePostale(int EntCodePostale) { adrEntCodePostale = EntCodePostale; }

};
#endif
