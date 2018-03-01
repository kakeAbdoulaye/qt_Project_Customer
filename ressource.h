#pragma once
#ifndef RESSOURCE_H
#define RESSOURCE_H
#include <map>
#include <iostream>
using namespace std;


struct IntervalleHeure
{
    int HeureDebut;
    int HeureFin;
};

class Ressource
{
private:
    int idRessource;

    /*
        Structure de ma MAP :
        - cle : IntervalleHeure , pour la gestion de l'intervalle de temps
            - HeureDebut : qui represente l'heure de debut du rdv
            - HeureFin : qui represente l'heure de fin du rdv
            // Les heures sont en minute et au quart heure
        - Valeur : int : id du client
    */
    map<IntervalleHeure,int> listeRdv;

protected:
    int convertirQuart(int minute);
public:
    Ressource();
    Ressource(int idres);

    Ressource(const Ressource & ressource);
    ~Ressource();

    // Ajouter in id de patient avec le temps
    int ajouterClient(int dureeMinute, int debutPossible, int idClient);
    int getRESidressource() { return this->idRessource; }
    int insererRDV(int debutPossible, int duree, int idClient);

    void affichagePlanning();
};
bool operator<(const IntervalleHeure & s1, const IntervalleHeure & s2);
#endif // !RESSOURCE_H
