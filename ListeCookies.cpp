#include "ListeCookies.h"

/**
* Constructeur de ListeCookies sans param�tre
*/
ListeCookies::ListeCookies() {
	queue = courant = tete = new NoeudCookie();
}

/**
* Destructeur de ListeCookie
*/
ListeCookies::~ListeCookies() {
	while (tete != nullptr) {
		courant = tete;
		tete = tete->suivant;
		delete courant;
	}
}

/**
* M�thode permettant d�ins�rer un nouveau noeud en fin de Liste Cha�n�e
* @param Un nouveau cookie
*/
void ListeCookies::Inserer(const Cookie& _cookie) {
	queue = queue->suivant = new NoeudCookie(_cookie);
}

/**
* Obtenir le Cookie au noeud courant
* @return un Cookie
*/
Cookie ListeCookies::ValeurCourante() const {
	return courant->suivant->element;
}

/**
* M�thode permettant de v�rifier que courant cible toujours un noeud de la liste
* @return true si courant est sur un noeud de la liste, false sinon
*/
bool ListeCookies::EstDansListe() const {
	return (courant != nullptr) && (courant->suivant != nullptr);
}

/**
* M�thode parcourant la liste afin de trouver le Cookie souhait�
* Si la liste poss�de ce Cookie, le pointeur courant sera sur le noeud correspondant et la m�thode renverra true
* Sinon le pointeur courant sera sur au m�me emplacement que queue et la m�thode renverra false
*/
bool ListeCookies::Trouver(const Cookie& _cookie) {
	courant = tete; // On replace courant au d�but de la liste

	// Tant que nous sommes dans la liste
	while (this->EstDansListe()) {
		// Si le Cookie est trouv� dans le noeud courant, on retourne true
		if (this->ValeurCourante().EstEquivalent(_cookie)) {
			return true;
		}
		// Sinon on passe au noeud suivant
		else {
			courant = courant->suivant;
		}
	}
	//Si le Cookie ne fait pas partie de la liste, on retourne false
	return false;
}

/**
* M�thode permettant d�obtenir le Cookie avec le Total le plus Haut 
* @return le meilleur Cookie
*/
Cookie ListeCookies::getMeilleurCookie() {
	Cookie meilleur;
	courant = tete; // On se place en d�but de liste

	//On parcourt tous les noeuds afin de trouver le meilleur Cookie
	while (this->EstDansListe()) {
		// Si le Cookie du Noeud Courant est mieux que le "meilleur" Cookie, remplacer les Cookies
		if (this->ValeurCourante().getTotal() > meilleur.getTotal()) {
			meilleur = this->ValeurCourante();
		}
		// Sinon on passe au noeud suivant
		else {
			courant = courant->suivant;
		}
	}
	return meilleur;
}




// Possiblement � supprimer 

/**
* M�thode permettant de savoir si la liste est vide
* @return true si le suivant du premier noeud est videm false sinon
*/
bool ListeCookies::ListeVide() {
	return tete->suivant == nullptr;
}

/**
* M�thode permettant la suppression du Noeud
* @param Un Cookie
*/
void Supprimer(const Cookie& _cookie) {

}
void FixerTete();
void FixerQueue();
void Precedent();
void Suivant();