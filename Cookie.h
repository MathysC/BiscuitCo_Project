#pragma once
#include <string>
using namespace std;
class Cookie
{
	string nom;						// Nom/Type du Cookie
	short int total;				// Compte du nombre de cookie de ce type achet� 

public:
	Cookie();						// Constructeur de Cookie sans param�tre
	Cookie(string);					// Constructeur avec nom de Cookie
	Cookie(string,short int);		// Constructeur avec nom et la quantit� de Cookie
	~Cookie();						// Destructeur de Cookie
	string getNom();				// Getter de nom
	short int getTotal();			// Getter de total
	void setNom(string);			// Setter de nom
	void AugmenterTotal(short int);	// Ajout au compte total
	void ReduireTotal(short int);	// Retrait au compte total
	bool EstEquivalent(Cookie);		// V�rifier l��quivalence entre 2 Cookie
};

