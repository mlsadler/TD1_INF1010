#include "Restaurant.h"


Restaurant::Restaurant() {
	*nom_ = "inconnu";
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
		menuSoir_ = new Menu(fichier, moment);
		break;
	}
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

string Restaurant::getNom() const {

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
		capaciteTables_ += nbPlaces;
		nbTables_++;
		ajouterTable(id, nbPlaces);
		
	}
	ficLire.close();
}

void Restaurant::ajouterTable(int id, int nbPlaces){
	if(capaciteTables_<=nbTables_){
		capaciteTables_ *= 2;
		Table** copieTable = new Table*[capaciteTables_];
		for(int i=0;i<nbTables_;i++)
			copieTable[i] = tables_[i];

		delete[] tables_;
		tables_ = copieTable;
		
	}
	tables_[id-1]= &Table(id, nbPlaces);/////////// ici je cree une table et je vais le mettre dans une liste mais la fonction ne va pas la delete apres????****etoile?

	 
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

	int id, nbPlaceLibre = INFINITY;
	bool tableTrouver=false;

	for (int i = 0; i < nbTables_; i++) 
		if (tables_[i]->estOccupee() == false) 
			if (tables_[i]->getNbPlaces() >= nbClients) 
				if (nbPlaceLibre > tables_[i]->getNbPlaces() - nbClients) {
					id = tables_[i]->getId();
					nbPlaceLibre = tables_[i]->getNbPlaces() - nbClients;
					tableTrouver = true;
				}

	if (tableTrouver) 
		tables_[id - 1]->placerClient();
	
	else {
		cout << "Erreur: Le client ne pouvait pas etre placer pour une quantite insuffisante de table.";
	}


}

void Restaurant::afficher() const{

	cout << "Le restaurant PolyFood a fait un pofit de: ", chiffreAffaire_, "$";
	cout << "Les tables et leur disponibilite: " << endl;
	for (int i = 0; i < nbTables_; i++) {
		
		cout << "La table numero ", i + 1, " est ";//////////// mark: ici pour le numero de la table je ne suis pas sur de mettre le id ou genre la 4ieme table
		if (tables_[i]->estOccupee()) {
			cout << "libre."<<endl ;
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
	for (int i = 0; i < (capaciteTables_); i++)
		tables_[i] = nullptr;
	delete[] tables_;
}













