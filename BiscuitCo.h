#pragma once
#include <string>
#include <iostream>
using namespace std;
/**
* Structure de Achat
* Une commande est compos�e de plusieurs achats
* Chaque Achat modifie le total des cookies command�s
*/
struct Achat
{
	string nomCookie;
	short int quantiteCookie;
	Achat* achatSuivant;

	// Constructeur par defaut de Achat
	Achat() {
		achatSuivant = nullptr;
	};

	/**
	* Constructeur de Achat
	* @param _nomCookie : le nom du cookie
	* @param _quantiteCookie : la quantite achet�e 
	* @param _suivant : pointeur vers l�achat suivant
	*/
	Achat(string _nomCookie, short int _quantiteCookie, Achat * _suivant = nullptr) {
		nomCookie = _nomCookie;
		quantiteCookie = _quantiteCookie;
		achatSuivant = _suivant;
	}
	
	// Destructeur de Achat
	~Achat() {}

	/**
	* M�thode renvoyant les informations de Achat sous forme de string
	* @return le nom du cookie suivit de sa quantit� achet�e
	*/
	string toString() {
		return nomCookie + " " + to_string(quantiteCookie);
	}

	/**
	* Setter de achatSuivant
	* @param un pointeur vers un autre Achat
	*/
	void setSuivant( Achat * _suivant) {
		achatSuivant = _suivant;
	}
};

/**
* Structure du Commande et Noeud-Commande
*/
struct Commande {
	// Structure Commande
	string source;
	string destinataire;

	//Liste achats
	Achat * teteAchat;
	Achat * queueAchat;
	Achat * courantAchat;
	
	// Structure Noeud-Commande
	Commande* commandeSuivante;

	//Constructeur par d�faut de Commande
	Commande() {
		teteAchat = queueAchat = courantAchat = new Achat;
	}

	/**
	* Constructeur de Commande
	* @param _source : le nom du Client � la source de la Commande
	* @param _destinataire : le nom du destinataire de la Commande
	* @param _suivante : pointeur vers la Commande suivante
	*/
	Commande(string _source, string _destinataire, Commande * _suivante = nullptr) {
		source = _source;
		destinataire = _destinataire;
		commandeSuivante = _suivante;
		teteAchat = queueAchat = courantAchat = new Achat();
	}



	//Destructeur de Commande
	~Commande() {
		// Tant que la tete n�est pas vid�e, on d�truit l��l�ment suivant
		while (teteAchat != nullptr) {
			courantAchat = teteAchat;
			teteAchat = teteAchat->achatSuivant;
			delete courantAchat;
		}
	}

	/**
	* Inserer un Achat � la fin de la liste des Achats
	* @param _nomCookie : le nom du cookie
	* @param _quantiteCookie : la quantite achet�e
	*/
	void insererAchat(string _nomCookie, short int _quantiteCookie) {
		queueAchat = queueAchat->achatSuivant = new Achat(_nomCookie, _quantiteCookie);
		
		// Partie avec la liste des cookies manquantes
	}

	// Supprimer un Achat � la position courante
	// Code provenant du cours
	void supprimerAchat() {
		
		// Sauvegarde du pointeur suivant
		Achat* courant = achatCourant();
		// Suppression de l��l�ment
		courantAchat->achatSuivant = courant->achatSuivant;

		if (queueAchat == courant) {
			// C�est le dernier �l�ment supprim�, mise � jour de queueAchat
			queueAchat = courantAchat;
		}

		// Suppression du pointeur cr��
		delete courant;

		// Partie avec la liste des cookies manquantes
	}
	
	// Supprimer tous les achats de la commande
	// Code provenant du cours
	void viderListeAchats() {

		// On parcourt la liste et on supprime l�achat courant � chaque it�ration
		while (teteAchat->achatSuivant != nullptr) {
			courantAchat = teteAchat->achatSuivant;
			teteAchat->achatSuivant = courantAchat->achatSuivant;
			delete courantAchat;
		}
		courantAchat = queueAchat = teteAchat;
	}


	// Return true si le pointeur courant est � l�int�rieur de la liste
	// Code provenant du cours
	bool estDansListe() const {
		return (courantAchat != nullptr) && courantAchat->achatSuivant != nullptr;
	}

	// Transporte le pointeur courant � la t�te de la liste
	// Code provenant du cours
	void fixerTete() {
		courantAchat = teteAchat;
	}

	// Transporte le pointeur courant � l�Achat suivant dans la liste
	// Code provenant du cours
	void suivant() {
		if (courantAchat != nullptr)
			courantAchat = courantAchat->achatSuivant;
	}

	// Retourne l�achat qui est actuellement point�
	// Code provenant du cours
	Achat* achatCourant() const {
		return courantAchat->achatSuivant;
	}

	/**
	* Methode toString de Commande retournant toutes les informations d�une commande :
	*  - source
	*  - destinataire
	*  - toString() de chaque Achat
	*  - &
	* @return resultat : toute la commande dans un string
	*/
	string toString() {

		// Ajout du nom du Client source
		string resultat = source + '\n';
		// Ajout du nom du Client destinataire
		resultat += destinataire + '\n';


		// Ajout des achats de cette commande
		for (fixerTete(); estDansListe();suivant()) {
			resultat += achatCourant()->toString() + '\n';
		}

		// Ajout du caract�re de fin de Commande
		resultat += "& \n";
		return resultat;
	}

};

/**
* Structure du Client et Noeud-Client
*/
struct Client {
	// Structure Client
	string nom;
	short int numero;
	string rue;

	// Structure Noeud-Client
	Client* clientSuivant;

	// Liste Commande 
	Commande* teteCommande, queueCommande, courantCommande;
};


/**
* Structure du Commande et Noeud-Commande
*/
struct Cookie {
	// Structure Cookie
	string nom;
	short int total;

	// Structure Noeud-Cookie
	Cookie* cookieSuivant;
};

class BiscuitCo
{
private:
	Client* listeClients;
	Cookie* listeCookies;
	//Storage storage;
public:
	BiscuitCo();
	~BiscuitCo();

	void ajouterCommande(string, Commande&); // Ajouter la Commander pass�e en param�tre � la liste des commandes du client
	void supprimerCommande(string, Commande&);
};
