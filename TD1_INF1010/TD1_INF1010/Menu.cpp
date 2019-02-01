/****************************************************************************
 * Fichier: Point.h
 * Auteur: Georges Abou-Khalil
 * Date: 2 sept 2008
 * Mise a jour : 11 mai 2011
 * Description: Impl�mentation de la classe Point
 ****************************************************************************/

#include "Menu.h"


 /****************************************************************************
  * Fonction: Point::Point
  * Description: Constructeur par d�faut
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
Menu::Menu() 
{
	capacite_ = MAXPLAT;
	nbPlats_ = 0;
	type_ = Matin;
	listePlats_ = new Plat* [capacite_];
	for (int i = 0; i < capacite_; i++) 
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
	for (int i = 0; i < nbPlats_; i++) {
		if (listePlats_[i]->getNom() == nom) 
			return listePlats_[i];
	}
	return nullptr;
}

void Menu::ajouterPlat(Plat& plat)
{
	if (nbPlats_ == capacite_) {
		Plat** copieListe = new Plat*[capacite_];
		for (int i = 0; i < capacite_; i++) //jai modifi� le <= que tavais mis
			copieListe[i] = listePlats_[i];
		capacite_ *= 2;
		delete[] listePlats_;
		listePlats_ = new Plat*[capacite_];
		for (int i = 0; i < (capacite_/2); i++)
			listePlats_[i] = copieListe[i];
		for (int i = (capacite_/2); i < capacite_; i++)
			listePlats_[i] = nullptr;
		
		for (int i = 0; i < (capacite_ / 2); i++)
			copieListe[i] = nullptr;
		delete[] copieListe;
	}
	listePlats_[nbPlats_] = &plat;
	nbPlats_++;	
}

void Menu::ajouterPlat(const string& nom, double montant, double cout)
{
	Plat plat=Plat(nom, montant, cout);
	ajouterPlat(plat);
}

bool Menu::lireMenu(const string& fichier)
{
	ifstream ficLire (fichier);
	string nom, type = "";
	double montant, cout;
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
				 ficLire >> montant >> cout;
				 ajouterPlat(nom, montant, cout);
			 }
		 } while (type != "MIDI");
		 return lectureEffectuee;
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
				ficLire >> montant >> cout;
				ajouterPlat(nom, montant, cout);
			}
		} while (type != "SOIR");
		return lectureEffectuee;
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
				ficLire >> montant >> cout;
				ajouterPlat(nom, montant, cout);
			}
		} while (type != "TABLES");
		return lectureEffectuee;
		break;
	}
	ficLire.close();
	lectureEffectuee = false;
	return lectureEffectuee;
}

Menu::~Menu()
{
	for (int i = 0; i < (capacite_); i++)
		listePlats_[i] = nullptr;
	delete[] listePlats_;
}







