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
	for (int i = 0; i < capacite_; i++)
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
	for (int i = 0; i < capacite_; i++)
		commande_[i] = nullptr; // felix: methode de lecture??
	// felix: lireMenu() //wtf???
}

int Table::getId()
{
	return id_;
}

int Table::getNbPlaces()
{
	return nbPlaces_;
}

bool Table::estOccupee()
{
	return occupee_; 
}

void Table::libererTable()
{
	delete[] commande_;
	for (int i = 0; i < capacite_; i++)
		commande_[i] = nullptr; // felix: qu est ce qu il faut effacer
	occupee_ = false;
}

void Table::placerClient()
{
	occupee_ = true; //   felix: dont know wtf is going on here...
}

void Table::setId(int id)
{
	id_ = id;
}

void Table::commander(Plat* plat)
{
	if (nbPlats_ == capacite_) {
		Plat** copieCommande = new Plat*[capacite_];
		for (int i = 0; i < capacite_; i++)
			copieCommande[i] = commande_[i];
		capacite_ *= 2;
		delete[] commande_;
		commande_ = new Plat*[capacite_];
		for (int i = 0; i < (capacite_ / 2); i++)
			commande_[i] = copieCommande[i];
		for (int i = (capacite_ / 2); i < capacite_; i++)
			commande_[i] = nullptr;
		delete[] copieCommande;
		for (int i = 0; i < (capacite_ / 2); i++)
			copieCommande[i] = nullptr;
	}
	commande_[nbPlats_] = plat;
	nbPlats_++;
}

double Table::getChiffreAffaire()
{
	double coutTotal = 0, prixTotal = 0;
	for (int i = 0; i < capacite_; i++) {
		coutTotal += commande_[i]->getCout;
		prixTotal += commande_[i]->getPrix;
	}
	double chiffreAffaire = prixTotal - coutTotal;
	return chiffreAffaire;
}

void Table::afficher()
{
	if (occupee_) {
		cout << "La table ", id_, "a ", nbPlaces_, "places et elle est occupée.";
		cout << endl << "Voici la commande des clients: " << endl;
		for (int i = 0; i < nbPlats_; i++) 
			commande_[i]->afficher;
	}
	else {
		cout << "La table ", id_, "a ", nbPlaces_, "places et elle est libre.";
		cout << endl;
	}

}