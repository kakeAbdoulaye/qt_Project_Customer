#pragma once
#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <string>

using namespace std;

class Personne
{
private :
    int perEntId;
    string perStrNom;
    string perStrPrenom;
    int perEntTelephone;


public:
    Personne();
    Personne(int entId ,string strNom, string strPrenom, int entTelephone);
    Personne(Personne const& personne);
    ~Personne();


    void perAffichePersonne();

    string getPERNom() { return perStrNom; }
    string getPERPrenom() { return perStrPrenom; }
    int getPERTelephone() { return perEntTelephone; }
    int getPERID() { return perEntId; }

    void setPERNom(string strNom) {  perStrNom = strNom; }
    void setPERPrenom(string strPrenom) { perStrPrenom = strPrenom; }
    void setPERTelephone(int entTelephone) { perEntTelephone = entTelephone; }
    void setPERID(int entId) {  perEntId = entId; }
};

#endif // !PERSONNE_H
