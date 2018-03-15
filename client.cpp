#include "client.h"



Client::Client():Personne()
{
    patAdresse =  Adresse();
    patStrCommentaire = "";
    patEntDureeConsultation = 0;
    patEntPriorite = 0;
}

Client::Client(Client const & client):Personne(client)
{
    patAdresse = client.patAdresse ;
    patStrCommentaire = client.patStrCommentaire;
    patEntDureeConsultation = client.patEntDureeConsultation;
    patEntPriorite = client.patEntPriorite;
    patVecIdenRessource = client.patVecIdenRessource;
}

Client::Client(qint32 entId ,QString strNom, QString strPrenom, qint32 entTelephone, Adresse  adresse, qint32 entDuree, qint32 entPrio, QString strCom)
    :Personne(entId ,strNom,strPrenom,entTelephone)
{
    patAdresse = adresse ;
    patStrCommentaire = strCom;
    patEntDureeConsultation = entDuree;
    patEntPriorite = entPrio;
}
Client::Client(qint32 entId ,QString strNom, QString strPrenom, qint32 entTelephone, Adresse  adresse, QTime Duree, qint32 entPrio, QString strCom)
    :Personne(entId ,strNom,strPrenom,entTelephone)
{
    patAdresse = adresse ;
    patStrCommentaire = strCom;
    patEntDureeConsultation = convertirTime(Duree);
    patEntPriorite = entPrio;
}
qint32 Client::convertirTime(QTime Duree)
{
    qint64 heure = Duree.hour();
    qint64 minute = Duree.minute();
    return heure*60+minute;
}
Client::~Client()
{

}

void Client::ajouterIdenRessource(qint32 entNombre)
{
    this->patVecIdenRessource.push_back(entNombre);
}

void Client::supprimerIdenRessource(qint32 entPosition)
{
    QVector<qint32>::iterator myIterator;
    myIterator = this->patVecIdenRessource.begin() + entPosition;
    this->patVecIdenRessource.erase(myIterator);
}

qint32 Client::getIdenRessource(int entPosition)
{
    QVector<qint32>::iterator myIterator;
    myIterator = this->patVecIdenRessource.begin() + entPosition;
    return *myIterator;
}

void Client::viderListeIdenRessource()
{
    this->patVecIdenRessource.clear();
}

qint32 Client::dureeParExamen()
{
    return patEntDureeConsultation / patVecIdenRessource.size();
}


qint32 Client::getIndicePriorite()
{
    qint32 valeur1 = 0;
    valeur1 = (getPATPriorite() * 100) + (getNombreRessource() * 10) + getPATDureeConsultation();
    return valeur1 ;
}


