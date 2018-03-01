#include "client.h"



Client::Client()
{
    patPersonne = Personne();
    patAdresse =  Adresse();
    patStrCommentaire = "";
    patEntDureeConsultation = 0;
    patEntPriorite = 0;
    //patVecIdenRessource = vector<int>(1);
}

Client::Client(Client const & client)
{
    patPersonne = client.patPersonne;
    patAdresse = client.patAdresse ;
    patStrCommentaire = client.patStrCommentaire;
    patEntDureeConsultation = client.patEntDureeConsultation;
    patEntPriorite = client.patEntPriorite;
    patVecIdenRessource = client.patVecIdenRessource;
}

Client::Client(Personne  personne, Adresse  adresse, int entDuree, int entPrio, string strCom)
{
    patPersonne = personne;
    patAdresse = adresse ;
    patStrCommentaire = strCom;
    patEntDureeConsultation = entDuree;
    patEntPriorite = entPrio;
    //patVecIdenRessource = vector<int>(1);
}


Client::~Client()
{

}

void Client::ajouterIdenRessource(int entNombre)
{
    this->patVecIdenRessource.push_back(entNombre);
}

void Client::supprimerIdenRessource(int entPosition)
{
    vector<int>::iterator myIterator;
    myIterator = this->patVecIdenRessource.begin() + entPosition;
    this->patVecIdenRessource.erase(myIterator);
}

int Client::getIdenRessource(int entPosition)
{
    vector<int>::iterator myIterator;
    myIterator = this->patVecIdenRessource.begin() + entPosition;
    return *myIterator;
}

void Client::viderListeIdenRessource()
{
    this->patVecIdenRessource.clear();
}

int Client::dureeParExamen()
{
    return patEntDureeConsultation / patVecIdenRessource.size();
}

void Client::afficheClient()
{


    patPersonne.perAffichePersonne();
    patAdresse.adrAfficheAdresse();
    cout << "Duree de la consultation : " << this->patEntDureeConsultation << endl;
    cout << "Priorite du Client : " << this->patEntPriorite << endl;
    cout << "Commentaire sur le Client : " << this->patStrCommentaire << endl;
    cout << "Nombre de Ressource demander : " << this->patVecIdenRessource.size() << endl;
    afficheRessource();
    cout << "-------------------------------------------------------------" << endl;
    cout << endl;
}

void Client::afficheRessource()
{
    vector <int> ::iterator it;
    cout << "Les Identifiants ressources : " << endl;
    for (it = patVecIdenRessource.begin(); it != patVecIdenRessource.end(); it++)
    {
        cout << "No Ressource : " << *it << endl;
    }
}

int Client::getIndicePriorite()
{
    int valeur1 = 0;
    valeur1 = (getPATPriorite() * 100) + (getNombreRessource() * 10) + getPATDureeConsultation();
    return valeur1 ;
}


