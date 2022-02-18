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
* Fonction trouvant si le client existe dans la liste cha�n�e.
* S�il existe, le pointeur clientCourant pointera sur ce client
* @param _nomclient : le nom du client � trouver
* @returns Return True si le client existe.
*/
bool BiscuitCo::trouverClient(string _nomClient) {
	// On parcourt la liste des clients compl�tement
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

/**
* Code provenant du cours
* @returns true si le pointeur courant est � l�int�rieur de la liste
*/ 
bool BiscuitCo::estDansListeClient() const {
	return (courantClient != nullptr) && (courantClient->clientSuivant != nullptr);
}

/** 
* Transporte le pointeur courant au cookie suivant dans la liste
* Code provenant du cours
*/
void BiscuitCo::clientSuivant() {
	if (courantClient != nullptr)
		courantClient = courantClient->clientSuivant;
}

/** 
* Code provenant du cours
* @returns le client actuellement point�
*/
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

		// La suppression de ses commandes se fait en deux �tapes
		// 1.Mettre � jour les totaux des cookies
		for (courant->fixerTeteCommande(); courant->estDansListeCommande(); courant->commandeSuivante()) {
			supprimerCommandeCookies(courant->commandeCourante());
		}

		// 2. Vider la liste cha�n�e des commandes
		courant->viderListeCommandes();

		//Suppression du Client
		courantClient->clientSuivant = courant->clientSuivant;
		if (queueClient == courant) {
			queueClient = courantClient;
		}

		// Suppression du pointeur utilis�
		delete courant;
	}
}

/**
* Supprimer un Client de la liste des Clients destinataire
* @param _nomClient : le nom du client
*/
void BiscuitCo::supprimerClientDest(string _destinataire) {

	// On parcourt compl�tement la liste des Clients
	for (fixerTeteClient(); estDansListeClient(); clientSuivant()) {

		// Pour chaque client, on parcourt sa liste des commandes
		Client* courant = clientCourant();
		for (courant->fixerTeteCommande(); courant->estDansListeCommande(); courant->commandeSuivante()) {

			// On verra pour chacune des commandes 
			Commande* cmd = courant->commandeCourante();

			// Si le destinataire est celui recherch�
			if (cmd->destinataire == _destinataire) {
				supprimerCommandeCookies(cmd);
				courant->supprimerCommande();
			}

			// Suppression des pointeurs 
			delete courant;
			delete cmd;
		}
	}
}


/// COMMANDES ////////////////////////////////////////////////


/**
* Augmenter les totaux des cookies en fonctions des achats de la commande
* @param _commande : la commande � ajouter
*/
void BiscuitCo::ajouterCommandeCookies(Commande* _commande) {

	// On parcourt tous les achats de cette commande
	for (_commande->fixerTeteAchat(); _commande->estDansListeAchat(); _commande->achatSuivant()) {
		Achat* achat = _commande->achatCourant();
		// On modifie les totaux des cookies
		insererCookie(achat->nomCookie, achat->quantiteCookie);
	}
}

/**
* R�duire les totaux des cookies en fonctions des achats de la commande
* @param _commande : la commande � retirer
*/
void BiscuitCo::supprimerCommandeCookies( Commande* _commande) {
	// On parcourt tous les achats de cette commande
	for (_commande->fixerTeteAchat(); _commande->estDansListeAchat(); _commande->achatSuivant()) {
		Achat* achat = _commande->achatCourant();

		// On modifie les totaux des cookies
		supprimerCookie(achat->nomCookie, achat->quantiteCookie);
	}
}

/**
* V�rification de l'existence des clients dans la liste cha�n�e et cr�ation de la nouvelle commande.
* Si les clients n'existent pas, return null
* @param _source : le nom du client � la source de la commande
* @param _destinataire : le nom du client destinataire de la commande
* @returns la commande nouvellement cr��e ou NULL sinon
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

	// Si les deux clients n'existent pas
	cout << "Au moins un des clients de cette commande ne fait pas partie des membres enregistr�s." << endl;
	cout << "La commande n�a pas �t� sauvegard�e." << endl;
	return NULL;
}


/// COOKIES //////////////////////////////////////////////////


/**
* Si le cookie existe, le pointeur cookiecourant pointera sur ce cookie
* @param _nomCookie : le nom du cookie � trouver
* @returns return True si le cookie existe
*/
bool BiscuitCo::trouverCookie(string _nomCookie) {

	// On parcourt la liste de Cookies
	for (fixerTeteCookie(); estDansListeCookie(); cookieSuivant()) {
		Cookie* tmp = cookieCourant();

		// Le cookie existe
		if (tmp->nomCookie == _nomCookie) {
			return true;
		}
	}
	return false;
}

/** 
* Transporte le pointeur courant � la t�te de la liste
* Code provenant du cours
*/ 
void BiscuitCo::fixerTeteCookie() {
	courantCookie = teteCookie;
}

/**
* Code provenant du cours
* @returns  true si le pointeur courant est � l�int�rieur de la liste
*/
bool BiscuitCo::estDansListeCookie() const {
	return (courantCookie != nullptr) && this->courantCookie->cookieSuivant != nullptr;
}

/** 
* Transporte le pointeur courant au cookie suivant dans la liste
* Code provenant du cours
*/
void BiscuitCo::cookieSuivant() {
	if (courantCookie != nullptr)
		courantCookie = courantCookie->cookieSuivant;
}

/**
* Code provenant du cours
* @returns le cookie actuellement point�
*/
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

		// Il n�y a plus de Cookie command�
		if (cookieCourant()->total <= 0) {

			// On supprime ce cookie sans quantit� command�e
			Cookie* courant = cookieCourant();
			courantCookie->cookieSuivant = courant->cookieSuivant;
			if (queueCookie == courant) {
				queueCookie = courantCookie;
			}

			// Suppression pointeur
			delete courant;
		}
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

	// Suppression pointeur
	delete meilleur;
}


/// STORAGE //////////////////////////////////////////////////


/** 
* Methode permettant d�int�grer � l�object BiscuitCo les informations sur les clients
* @param _fichierClient : le fichier des clients
*/
void BiscuitCo::ouverture_clients(string _fichierClient) {

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

/**
* M�thode permettant d�int�grer aux clients les commandes enregistr�s sur le document txt
* @param _fichierCommande : le fichier des commandes
*/
void BiscuitCo::ouverture_commandes(string _fichierCommande) {

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
		
		// On v�rifie que les clients existent et on cr�� la commande
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

/**
* M�thode permettant d�int�grer les transactions effectues dans le document txt
* @param _fichierTransaction : Fichier de transaction � lire
*/
void BiscuitCo::ouverture_transactions(string _fichierTransaction) {

	ifstream fin(_fichierTransaction); //Lecture

	char caractere;
	//Impl�mentaion dans supprimerClient ins�rerClient
	string nomClient;
	//Impl�mentaion dans ins�rerClient
	short int numero;
	string rue;

	//Impl�mentaion des variables n�cessaires 
	string source;
	string nomFichierClient;
	string nomFichierCommande;
	string destinataire;
	string nomCookie;
	string courant;
	short int quantiteCookie;

	while (fin >> caractere) {
		switch (caractere) {

			// Suppression d'un Client
			case '-': {
				fin >> nomClient;
				cout << "Suppression " << nomClient << "\n" << endl;
				supprimerClient(nomClient);
				break;
			}

			// Ajout d'un Client
			case '+': {
				fin >> nomClient >> numero >> rue;

				cout << "Ajout " << nomClient << "\n" << endl;
				insererClient(nomClient, numero, rue);
				break;
			}

			// Ajout d'une commande d'un client
			case '=': {
				fin >> source >> destinataire;
				cout << "Ajout d'une commande de " << source << " � " << destinataire << "\n" << endl;
				Commande* commande = verifierClientsEtCreerCommande(source, destinataire);

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
			}

			// Afficher les commandes faites par un Client
			case '?': {
				fin >> nomClient;
				cout << "Affichage des commandes de " << nomClient << "\n" << endl;
				trouverClient(nomClient);
				cout << clientCourant()->toStringCommandes();
				break;
			}

			// Afficher les informations du meilleur cookie
			case '$': {
				cout << "Affichage du meilleur Cookie" << "\n" << endl;
				meilleurCookie();
				break;
			}

			// Ouverture des fichiers de Clients et Commandes
			case 'O': {
				cout << "Ouvertures des fichiers des Clients et Commandes \n" << endl;
				fin >> nomFichierClient;
				fin >> nomFichierCommande;
				ouverture_clients(nomFichierClient);
				ouverture_commandes(nomFichierCommande);
				break;
			}

			// Sauvegarde des Clients et Commandes
			case 'S': {
				cout << "Sauvegardes des fichiers des Clients et Commandes \n" << endl;
				fin >> nomFichierClient;
				fin >> nomFichierCommande;
				sauvegarde_clients(nomFichierClient);
				sauvegarde_commandes(nomFichierCommande);
				break;
			}

			// Cas erreur
			default: {
				cout << "\n fin de la liste transaction \n";
				fin.close();
				return;
			}
		}
	}

	cout << "\n Merci Isaaaaaaa :)" << endl;
	fin.close();
}

/**
* Fonction sauvegarde de la liste cha�n�e des Clients sur un fichier txt
* @param _nomFichierClient : Le nom du fichier de sauvegarde
*/
void BiscuitCo::sauvegarde_clients(string _nomFichierClient) {

	// Cr�ation/Ouverture du fichier de sauvegarde
	ofstream sortie;
	sortie.open(_nomFichierClient);
	
	// On parcourt tous les clients et on sauvegarde les informations de ceux l�
	for (fixerTeteClient(); estDansListeClient(); clientSuivant()) {
		Client* courant = clientCourant();
		sortie << courant->toString();
	}

	// Fermeture du fichier
	sortie.close();
}

/**
* Fonction sauvegarde des commandes de tous les clients sur un fichier txt
* @param _nomFichierCommande : Le nom du fichier de sauvegarde
*/
void BiscuitCo::sauvegarde_commandes(string _nomFichierCommande) {
	// Cr�ation/Ouverture du fichier de sauvegarde
	ofstream sortie;
	sortie.open(_nomFichierCommande);


	// On parcourt tous les clients et on sauvegarde les commandes de ceux l�
	for (fixerTeteClient(); estDansListeClient(); clientSuivant()) {
		Client* courant = clientCourant();
		sortie << courant->toStringCommandes();
	}

	// Fermeture du fichier
	sortie.close();
}