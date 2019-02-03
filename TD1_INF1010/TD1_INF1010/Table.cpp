/****************************************************************************
 * Fichier: Point.h
 * Auteur: Georges Abou-Khalil
 * Date: 2 sept 2008
 * Mise a jour : 11 mai 2011
 * Description: Implémentation de la classe Point
 ****************************************************************************/

#include "Table.h"


 /****************************************************************************
  * Fonction: Point::Point
  * Description: Constructeur par défaut
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/

Table::Table() 
{
	capacite_ = MAXCAP;
	id_ = -1;
	nbPlaces_ = 1;
	nbPlats_ = 0;
	occupee_ = false;
	commande_ = new Plat*[capacite_];
	for (unsigned int i = 0; i < capacite_; i++)
		commande_[i] = nullptr;
}

Table::Table(int id, int nbPlaces)
{
	capacite_ = MAXCAP;
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbPlats_ = 0;
	occupee_ = false;
	commande_ = new Plat*[capacite_];
	for (unsigned int i = 0; i < capacite_; i++)
		commande_[i] = nullptr; // felix: methode de lecture?? ------------------> mark: non c bon c dans la fonction que tu va ajouter des plats mais y faut qui y aille une liste
	// felix: lireMenu() //wtf???
}

int Table::getId() const
{
	return id_;
}

int Table::getNbPlaces() const
{
	return nbPlaces_;
}

bool Table::estOccupee() //const
{
	return occupee_; 
}

void Table::libererTable()
{
	//delete[] commande_; ------------> mark: je pense que c juste la deuxieme affaire on va delete la liste mais qu elle aille rien pour quand les prochain client vont mettre des affaire dedans
	for (unsigned int i = 0; i < capacite_; i++)
		commande_[i] = nullptr; // felix: qu est ce qu il faut effacer --------> mark: check en haut
	occupee_ = false;
}

void Table::placerClient()
{
	occupee_ = true;
}

void Table::setId(int id)
{
	id_ = id;
}

void Table::commander(Plat* plat)
{
	cout << "dsafkllksdfa";
	if (nbPlats_ == capacite_) {
		capacite_ *= 2;
		Plat** copieCommande = new Plat*[capacite_];
		for (unsigned int i = 0; i < capacite_; i++)
			copieCommande[i] = commande_[i];
		
		delete[] commande_;
		commande_ = copieCommande;
	}
	commande_[nbPlats_] = plat;
	nbPlats_++;
}

double Table::getChiffreAffaire()
{
	double coutTotal = 0, prixTotal = 0;
	for (unsigned int i = 0; i < capacite_; i++) {
		coutTotal += commande_[i]->getCout();
		prixTotal += commande_[i]->getPrix();
	}
	double chiffreAffaire = prixTotal - coutTotal;
	return chiffreAffaire;
}

void Table::afficher()
{
	if (occupee_) {
		cout << "La table " << id_ << "a " << nbPlaces_ << "places et elle est occupée."<< endl << "Voici la commande des clients: " << endl;
		for (unsigned int i = 0; i < nbPlats_; i++) 
			commande_[i]->afficher();
	}
	else {
		cout << "La table "<< id_ << "a " << nbPlaces_ << "places et elle est libre." << endl;
	}

}


Table::~Table()
{
	for (unsigned int i = 0; i < capacite_ ; i++)
		commande_[i] = nullptr;
	delete[] commande_;
}