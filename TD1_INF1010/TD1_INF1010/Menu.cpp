/****************************************************************************
 * Fichier: Menu.cpp
 * Auteur: Mark Weber-Sadler et Felix Dumont
 * Date: 4 fevrier 2019
 * Description: Implémentation de la classe Menu
 ****************************************************************************/

#include "Menu.h"


 /****************************************************************************
  * Description: Constructeur par default
  * in: 
  * out: 
  * in \ out: 
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

/****************************************************************************
  * Description: Constructeur avec parametre
  * in: fichier et type
  * out: 
  * in \ out:
  ****************************************************************************/
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

/****************************************************************************
  * Description: Retourne le nombre de plats dans la liste
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
int Menu::getNbPlats() const
{
	return nbPlats_;
}

/****************************************************************************
  * Description: Afficher tous les plats du menu
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
void Menu::afficher() const
{
	cout << "Voici ce qu'il y a sur le menu: " << endl;
	for (int i = 0; i < getNbPlats(); i++) 
		listePlats_[i]->afficher();
}

/****************************************************************************
  * Description: Fonction qui trouve le un plat avec l'aide d'un nom dans la liste et retourne le pointeur du plat
  * in: nom
  * out:
  * in \ out:
  ****************************************************************************/
Plat* Menu::trouverPlat(const string& nom) const
{
	
	for (unsigned int i = 0; i < nbPlats_; i++) {
		if (listePlats_[i]->getNom() == nom) 
			return listePlats_[i];
	}
	return nullptr;
}

/****************************************************************************
  * Description: Fonction qui ajoute un plat dans la liste du menu avec l'aide d'un plat
  * in: plat
  * out:
  * in \ out:
  ****************************************************************************/
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

/****************************************************************************
  * Description: Ajoute un plat a la liste en creant un variable plat avec l'aide de prametre
  * in: nom, montant et cout
  * out:
  * in \ out:
  ****************************************************************************/
void Menu::ajouterPlat(const string& nom, double montant, double cout)
{
	Plat* plat= new Plat(nom, montant, cout);
	ajouterPlat(*plat);
}

/****************************************************************************
  * Description: Fonction qui le lit un fichier et cree un menu
  * in: fichier
  * out:
  * in \ out:
  ****************************************************************************/
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

/****************************************************************************
  * Description: Fonction qui suprime toutes les vriables
  * in:
  * out:
  * in \ out:
  ****************************************************************************/
Menu::~Menu()
{

	for (unsigned int i = 0; i < nbPlats_; i++)
		listePlats_[i] = nullptr;
	delete[] listePlats_;
}







