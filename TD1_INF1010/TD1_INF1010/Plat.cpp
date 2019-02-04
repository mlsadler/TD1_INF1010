/****************************************************************************
 * Fichier: Plat.cpp
 * Auteur: Mark Weber-Sadler(1947609) et Félix Dumont(1954787)
 * Date: 4 février 2019
 * Description: Implémentation de la classe Plat
 ****************************************************************************/

#include "Plat.h"


 /****************************************************************************
 * Description: Constructeur par default
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
Plat::Plat() 
{
	nom_ = "inconnu";
	prix_ = 0;
	cout_ = 0;
}

/****************************************************************************
 * Description: Constructeur par parametre
 * in: nom, prix et cout
 * out:
 * in \ out:
 ****************************************************************************/
Plat::Plat(string nom, double prix, double cout) 
{
	nom_ = nom;
	prix_ = prix;
	cout_ = cout;
}

/****************************************************************************
 * Description: Fonction qui retourne le nom du plat
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
string Plat::getNom() const
{
	return nom_;
}

/****************************************************************************
 * Description Fonction qui retourne le prix du plat
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
double Plat::getPrix() const
{
	return prix_;
}

/****************************************************************************
 * Description: Fonction qui retourne le prix
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
double Plat::getCout() const
{
	return cout_;
}

/****************************************************************************
 * Description: Fonction qui met le nom du plat a un nom voulu
 * in: nom
 * out:
 * in \ out:
 ****************************************************************************/
void Plat::setNom(string nom) 
{
	nom_ = nom;
}

/****************************************************************************
 * Description: Fonction qui met le prix a un prix voulu
 * in: prix
 * out:
 * in \ out:
 ****************************************************************************/
void Plat::setPrix(double prix)
{
	prix_ = prix;
}

/****************************************************************************
 * Description: Fonction qui affiche un plat
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
void Plat::afficher() const
{
	cout << "Le nom du plat est " << nom_ << " avec un prix de " << prix_ << " associer avec un cout de " <<  cout_ << '.' << endl;
}

/****************************************************************************
 * Description: Destructeur de la class plat
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
Plat::~Plat(){}





