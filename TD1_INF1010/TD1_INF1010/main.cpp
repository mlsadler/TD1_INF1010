/*
* Titre : main.cpp - Travail Pratique #1
* Date : 09 Janvier 2019 
* Auteur : David Dratwa
*/

#include "Restaurant.h"
#include <string>

using namespace std; 

int main() {

	//creation du restaurant - avec le fichier donne - le nom : PolyFood - moment de la journee : soir. 
	string fichier = "polyfood.txt";
	string nomRestaurant = "PolyFood";
	Restaurant polyfood ("Polyfood.txt", nomRestaurant, Soir);


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
	polyfood.commanderPlat("Poisson", 1);
	polyfood.commanderPlat("Poulet", 2);
	polyfood.commanderPlat("Pizza", 2);
	polyfood.commanderPlat("Poulet", 4);
	polyfood.commanderPlat("Muffin", 4);
	polyfood.commanderPlat("Oeuf", 4);
	

	//afficher le restaurant
	////////////////////////////////poly.afficher(); 

	cout << "-------------------------------------------------" << endl; 

	//liberer les tables 

	//afficher le restaurant 
	/////////////////////////////////poly.afficher(); 
	return 0;

}