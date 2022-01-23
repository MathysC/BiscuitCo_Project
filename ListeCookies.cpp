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
	// Destruction des Noeuds un � un
	while (tete != nullptr) {
		courant = tete;
		tete = tete->suivant;
		delete courant;
	}
}

/**
* M�thode permettant d�augmenter le total du Cookie pass�
* en param�tre s�il existe d�j�. Sinon cr�� et insert un nouveau Cookie
*
* Le cookie est d�finit en son ensemble
* @param _cookie : le Cookie
*/
void ListeCookies::Inserer(const Cookie& _cookie) {
	queue = queue->suivant = new NoeudCookie(_cookie);
}

/**
* M�thode permettant d�augmenter le total du Cookie pass� 
* en param�tre s�il existe d�j�. Sinon cr�� et insert un nouveau Cookie
* 
* Le cookie est d�finit par son nom et sa quantit�
* @param _nomCookie : le nom du Cookie
* @param _quantite : la quantite du Cookie
*/
void ListeCookies::Inserer(string _nomCookie, short int _quantite) {

	// Si le Cookie existe d�j�
	if (Trouver(_nomCookie)) {
		// On modifie la valeur du Total de ce Cookie
		Cookie cookieCourant = this->ValeurCourante();
		cookieCourant.AugmenterTotal(_quantite);

		//Modifier la valeur dans le Noeud
		FixerValeur(cookieCourant);
	}
	// Sinon, il faut Ajouter ce nouveau Cookie
	else {
		Inserer(Cookie(_nomCookie, _quantite));
	}
}

/**
* M�thode permettant la suppression du Noeud
* @param _cookie : Un Cookie
*/
void ListeCookies::Supprimer(const Cookie& _cookie) {
	//Mettre le pointeur courant sur le Cookie a supprimer
	Trouver(_cookie); 
	// Sauvegarde du pointeur du noeud Courant
	NoeudCookie* ptemp = courant->suivant; 
	// suppression de l'�l�ment
	courant->suivant = ptemp->suivant; 
	if (queue == ptemp)
		// C'est le dernier �l�ment supprim�, mise � jour de Queue
		queue = courant; 
	delete ptemp;
}

/**
* M�thode permettant de r�duire la quantite totale d�un cookie
* @param _nomCookie : le nom du Cookie
* @param _quantite : la quantit� du cookie � r�duire
*/
void ListeCookies::Reduire(string _nomCookie, short int _quantite) {
	//Mettre le pointeur courant sur le Cookie a supprimer
	if (Trouver(_nomCookie)) { 

		// Reduire la quantite de ce Cookie
		Cookie cookieCourant = this->ValeurCourante();
		cookieCourant.ReduireTotal(_quantite); 

		//Modifier la valeur dans le Noeud
		FixerValeur(cookieCourant);


		// Si cette quantite devient inf�rieur ou �gale � 0, Supprimer le Cookie
		if (this->ValeurCourante().getTotal() <= 0) {
			Supprimer(this->ValeurCourante());
		}
	}
}

/**
* Modifier le Cookie du pointeur Courant pour le Cookie en param�tre.
* @param _cookie : le nouveau Cookie
*/
void ListeCookies::FixerValeur(const Cookie& _cookie) {
	courant->suivant->element = _cookie;
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
	// V�rifier que le courant et son suivant ne sont pas null
	return (courant != nullptr) && (courant->suivant != nullptr);
}

/**
* M�thode parcourant la liste afin de trouver le Cookie souhait�
* Si la liste poss�de ce Cookie, le pointeur courant sera sur le noeud correspondant et la m�thode renverra true
* Sinon le pointeur courant sera sur au m�me emplacement que queue et la m�thode renverra false
* 
* La v�rification se fait sur l�ensemble du Cookie (nom et total)
* @param _cookie : un Cookie
*/
bool ListeCookies::Trouver(const Cookie& _cookie) {
	// On replace courant au d�but de la liste
	courant = tete; 

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
* M�thode parcourant la liste afin de trouver le Cookie souhait�
* Si la liste poss�de un Cookie de ce nom, le pointeur courant sera sur le noeud correspondant et la m�thode renverra true
* Sinon le pointeur courant sera sur au m�me emplacement que queue et la m�thode renverra false
* 
* La v�rification se fait que de nom
* @param _nomCookie : le nom du Cookie
*/
bool ListeCookies::Trouver(const string _nomCookie) {
	// On replace courant au d�but de la liste
	courant = tete; 

	// Tant que nous sommes dans la liste
	while (this->EstDansListe()) {
		// Si le Cookie est trouv� dans le noeud courant, on retourne true
		if (this->ValeurCourante().getNom() == _nomCookie) {
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

	// On se place en d�but de liste
	courant = tete; 

	//On parcourt tous les noeuds afin de trouver le meilleur Cookie
	while (this->EstDansListe()) {
		// Si le Cookie du Noeud Courant est mieux que le meilleur Cookie : remplacer les Cookies
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
bool ListeCookies::EstVide() {
	return tete->suivant == nullptr;
}


void FixerTete();
void FixerQueue();
void Precedent();
void Suivant();