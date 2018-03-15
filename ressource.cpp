#include "ressource.h"

Ressource::Ressource()
{
}

Ressource::Ressource(qint32 entId ,QString strNom, QString strPrenom):Personne(entId ,strNom,strPrenom)
{
    login="";
    motPasse="";
}
Ressource::Ressource(qint32 entId ,QString strNom, QString strPrenom,QString log , QString mdp):Personne(entId ,strNom,strPrenom)
{
    login=log;
    motPasse=mdp;
}

Ressource::Ressource(const Ressource & ressource):Personne(ressource)
{
    login=ressource.login;
    motPasse=ressource.motPasse;
    this->listeRdv = ressource.listeRdv;
}


Ressource::~Ressource()
{
}

int Ressource::convertirQuart(int minute)
{
    int valeur = minute;
    int resultat = 0;
    int minutequart = valeur % 15;

    if (minutequart > 0 && minutequart <= 15)
    {
        resultat = 15 - minutequart;
        valeur = valeur + resultat;
    }
    else if (minutequart > 15 && minutequart <= 30)
    {
        resultat = 30 - minutequart;
        valeur = valeur + resultat;
    }
    else if (minutequart >30)
    {
        resultat = 15 - minutequart;
        valeur = valeur + resultat;
    }
    else
    {

    }

    return valeur;
}

int Ressource::ajouterClient(int dureeMinute,int debutPossible, int idClient)
{
    int quartDureeMinute = convertirQuart(dureeMinute);
    int quartDebutPossible = convertirQuart(debutPossible);
    int calculProchainDebutPossible = -1;
    map<IntervalleHeure, int>::iterator it;
    map<IntervalleHeure, int>::iterator it2;
    bool place = false; // il n'est pas placé
    int espace;

    if (this->listeRdv.size() == 0)
    {
        calculProchainDebutPossible = this->insererRDV(debutPossible, dureeMinute, idClient);
    }
    else
    {
        it = this->listeRdv.begin();
        IntervalleHeure interval1 = it->first;
        espace = interval1.HeureDebut - 0;
        if (espace >= quartDureeMinute)
        {
            if (0 <= quartDebutPossible)
            {
                if (interval1.HeureDebut >= quartDebutPossible + quartDureeMinute)
                {
                    calculProchainDebutPossible = this->insererRDV(debutPossible, dureeMinute, idClient);
                    place = true;
                }
            }
        }
        if (place == false)
        {

            for (it = this->listeRdv.begin(); it != this->listeRdv.end(); it++)
            {
                IntervalleHeure interval1 = it->first;
                it2 = it;
                it2++;
                if (it2 != this->listeRdv.end())
                {
                    IntervalleHeure interval2 = it2->first;

                    espace = interval2.HeureDebut - interval1.HeureFin;

                    if (espace >= quartDureeMinute)
                    {
                        if (interval1.HeureFin <= quartDebutPossible)
                        {
                            if (interval2.HeureDebut >= quartDebutPossible + quartDureeMinute)
                            {
                                calculProchainDebutPossible = this->insererRDV(debutPossible, dureeMinute, idClient);
                                place = true;
                            }
                        }
                        else
                        {
                            if (interval2.HeureDebut >= interval1.HeureFin + quartDureeMinute)
                            {
                                calculProchainDebutPossible = this->insererRDV(interval1.HeureFin, dureeMinute, idClient);
                                place = true;
                            }
                        }


                    }

                }
            }
            if (place == false)
            {
                it = --this->listeRdv.end();
                IntervalleHeure interval1 = it->first;
                calculProchainDebutPossible = this->insererRDV(interval1.HeureFin, dureeMinute, idClient);

            }
        }

    }
    return calculProchainDebutPossible;
}

int Ressource::insererRDV(int debutPossible, int duree, int idClient)
{
    IntervalleHeure newInterval;
    newInterval.HeureDebut = convertirQuart(debutPossible);
    newInterval.HeureFin = convertirQuart(debutPossible + duree);
    this->listeRdv[newInterval] = idClient;
    return newInterval.HeureFin;
}

void Ressource::affichagePlanning()
{
    map<IntervalleHeure, int>::iterator it;
    cout << "Ressource No :  " << this->getPERID() << "  --->   ";
    for (it = this->listeRdv.begin(); it != this->listeRdv.end(); it++)
    {
        IntervalleHeure interval = it->first;
        cout << interval.HeureDebut << " - " << interval.HeureFin << " : " << it->second << "  -  " ;
    }
    cout << endl;
}

bool operator<(const IntervalleHeure & s1, const IntervalleHeure & s2)
{
    return s1.HeureDebut < s2.HeureDebut && s1.HeureFin < s2.HeureFin;
}
