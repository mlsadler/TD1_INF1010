/*
* Titre : main.cpp - Travail Pratique #1
* Date : 09 Janvier 2019 
* Auteur : David Dratwa
*/

#include "Restaurant.h"
#include <string>
#include <iostream>

using namespace std; 

int main()
{
	cout << "test debut ";
	//creation du restaurant - avec le fichier donne - le nom : PolyFood - moment de la journee : soir. 
	string fichier = "polyFood.txt";
	string nomRestaurant = "PolyFood";
	Restaurant polyfood (fichier, nomRestaurant, Soir); //il entre ici

	//creer plusieurs clients -- des entiers 

	int client1 = 1;  
	int client2 = 5; 
	int client3 = 15; 
	int client4 = 3; 
	int client5 = 2; 
	

	//placer les clients 

	polyfood.placerClients(1);
	polyfood.placerClients(5);
	polyfood.placerClients(15);
	polyfood.placerClients(3);
	polyfood.placerClients(2);




	// commander des plats
	//Poisson - Table 1 
	//Poulet - Table 2 
	//Pizza - Table 2 
	//Poulet - Table 4
	//Muffin - Table 4 
	//Oeuf - Table 4 
	string poisson = "Poisson", poulet = "Poulet", pizza = "pizza", muffin = "muffin", oeuf = "oeuf";
	polyfood.commanderPlat(poisson, 1);
	polyfood.commanderPlat(poulet, 2);
	polyfood.commanderPlat(pizza, 2);
	polyfood.commanderPlat(poulet, 4);
	polyfood.commanderPlat(muffin, 4);
	polyfood.commanderPlat(oeuf, 4);
	

	//afficher le restaurant
	////////////////////////////////poly.afficher(); 
	polyfood.afficher();

	cout << "-------------------------------------------------" << endl; 

	//liberer les tables
	for (int i = 0; i< 4; i++)
		polyfood.libererTable(i);
	

	//afficher le restaurant 
	/////////////////////////////////poly.afficher(); 
	polyfood.afficher();
	return 0;

}