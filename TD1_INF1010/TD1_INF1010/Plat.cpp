/****************************************************************************
 * Fichier: Plat.h
 * Auteur: Mark Weber-Sadler() et Félix Dumont(1954787)
 * Date: 4 février 2019
 * Description: Implémentation de la classe Point
 ****************************************************************************/

#include "Plat.h"


 /****************************************************************************
  * Fonction: Point::Point
  * Description: Constructeur par défaut
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/

Plat::Plat() 
{
	nom_ = "inconnu";
	prix_ = 0;
	cout_ = 0;
}

Plat::Plat(string nom, double prix, double cout) 
{
	nom_ = nom;
	prix_ = prix;
	cout_ = cout;
}


string Plat::getNom()
{
	return nom_;
}


double Plat::getPrix() 
{
	return prix_;
}

double Plat::getCout()
{
	return cout_;
}

void Plat::setNom(string nom) 
{
	nom_ = nom;
}

void Plat::setPrix(double prix)
{
	prix_ = prix;
}

void Plat::afficher()
{
	cout << "Le nom du plat est ", nom_, " avec un prix de ", prix_, " associer avec un coup de ", cout_, '.';
	cout << endl;
}






