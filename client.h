#pragma once

#ifndef Client_H
#define Client_H

#include <string>
#include <vector>
#include "Adresse.h"
#include "Personne.h"

using namespace std;

class Client
{

private:
    Personne  patPersonne;
    Adresse  patAdresse;
    string patStrCommentaire;
    int patEntDureeConsultation;
    int patEntPriorite;
    vector<int> patVecIdenRessource;

public:
    Client();
    Client(Client const& Client);
    Client(Personne  personne, Adresse adresse , int entDuree , int entPrio , string strCom);

    ~Client();

    Personne getPATPersonne() { return patPersonne; }
    Adresse getPATAdresse() { return patAdresse; }
    string getPATCommentaire() { return patStrCommentaire; }
    int getPATDureeConsultation() { return patEntDureeConsultation; }
    int getPATPriorite() { return this->patEntPriorite; }
    int getNombreRessource() { return this->patVecIdenRessource.size(); }
    vector<int> getPATVecRessource() { return this->patVecIdenRessource; }

    void ajouterIdenRessource(int entIDNombre);
    void supprimerIdenRessource(int entPosition);
    int getIdenRessource(int entPosition);
    void viderListeIdenRessource();
    int dureeParExamen();
    void afficheClient();
    void afficheRessource();
    int  getIndicePriorite();

    //Mettre la duree au quart heure
    void setPATPersonne(Personne  perPersone) { patPersonne = perPersone ; }
    void setPATAdresse(Adresse  adrAdresse) {  patAdresse = adrAdresse ; }
    void setPATCommentaire(string strCom) { patStrCommentaire = strCom; }
    void setPATDureeConsultation(int entHeureC) {  patEntDureeConsultation = entHeureC; }
    void setPATPriorite(int entPriorite) { patEntPriorite = entPriorite ; }
    void setPATVecRessource(vector<int> vec) { this->patVecIdenRessource = vec ; }

};


#endif // !Client_H
