#pragma once
#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <QString>

using namespace std;

class Personne
{
private :
    qint32 perEntId;
    QString perStrNom;
    QString perStrPrenom;
    qint32 perEntTelephone;


public:
    Personne();
    Personne(qint32 entId ,QString strNom, QString strPrenom, qint32 entTelephone);
    Personne(qint32 entId ,QString strNom, QString strPrenom);
    Personne(Personne const& personne);
    ~Personne();

    QString getPERNom() { return perStrNom; }
    QString getPERPrenom() { return perStrPrenom; }
    qint32 getPERTelephone() { return perEntTelephone; }
    qint32 getPERID() { return perEntId; }

    void setPERNom(QString strNom) {  perStrNom = strNom; }
    void setPERPrenom(QString strPrenom) { perStrPrenom = strPrenom; }
    void setPERTelephone(qint32 entTelephone) { perEntTelephone = entTelephone; }
    void setPERID(qint32 entId) {  perEntId = entId; }
};

#endif // !PERSONNE_H
