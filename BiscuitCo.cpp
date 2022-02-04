#include "BiscuitCo.h"
#include <string>
#include <iostream>
using namespace std;

BiscuitCo::BiscuitCo() {
	cout << "Construction BiscuitCo sans param�tre" << endl;
	// Initialisation de la liste des cookies
	this->teteCookie = this->queueCookie = this->courantCookie = new Cookie();
}

BiscuitCo::~BiscuitCo() {
	cout << "Destruction BiscuitCo" << endl;
}

/** 
* Ajouter une commande au client indiqu�, 
* Modifier les informations sur les cookies achet�s
* @param _client : le client 
* @param _commande : la commande � ajouter
*/
void BiscuitCo::ajouterCommande(string _nomClient, Commande& _commande) {

	// Mettre le pointeur sur le bon client
	/*if(this->trouver(_nomClient)) {*/

		// Inserer la commande dans la liste des commandes du client
		/*this->clientCourant().insererCommande(_commande);*/


		// Ajouter les informations des achats de cette commande � la liste des cookies
	for (_commande.fixerTete(); _commande.estDansListe(); _commande.suivant()) {
		Achat* cookie = _commande.achatCourant();
		string nomCookie = cookie->nomCookie;
		short int quantiteCookie = cookie->quantiteCookie;
		delete cookie;

		/*// Insertion des donn�es c�t� liste des Cookies*/

	}

	/* } else { // endif */
		cout << "Le client "+ _nomClient + "ne fait pas partie des membres enregistr�s." << endl; 
		cout << "La commande n�a pas �t� sauvegard�e." << endl;
	/* } // endelse */
}

//void supprimerCommande(string _nomClient, Commande* _commande) {
//	// Mettre le pointeur sur le bon client
//	/*if(this->trouver(_nomClient)) {*/
//
//		
//		/*// Suppression des donn�es c�t� liste de Cookies*/
//
//	/* } else { // endif */
//	cout << "Le client " + _nomClient + "ne fait pas partie des membres enregistr�s." << endl;
//	cout << "Aucune action n�a �t� effectu�e." << endl;
//	/* } // endelse */
//}


bool BiscuitCo::trouverClient(string _nomClient) {

	
	for (fixerTeteClient(); estDansListeClient(); clientSuivant()) {
		Client* temp = clientCourant();
		if (temp->nom == _nomClient) {
			return true;
		}
		else {
			return false;
		}

	}

	
}

bool BiscuitCo::trouverCookie(string _nomCookie) {

	for (fixerTeteCookie(); estDansListeCookie(); cookieSuivant()) {
		Cookie* tmp = CookieCourant();
		if (tmp->nomCookie == _nomCookie) {
			return true;
		}
	}
	return false;
}
