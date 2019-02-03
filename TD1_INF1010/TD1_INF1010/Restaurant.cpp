#include "Restaurant.h"


Restaurant::Restaurant() 
{
	nom_ = new string("inconnu");
	momentJournee_ = Matin;
	chiffreAffaire_ = 0;
	menuMatin_ = new Menu();
	menuMidi_ = new Menu();
	menuSoir_ = new Menu();
	capaciteTables_ = INTTABLES;
	nbTables_ = 0;
	tables_ = new Table* [INTTABLES];
	for (int i = 0; i < INTTABLES; i++) {
		tables_[i] = nullptr;
	}
	
}

Restaurant::Restaurant(const string& fichier, const string& nom, TypeMenu moment) 
{
	
	nom_ = new string(nom);
	momentJournee_ = moment;
	chiffreAffaire_ = 0;
	
	switch (moment) {
	case 0:
		menuMatin_ = new Menu(fichier, moment);
		break;
	case 1:
		menuMidi_ = new Menu(fichier, moment);
		break;
	case 2:
		menuSoir_ = new Menu(fichier, moment); //il entre ici
		break;
	}
	//menuSoir_->afficher(); //test
	tables_ = new Table*[INTTABLES];
	for (int i = 0; i < INTTABLES; i++) {
		tables_[i] = nullptr;
	}
	nbTables_ = 0;
	capaciteTables_ = INTTABLES;
	lireTable(fichier);
}

void Restaurant::setMoment(TypeMenu moment) {

	momentJournee_ = moment;
}

string Restaurant::getNom(){//const

	return *nom_;
}

TypeMenu Restaurant::getMoment() const{

	return momentJournee_;
}

void Restaurant::lireTable(const string & fichier){
	ifstream ficLire (fichier);
	string nom;
	int id;
	unsigned int nbPlaces;

	do {
		ficLire >> nom;
		if (nom[0] == '-')
			nom = nom.substr(1, nom.size() - 1);
	} while (nom != "TABLES");

	while (!ws(ficLire).eof()) {
		ficLire >> id >> nbPlaces;
		nbTables_++;
		ajouterTable(id, nbPlaces);
	}

	ficLire.close();
}

void Restaurant::ajouterTable(int id, int nbPlaces){
	if(capaciteTables_==nbTables_){
		capaciteTables_ *= 2;
		Table** copieTable = new Table*[capaciteTables_];
		for(unsigned int i=0;i<nbTables_;i++)
			copieTable[i] = tables_[i];

		delete[] tables_;
		tables_ = copieTable;
		
	}
	Table table (id, nbPlaces);
	tables_[id - 1] = &table; /////////// ici je cree une table et je vais le mettre dans une liste mais la fonction ne va pas la delete apres????
	
}

void Restaurant::libererTable(int id){//////////// dans la fonction j assume que la liste est toujours assez grande 

	chiffreAffaire_+= tables_[id - 1]->getChiffreAffaire();
	tables_[id - 1]->libererTable();
	
}

void Restaurant::commanderPlat(const string & nom, int idTable){

	switch (momentJournee_) {
	case 0:
		tables_[idTable - 1]->commander(menuMatin_->trouverPlat(nom));
		break;
	case 1:
		tables_[idTable - 1]->commander(menuMidi_->trouverPlat(nom));
		break;
	case 2:
		tables_[idTable - 1]->commander(menuSoir_->trouverPlat(nom));
		break;
	}

}

void Restaurant::placerClients(int nbClients){

	int id, nbPlaceLibre,nbPlaceMin = 400; //infinity
	bool tableTrouver = false;
	bool occupation;
	double nbPlaceTable, idTable;

	cout << "table 0 " << tables_[0]->estOccupee() << endl;
	//cout << "table 1 " << tables_[1]->estOccupee() << endl;
	//cout << "table 2 " << tables_[2]->estOccupee() << endl;
	//cout << "table 3 " << tables_[3]->estOccupee() << endl;
	

	for (unsigned int i = 0; i < nbTables_; i++) {
		occupation = tables_[i]->estOccupee();
		nbPlaceTable = tables_[i]->getNbPlaces();
		idTable = tables_[i]->getId();
		//cout << endl << occupation << " " << nbPlaceTable << " " << idTable;

		if (occupation == false) {
			cout << " test occupe";
			if (tables_[i]->getNbPlaces() >= nbClients) {
				nbPlaceLibre = (tables_[i]->getNbPlaces() - nbClients);
				cout << " table libre";
				if (nbPlaceLibre < nbPlaceMin) {
					cout << " table mini";
					id = tables_[i]->getId();
					nbPlaceMin = nbPlaceLibre;
					tableTrouver = true;
				}
			}
		}
	}
	if (tableTrouver) 
		tables_[id - 1]->placerClient();
	
	else 
		cout << "Erreur: Le client ne pouvait pas etre placer pour une quantite insuffisante de table." << endl;
	


}

void Restaurant::afficher() const{

	cout << "Le restaurant PolyFood a fait un pofit de: "<< chiffreAffaire_<< "$" <<endl;
	cout << "Les tables et leur disponibilite: " << endl;
	for (unsigned int i = 0; i < nbTables_; i++) {
		
		cout << "La table numero "<< i + 1<< " est ";//////////// mark: ici pour le numero de la table je ne suis pas sur de mettre le id ou genre la 4ieme table
		if (tables_[i]->estOccupee()) {
			cout << "libre."<< endl ;
		}
		else {
			cout << "prise." << endl; ////// mark: felix je sais pas comment conjuguer prise
			//////felix: mark...get goood!!!!! pas de s car cest une table
			//
		}


	}

}

Restaurant::~Restaurant()
{
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
	for (unsigned int i = 0; i < capaciteTables_; i++)
		tables_[i] = nullptr;
	delete[] tables_;
}













