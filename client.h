#pragma once

#ifndef Client_H
#define Client_H

#include <QVector>
#include <QString>
#include<QTime>
#include "Adresse.h"
#include "Personne.h"

using namespace std;

class Client
{

private:
    Personne  patPersonne;
    Adresse  patAdresse;
    QString patStrCommentaire;
    qint32 patEntDureeConsultation;
    qint32 patEntPriorite;
    QVector<qint32> patVecIdenRessource;

public:
    Client();
    Client(Client const& Client);
    Client(Personne  personne, Adresse adresse , int entDuree , int entPrio , QString strCom);

    Client(Personne  personne, Adresse adresse ,QTime duree, int entPrio , QString strCom);
    ~Client();

    Personne getPATPersonne() { return patPersonne; }
    Adresse getPATAdresse() { return patAdresse; }
    QString getPATCommentaire() { return patStrCommentaire; }
    qint32 getPATDureeConsultation() { return patEntDureeConsultation; }
    qint32 getPATPriorite() { return this->patEntPriorite; }
    qint32 getNombreRessource() { return this->patVecIdenRessource.size(); }
    QVector<qint32> getPATVecRessource() { return this->patVecIdenRessource; }

    void ajouterIdenRessource(qint32 entIDNombre);
    void supprimerIdenRessource(qint32 entPosition);
    int getIdenRessource(qint32 entPosition);
    void viderListeIdenRessource();
    int dureeParExamen();
    qint32  getIndicePriorite();
    bool verifieChamp();
    qint32 convertirTime(QTime Duree);

    //Mettre la duree au quart heure
    void setPATPersonne(Personne  perPersone) { patPersonne = perPersone ; }
    void setPATAdresse(Adresse  adrAdresse) {  patAdresse = adrAdresse ; }
    void setPATCommentaire(QString strCom) { patStrCommentaire = strCom; }
    void setPATDureeConsultation(qint32 entHeureC) {  patEntDureeConsultation = entHeureC; }
    void setPATPriorite(qint32 entPriorite) { patEntPriorite = entPriorite ; }
    void setPATVecRessource(QVector<qint32> vec) { this->patVecIdenRessource = vec ; }

};


#endif // !Client_H
