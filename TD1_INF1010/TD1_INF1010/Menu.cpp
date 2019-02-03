/****************************************************************************
 * Fichier: Point.h
 * Auteur: Georges Abou-Khalil
 * Date: 2 sept 2008
 * Mise a jour : 11 mai 2011
 * Description: Implémentation de la classe Point
 ****************************************************************************/

#include "Menu.h"


 /****************************************************************************
  * Fonction: Point::Point
  * Description: Constructeur par défaut
  * Paramètres: aucun
  * Retour: aucun
  * 
  ****************************************************************************/
Menu::Menu() 
{
	capacite_ = MAXPLAT;
	nbPlats_ = 0;
	type_ = Matin;
	listePlats_ = new Plat* [capacite_];
	for (unsigned int i = 0; i < capacite_; i++) 
		listePlats_[i] =  nullptr;
}

Menu::Menu(string fichier, TypeMenu type)
{
	type_ = type;
	capacite_ = MAXPLAT;
	nbPlats_ = 0;
	listePlats_ = new Plat*[capacite_];

	for (int i = 0; i < MAXPLAT; i++)
		listePlats_[i] = nullptr;

	
	lireMenu(fichier);
}


int Menu::getNbPlats() const
{
	return nbPlats_;
}

void Menu::afficher() const
{
	cout << "Voici ce qu'il y a sur le menu: " << endl;
	for (int i = 0; i < getNbPlats(); i++) 
		listePlats_[i]->afficher();
}

Plat* Menu::trouverPlat(const string& nom) const
{
	
	for (unsigned int i = 0; i < nbPlats_; i++) {
		if (listePlats_[i]->getNom() == nom) 
			return listePlats_[i];
	}
	return nullptr;
}

void Menu::ajouterPlat(Plat& plat)
{
	if (nbPlats_ == capacite_) {
		capacite_ *= 2;
		Plat** copiePlats = new Plat*[capacite_];
		for (unsigned int i = 0; i < nbPlats_; i++)
			copiePlats[i] = listePlats_[i];
		for (unsigned int i = nbPlats_; i < capacite_; i++)
			copiePlats[i] = nullptr;
		delete[] listePlats_;
		listePlats_ = copiePlats;
	}
	listePlats_[nbPlats_] = &plat;
	nbPlats_++;	
}

void Menu::ajouterPlat(const string& nom, double montant, double cout)
{
	Plat* plat= new Plat(nom, montant, cout);
	ajouterPlat(*plat);
}

bool Menu::lireMenu(string& fichier)
{
	ifstream ficLire(fichier);
	string nom, type = "type";
	double montant, coutPlat;
	bool lectureEffectuee = false;
		
	switch (type_) {
	case (Matin):
		
		 do {
			 if (type != "MATIN") {
				 getline(ficLire, nom);
				 if (nom[0] == '-') {
					 type = nom.substr(1, nom.size() - 1);
					 nom = type;
				 }		
			 }
			 else if (type == "MATIN") {
				 ficLire >> nom;
				 if (nom[0] == '-')
					 type = nom.substr(1, nom.size() - 1);
			 }
			 if (type == "MATIN" && nom != type) {
				 ficLire >> montant >> coutPlat;
				 ajouterPlat(nom, montant, coutPlat);
			 }
		 } while (type != "MIDI");
		 lectureEffectuee = true;
		 break;
	case (Midi):

		do {
			if (type != "MIDI") {
				getline(ficLire, nom);
				if (nom[0] == '-') {
					type = nom.substr(1, nom.size() - 1);
					nom = type;
				}
			}
			else if (type == "MIDI") {
				ficLire >> nom;
				if (nom[0] == '-')
					type = nom.substr(1, nom.size() - 1);
			}
			if (type == "MIDI" && nom != type) {
				ficLire >> montant >> coutPlat;
				ajouterPlat(nom, montant, coutPlat);
			}
		} while (type != "SOIR");
		lectureEffectuee = true;
		break;
	case (Soir):
		do {
			if (type != "SOIR") {
				getline(ficLire, nom);
				if (nom[0] == '-') {
					type = nom.substr(1, nom.size() - 1);
					nom = type;
				}	
			}
			else if (type == "SOIR") {
				ficLire >> nom;
				if (nom[0] == '-')
					type = nom.substr(1, nom.size() - 1);
			}
			if (type == "SOIR" && nom != type) {
				ficLire >> montant >> coutPlat;
				ajouterPlat(nom, montant, coutPlat);
			}
			//cout << type << nom << montant << coutPlat << endl;
		} while (type != "TABLES");
		lectureEffectuee = true;
		break;
	}
	ficLire.close();
	return lectureEffectuee;
}

Menu::~Menu()
{

	for (unsigned int i = 0; i < nbPlats_; i++)
		listePlats_[i] = nullptr;
	delete[] listePlats_;
}







