#pragma once
#include "Cookie.h"
#include "NoeudCookie.h"

class ListeCookies {
public:
	ListeCookies();						// Constructeur de ListeCookies
	~ListeCookies();					// Destructeur de ListeCookies
	
	void Inserer(const Cookie&);		// Ins�rer un nouveau Cookie � la liste
	void Inserer(string, short int);	// Ins�rer les informations d�un Cookie
	void Reduire(string,short int);		// R�duire la quantite d�un Cookie voire le Supprimer
	void Supprimer(const Cookie&);		// Supprimer un Cookie
	void FixerValeur(const Cookie&);	// Modifier la Valeur du Cookie sur le pointeur courant

	Cookie ValeurCourante() const;		// Obtenir la valeur au noeud courant
	Cookie getMeilleurCookie();			// Obtenir le Cookie avec le total le plus haut

	bool EstVide();						// V�rifier si la liste est vide
	bool EstDansListe() const;			// V�rifier que le pointeur Courant est dans la liste
	bool Trouver(const Cookie&);		// Trouver si le Cookie fait partie de la liste
	bool Trouver(const string);			// Trouver si le Cookie existe par les noms


	//// Actuellement sans utilisation
	void FixerTete();
	void FixerQueue();
	void Precedent();
	void Suivant();
	void ViderListe();					// Retirer tous les Cookies de la liste


private:
	NoeudCookie *tete;
	NoeudCookie *queue;
	NoeudCookie *courant;
};
