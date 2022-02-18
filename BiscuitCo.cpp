#include "BiscuitCo.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// Constructeur par defaut de BiscuitCo
BiscuitCo::BiscuitCo() {
	cout << "Construction BiscuitCo sans param�tre" << endl;
	// Initialisation de la liste des cookies
	this->teteCookie = this->queueCookie = this->courantCookie = new Cookie();

	// Initialisation de la liste des clients
	this->teteClient = this->queueClient = this->courantClient = new Client();
}

// Destructeur de BiscuitCo
BiscuitCo::~BiscuitCo() {
	cout << "Destruction BiscuitCo" << endl;

	// Destruction Cookies
	while (teteCookie != nullptr) {
		courantCookie = teteCookie;
		teteCookie = teteCookie->cookieSuivant;
		delete courantCookie;
	}

	// Destruction Clients
	while (teteClient != nullptr) {
		courantClient = teteClient;
		teteClient = teteClient->clientSuivant;
		delete courantClient;
	}
}



/// CLIENTS //////////////////////////////////////////////////

/**
* Fonction return True si le client existe,
* S�il existe, le pointeur clientCourant pointera sur ce client
* @param _nomclient : le nom du client � trouver
*/
bool BiscuitCo::trouverClient(string _nomClient) {
	// Il faut parcourir toute la liste
	for (fixerTeteClient(); estDansListeClient(); clientSuivant()) {
		Client* temp = clientCourant();
		if (temp->nom == _nomClient) {
			return true;
		}
	}
	return false; // Le client cherch� ne se trouve pas dans la liste
}

// Transporte le pointeur courant � la t�te de la liste
// Code provenant du cours
void BiscuitCo::fixerTeteClient() {
	courantClient = teteClient;
}

// Return true si le pointeur courant est � l�int�rieur de la liste
// Code provenant du cours
bool BiscuitCo::estDansListeClient() const {
	return (courantClient != nullptr) && (courantClient->clientSuivant != nullptr);
}

// Transporte le pointeur courant au cookie suivant dans la liste
// Code provenant du cours
void BiscuitCo::clientSuivant() {
	if (courantClient != nullptr)
		courantClient = courantClient->clientSuivant;
}

// Retourne le client actuellement point�
// Code provenant du cours
Client* BiscuitCo::clientCourant() const {
	return courantClient->clientSuivant;
}

/**
* Inserer un Client � la fin de la liste des Clients
* @param _nomClient : le nom du client
* @param _numero : le num�ro de rue du client
* @param _rue : la rue du client
*/
void BiscuitCo::insererClient(string _nomClient, short int _numero, string _rue) {
	queueClient = queueClient->clientSuivant = new Client(_nomClient, _numero, _rue);
}

/**
* Supprimer un Client de la liste des Clients
* @param _nomClient : le nom du client
*/
void BiscuitCo::supprimerClient(string _nomClient) {

	// Il faut d�abord trouver son emplacement dans la liste des Clients
	if (trouverClient(_nomClient)) {
		Client* courant = clientCourant();

		// Suppression de ses commandes
		// Mettre � jour les totaux des cookies
		for (courant->fixerTeteCommande(); courant->estDansListeCommande(); courant->commandeSuivante()) {
			supprimerCommandeCookies(courant->commandeCourante());
		}

		courant->viderListeCommandes();
		//Suppression du Client
		courantClient->clientSuivant = courant->clientSuivant;
		if (queueClient == courant) {
			queueClient = courantClient;
		}
		delete courant;
	}
}

/// COMMANDES ////////////////////////////////////////////////

/**
* Augmenter les totaux des cookies en fonctions des achats de la commande
* @param _commande : la commande � ajouter
*/
void BiscuitCo::ajouterCommandeCookies(Commande* _commande) {
	for (_commande->fixerTeteAchat(); _commande->estDansListeAchat(); _commande->achatSuivant()) {
		Achat* achat = _commande->achatCourant();
		insererCookie(achat->nomCookie, achat->quantiteCookie);
	}
}

/**
* R�duire les totaux des cookies en fonctions des achats de la commande
* @param _commande : la commande � retirer
*/
void BiscuitCo::supprimerCommandeCookies( Commande* _commande) {
	for (_commande->fixerTeteAchat(); _commande->estDansListeAchat(); _commande->achatSuivant()) {
		Achat* achat = _commande->achatCourant();
		supprimerCookie(achat->nomCookie, achat->quantiteCookie);
	}
}

/**
* V�rification de l'existence des clients dans la liste cha�n�e et cr�ation de la nouvelle commande.
* Si les clients n'existent pas, return null
* @param _source : le nom du client � la source de la commande
* @param _destinataire : le nom du client destinataire de la commande
*/
Commande* BiscuitCo::verifierClientsEtCreerCommande(string _source, string _destinataire) {

	// On v�rifier que les deux clients existent
	if (trouverClient(_source) && trouverClient(_destinataire)) {

		Client* _clientSource = clientCourant();
		// Cr�ation d�une commande 
		_clientSource->insererCommande(_source, _destinataire);

		// Retourne cette nouvelle commande
		return _clientSource->commandeCourante();
	} 

	cout << "Au moins un des clients de cette commande ne fait pas partie des membres enregistr�s." << endl;
	cout << "La commande n�a pas �t� sauvegard�e." << endl;
	return NULL;
}

/// COOKIES //////////////////////////////////////////////////


/**
* Fonction return True si le cookie existe,
* S�il existe, le pointeur cookiecourante pointera sur ce cookie
* @param _nomCookie : le nom du cookie � trouver
*/
bool BiscuitCo::trouverCookie(string _nomCookie) {

	for (fixerTeteCookie(); estDansListeCookie(); cookieSuivant()) {
		Cookie* tmp = cookieCourant();
		if (tmp->nomCookie == _nomCookie) {
			return true;
		}
	}
	return false;
}

// Transporte le pointeur courant � la t�te de la liste
// Code provenant du cours
void BiscuitCo::fixerTeteCookie() {
	courantCookie = teteCookie;
}

// Return true si le pointeur courant est � l�int�rieur de la liste
// Code provenant du cours
bool BiscuitCo::estDansListeCookie() const {
	return (courantCookie != nullptr) && this->courantCookie->cookieSuivant != nullptr;
}

// Transporte le pointeur courant au cookie suivant dans la liste
// Code provenant du cours
void BiscuitCo::cookieSuivant() {
	if (courantCookie != nullptr)
		courantCookie = courantCookie->cookieSuivant;
}

// Retourne le cookie actuellement point�
// Code provenant du cours
Cookie* BiscuitCo::cookieCourant() const {
	return this->courantCookie->cookieSuivant;
}

/**
* Augmenter le total du cookie d�j� existant ou en cr�er un nouveau
* @param _nomCookie : le nom du Cookie
* @param _quantiteCookie : la quantite de ce Cookie
*/
void BiscuitCo::insererCookie(string _nomCookie, short int _quantiteCookie) {

	// Le Cookie existe d�j�
	if (trouverCookie(_nomCookie)) {
		cookieCourant()->AugmenterTotal(_quantiteCookie);

	// Il faut cr�er un nouveau Cookie
	} else {
		queueCookie = queueCookie->cookieSuivant = new Cookie(_nomCookie, _quantiteCookie);
	}
}

/**
* Reduire le total du cookie d�j� existant et le supprimer s�il le total est nul
* @param _nomCookie : le nom du Cookie
* @param _quantiteCookie : la quantite de ce Cookie
*/
void BiscuitCo::supprimerCookie(string _nomCookie, short int _quantiteCookie) {

	// Le Cookie existe
	if (trouverCookie(_nomCookie)) {
		cookieCourant()->ReduireTotal(_quantiteCookie);
	}
	
	// Il n�y a plus de Cookie command�
	if (cookieCourant()->total <= 0) {
		Cookie* courant = cookieCourant();
		courantCookie->cookieSuivant = courant->cookieSuivant;
		if (queueCookie == courant) {
			queueCookie = courantCookie;
		}
		delete courant;
	}
}

// Methode permettant d�afficher sur la console le Cookie avec le total le plus �lev�
void BiscuitCo::meilleurCookie() {

	// Initialisation du point de d�part
	fixerTeteCookie();
	Cookie* meilleur = cookieCourant();

	// Trouver le cookie avec le total le plus �lev�
	for (fixerTeteCookie(); estDansListeCookie(); cookieSuivant()) {
		if (cookieCourant()->total > meilleur->total) {
			meilleur = cookieCourant();
		}
	}
	
	// Afficher ses informations
	cout << "Le cookie le plus populaire est le suivant :" << endl;
	cout << meilleur->toString() << endl;
}

/// STORAGE //////////////////////////////////////////////////


// Methode permettant d�int�grer � l�object BiscuitCo les informations sur les clients
void BiscuitCo::liste_clients(string _fichierClient) {

	ifstream fin(_fichierClient); //Lecture

	// Variables composant un client
	string nom;
	string rue;
	short int num;

	// Tant que l�on peut recup�rer les informations
	while (fin >> nom) {
		fin >> num >> rue;
		//Cr�er un client
		insererClient(nom, num, rue);
	}

	// Fermer la lecture du fichier
	fin.close();
}

// M�thode permettant d�int�grer aux clients les commandes enregistr�s sur le document txt
void BiscuitCo::liste_commandes(string _fichierCommande) {

	// Lecture du fichiers Commandes
	ifstream fin(_fichierCommande);

	// Une commande est compos� de ces variables
	string source;
	string destinataire;

	// Un achat est compos� de ces variables
	string nomCookie;
	short int quantiteCookie;

	string courant = "";

	// Tant que l�on peut r�cuperer des informations sur le fichier
	while (fin >> source){
		fin >> destinataire;
		

		Commande* commande = verifierClientsEtCreerCommande(source, destinataire);
		
		if(commande != NULL){
			// Il faut maintenant lire chaque achat et l�ajouter � la commande
			// Les achats sont list�s sur plusieurs lignes, jusqu�au "&"
			// la variable courant nous permet de faire cette v�rification

			// On r�cup�re une premi�re fois la ligne suivant le destinataire
			fin >> courant;
			while (courant != "&") {
				// Si ce n'�tais pas "&" c'�tait alors le nom d'un cookie.
				nomCookie = courant;

				// Sur cette m�me ligne nous r�cup�rons la quantit� indiqu�e
				fin >> quantiteCookie;

				// Nous pouvons ins�rer un achat compos� de ces deux informations
				commande->insererAchat(nomCookie,quantiteCookie);

				// Changer de ligne
				fin >> courant;
			}

			//Maintenant que la commande est cr��, il faut ajouter chaque achat dans la liste des cookies.
			ajouterCommandeCookies(commande);
		}
	}

	// Fermer la lecture du fichier
	fin.close();
}


//M�thode permettant d�int�grer les transactions effectues dans le document txt
void BiscuitCo::liste_transactions(string _fichierTransaction) {

	ifstream fin(_fichierTransaction); //Lecture

	char caractere;
	//Impl�mentaion dans supprimerClient ins�rerClient
	string nomClient;
	//Impl�mentaion dans ins�rerClient
	short int numero;
	string rue;

	//Impl�mentaion dans 
	string source;
	string nomFichierClient;
	string nomFichierCommande;
	string destinataire;
	string nomCookie;
	string courant;
	short int quantiteCookie;

	while (fin >> caractere) {
		switch (caractere) {
		case '-':
			fin >> nomClient;
			supprimerClient(nomClient);
			break;
		case '+':
			fin >> nomClient >> numero >> rue;
			insererClient(nomClient, numero, rue);
			break;
		case '=':
			fin >> source >> destinataire;
			Commande * commande = verifierClientsEtCreerCommande(source, destinataire);

			if (commande != NULL) {
				// Il faut maintenant lire chaque achat et l�ajouter � la commande
				// Les achats sont list�s sur plusieurs lignes, jusqu�au "&"
				// la variable courant nous permet de faire cette v�rification

				// On r�cup�re une premi�re fois la ligne suivant le destinataire
				fin >> courant;
				while (courant != "&") {
					// Si ce n'�tais pas "&" c'�tait alors le nom d'un cookie.
					nomCookie = courant;

					// Sur cette m�me ligne nous r�cup�rons la quantit� indiqu�e
					fin >> quantiteCookie;

					// Nous pouvons ins�rer un achat compos� de ces deux informations
					commande->insererAchat(nomCookie, quantiteCookie);

					// Changer de ligne
					fin >> courant;
				}

				//Maintenant que la commande est cr��, il faut ajouter chaque achat dans la liste des cookies.
				ajouterCommandeCookies(commande);
			}
			break;

		case '?':
			fin >> nomClient;
			trouverClient(nomClient);
			cout << clientCourant()->toString();
			break;

		case '$':
			meilleurCookie();
			break;

		case 'O':
			fin >> nomFichierClient;
			fin >> nomFichierCommande;
			break;
		case 'S':
			fin >> nomFichierClient;
			fin >> nomFichierCommande;

			break;

		default:
			cout << "\n fin de la liste transaction \n";
			return;
		}


		fin.close();

	}