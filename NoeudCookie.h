#pragma once
#include "Cookie.h"

class NoeudCookie {
public:
	Cookie element;						// Un Cookie, l��l�ment principal de chaque noeud
	NoeudCookie* suivant;				// Le prochain Noeud de la liste cha�n�e
	// Constructeur de NoeudCookie avec un Cookie et un NoeudCookie
	NoeudCookie(const Cookie& _cookie, NoeudCookie* _suiv = nullptr) {
		this->element = _cookie;
		this->suivant = _suiv;
	}
	NoeudCookie();						// Constructeur de NoeudCookie sans param�tre
	~NoeudCookie();						// Destructeur de NoeudCookie
};