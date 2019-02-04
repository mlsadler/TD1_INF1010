/****************************************************************************
 * Fichier: Table.cpp
 * Auteur: Mark Weber-Sadler et Felix Dumont
 * Date: 4 fevrier 2019
 * Description: Implémentation de la classe Table
 ****************************************************************************/


#include "Table.h"


 /****************************************************************************
  * Description: Constructeur par default
  * in:
  * out:
  * in \ out:
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

/****************************************************************************
 * Description: Constructeur avec parametre
 * in: id et nbPlaces
 * out:
 * in \ out:
 ****************************************************************************/
Table::Table(int id, int nbPlaces)
{
	capacite_ = MAXCAP;
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbPlats_ = 0;
	occupee_ = false;
	commande_ = new Plat*[capacite_];
	for (unsigned int i = 0; i < capacite_; i++)
		commande_[i] = nullptr; 
}

/****************************************************************************
 * Description: Fonction qui retourne le id de la table
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
int Table::getId() const
{
	return id_;
}

/****************************************************************************
 * Description: Fonction qui retourne le nombre de place que la table offre
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
int Table::getNbPlaces() const
{
	return nbPlaces_;
}

/****************************************************************************
 * Description: Fonction qui retourne si la table est occupee ou non
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
bool Table::estOccupee() const
{
	return occupee_; 
}

/****************************************************************************
 * Description: Fonction qui effacera les commandes de la table et la rendera valide pour de nouveau client
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
void Table::libererTable()
{
	
	for (unsigned int i = 0; i < capacite_; i++)
		commande_[i] = nullptr; 
	occupee_ = false;
}

/****************************************************************************
 * Description: Fonction qui rend la table occcupee
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
void Table::placerClient()
{
	occupee_ = true;
}

/****************************************************************************
 * Description: Fonction qui met le id a une valeur voulu
 * in: id
 * out:
 * in \ out:
 ****************************************************************************/
void Table::setId(int id)
{
	id_ = id;
}

/****************************************************************************
 * Description: Fonction qui recoit un plat et qui la place dans une liste de plat commander pour une table
 * in: Plat
 * out:
 * in \ out:
 ****************************************************************************/
void Table::commander(Plat* plat)
{
	if (nbPlats_ == capacite_) {
		capacite_ *= 2;
		Plat** copieCommande = new Plat*[capacite_];
		for (unsigned int i = 0; i < capacite_; i++)
			copieCommande[i] = commande_[i];
		
		delete[] commande_;
		commande_ = copieCommande;
	}
	
	if (plat == nullptr) {
		cout << "Erreur: Le plat n'existe pas dans se menu." << endl;
	}
	else {
		commande_[nbPlats_] = plat;
		nbPlats_++;
	}
	
}

/****************************************************************************
 * Description: Fonction qui calcul le chiffre d'affaire
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
double Table::getChiffreAffaire()
{
	double coutTotal = 0, prixTotal = 0;
	for (unsigned int i = 0; i < nbPlats_; i++) {
		coutTotal += commande_[i]->getCout();
		prixTotal += commande_[i]->getPrix();
	}
	double chiffreAffaire = prixTotal - coutTotal;
	return chiffreAffaire;
}

/****************************************************************************
 * Description: Fonction qui affiche le contenu de la class table
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
void Table::afficher() const
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

/****************************************************************************
 * Description: Destructeur des variables de la class table
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
Table::~Table()
{
	for (unsigned int i = 0; i < capacite_ ; i++)
		commande_[i] = nullptr;
	delete[] commande_;
}