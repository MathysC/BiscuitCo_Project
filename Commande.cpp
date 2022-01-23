#include "Commande.h"
#include <iostream>
using namespace std;

/**
* Constructeur vide de Commande
*/
Commande::Commande() {}

/**
* Constructeur de Commande 
* @param _source : le client source de la Commande
* @param _destinataire : le client destinataire de la Commande
* @param _liste : la liste Globale des Cookies permettant un suivi des totaux
*/
Commande::Commande(Client* _source, Client* _destinataire, ListeCookies* _liste) : 
	source(_source), destinataire(destinataire), listeCookies(_liste){}

/**
* Destructeur de Commande
*/
Commande::~Commande() {}

/**
* Getter de source
* @return le client source
*/
Client* Commande::getSource() { return this->source; }

/**
* Getter de destinataire
* @return le client destinataire
*/
Client* Commande::getDestinataire() { return this->destinataire; }

/**
* Getter de listeCommandeCookies
* @return la liste des commandes de Cookies
*/
list<CommandeCookie> Commande::getListeCommandeCookies() { return this->listeCommandeCookies; }

/**
* Setter de Source
* @param _client : Un client source, peut �tre le destinataire
*/
void Commande::setSource(Client* _client) { this->source = _client; }

/**
* Setter de Destinataire
* @param _client : Un client destinataire, peut �tre la source
*/
void Commande::setDestinaire(Client* _client) { this->destinataire = _client; }

/**
* Ajouter le Cookie dans les listes de Cookies et Commandes
* @param _nomCookie : le nom du Cookie
* @param _quantite : la quantite de ce Cookie � ajouter
*/
void Commande::AjouterCookie(string _nomCookie, short int _quantite) {
	// Ins�rer ce Cookie dans la liste des Cookies
	listeCookies->Inserer(_nomCookie, _quantite);
	// Ins�rer ce Cookie dans la liste des Commandes
	listeCommandeCookies.push_back(CommandeCookie(_nomCookie, _quantite));
}

/**
* Retirer la quantit� du cookie de la liste globale des Cookies
* @param _nomCookie : le nom du Cookie
* @param _quantite : la quantite de ce Cookie � soustraire
*/
void Commande::RetirerCookie(string _nomCookie, short int _quantite) {
	// Reduire dans la liste globale de cookie la quantit� du cookie pass� en param�tre
	listeCookies->Reduire(_nomCookie, _quantite);
	// // Cette partie consiste � supprimer le Cookie de la liste des Commandes
	// // Mais ne fonctionne pas
	//list<CommandeCookie>::iterator it = find(listeCommandeCookies.begin(), listeCommandeCookies.end(), CommandeCookie(_nomCookie, _quantite));
	//listeCommandeCookies.erase(it);
}

/**
* Soustraire des totaux les quantit�s de cookies command�es et vider la liste
*/
void Commande::ViderCookies() {
	// Retirer de la Liste Cha�n�e de Cookies la quantit� command�e des cookies de cette commande
	for (list<CommandeCookie>::iterator it = listeCommandeCookies.begin(); it != listeCommandeCookies.end(); ++it) {
		RetirerCookie(it->nomCookie, it->quantite);
	}
	// Supprimer tous les �l�ments de la liste de commandes
	listeCommandeCookies.clear();
}

/**
* M�thode affichant la totalit� de la commande effectu�e
* Les informations sont affich�s de la m�me fa�on qu�elles sont re�ues
*/
void Commande::AfficherCommande() {
	// Afficher la source de la commande
	cout << source->getNom() << endl;
	
	// Afficher le destinataire de la commande
	cout << destinataire->getNom() << endl;

	// Afficher tous les Cookies de la commande
	for (list<CommandeCookie>::iterator it = listeCommandeCookies.begin(); it != listeCommandeCookies.end();++it) {
		cout << it->nomCookie << " : " << it->quantite << endl;
	}

	// Afficher le caract�re de fin de commande
	cout << "&" << endl;
}
