#pragma once
#ifndef RESSOURCE_H
#define RESSOURCE_H
#include <map>
#include <iostream>
#include "personne.h"
using namespace std;


struct IntervalleHeure
{
    int HeureDebut;
    int HeureFin;
};

class Ressource : public Personne
{
    /*
        Structure de ma MAP :
        - cle : IntervalleHeure , pour la gestion de l'intervalle de temps
            - HeureDebut : qui represente l'heure de debut du rdv
            - HeureFin : qui represente l'heure de fin du rdv
            // Les heures sont en minute et au quart heure
        - Valeur : int : id du client
    */
    map<IntervalleHeure,int> listeRdv;

private:
    QString login ;
    QString motPasse;

protected:
    int convertirQuart(int minute);
public:
    Ressource();
    Ressource(qint32 entId ,QString strNom, QString strPrenom);
    Ressource(qint32 entId ,QString strNom, QString strPrenom,QString log , QString mdp);

    Ressource(const Ressource & ressource);
    ~Ressource();

    // Ajouter in id de patient avec le temps
    int ajouterClient(int dureeMinute, int debutPossible, int idClient);
    int insererRDV(int debutPossible, int duree, int idClient);
    QString getLogin(){return login;}
    QString getMotPasse(){return motPasse;}

     void setLogin(QString logi) {login = logi;}
    void setMotPasse(QString mdp){motPasse = mdp;}

    void affichagePlanning();
};
bool operator<(const IntervalleHeure & s1, const IntervalleHeure & s2);
#endif // !RESSOURCE_H
