/****************************************************************************
 * Fichier: Restaurant.cpp
 * Auteur: Mark Weber-Sadler et Felix Dumont
 * Date: 4 fevrier 2019
 * Description: Implémentation de la classe Restaurant
 ****************************************************************************/

#include "Restaurant.h"

/****************************************************************************
 * Description: Constructeur par default
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
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

/***************************************************************************
 * Description: Constucteur avec l'aide de parametre
 * in: fichier, nom et moment
 * out:
 * in \ out:
 ****************************************************************************/
Restaurant::Restaurant(const string& fichier, const string& nom, TypeMenu moment) 
{
	
	nom_ = new string(nom);
	momentJournee_ = moment;
	chiffreAffaire_ = 0;
	
	switch (moment) {
	case 0:
		menuMatin_ = new Menu(fichier, moment);
		menuMidi_ = new Menu();
		menuSoir_ = new Menu();
		break;
	case 1:
		menuMidi_ = new Menu(fichier, moment);
		menuMatin_ = new Menu();
		menuSoir_ = new Menu();
		break;
	case 2:
		menuSoir_ = new Menu(fichier, moment); 
		menuMatin_ = new Menu();
		menuMidi_ = new Menu();
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

/***************************************************************************
 * Description: Fonction qui set la variable au moment voulu
 * in: moment
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::setMoment(TypeMenu moment) {

	momentJournee_ = moment;
}

/***************************************************************************
 * Description: Fonction qui retourne le nomdu restaurant
 * in: 
 * out:
 * in \ out:
 ****************************************************************************/
string Restaurant::getNom() const{

	return *nom_;
}

/***************************************************************************
 * Description: Fonction qui retourne le moment de la journee
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
TypeMenu Restaurant::getMoment() const{

	return momentJournee_;
}

/***************************************************************************
 * Description: Fonction qui lira le document et cree un variable table
 * in: fichier
 * out:
 * in \ out:
 ****************************************************************************/
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
		ajouterTable(id, nbPlaces);
		nbTables_++;
	}

	ficLire.close();
}

/***************************************************************************
 * Description: Fonction qui ajoute une table dans la liste de table
 * in: id et nbPlaces
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::ajouterTable(int id, int nbPlaces){
	if(capaciteTables_==nbTables_){
		capaciteTables_ *= 2;
		Table** copieTable = new Table*[capaciteTables_];
		for(unsigned int i=0;i<nbTables_;i++)
			copieTable[i] = tables_[i];

		delete[] tables_;
		tables_ = copieTable;
		
	}
	Table* table= new Table(id,nbPlaces);
	tables_[nbTables_] = table; 
	
}

/***************************************************************************
 * Description: Fonction qui libere un table et calcul le chiffre d'affaire
 * in: id
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::libererTable(int id){
	int placeListeTable;

	for (int i = 0; i < nbTables_; i++) {
		if (tables_[i]->getId() == id) {
			placeListeTable = i;
		}
	}
	

	chiffreAffaire_+= tables_[placeListeTable]->getChiffreAffaire();
	tables_[placeListeTable]->libererTable();
	
}

/***************************************************************************
 * Description: Fonction pour commander des plats
 * in: nom et idTable
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::commanderPlat(const string & nom, int idTable){
	int placeListeTable;

	for (int i = 0; i < nbTables_; i++) {
		if (tables_[i]->getId() == idTable) {
			placeListeTable = i;
			
		}
	}
	
	switch (momentJournee_) {
	case 0:
		tables_[placeListeTable]->commander(menuMatin_->trouverPlat(nom));
		break;
	case 1:
		tables_[placeListeTable]->commander(menuMidi_->trouverPlat(nom));
		break;
	case 2:
		
		tables_[placeListeTable]->commander(menuSoir_->trouverPlat(nom));
		break;
	}

}


/***************************************************************************
 * Description: Fonction pour placer les clients a une table
 * in: nbClients
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::placerClients(int nbClients)
{

	int id, nbPlaceLibre,nbPlaceMin = 400, placeListeTable; //Nous avons choisi de mettre nbPlaceMin a 400, car nous assumons que les tables aurons pas plus de 400 place
	bool tableTrouver = false;
	bool occupation;
	double nbPlaceTable, idTable;

	

	for (unsigned int i = 0; i < nbTables_; i++) 

		if (tables_[i]->estOccupee() == false) 
			
			if (tables_[i]->getNbPlaces() >= nbClients) {
				nbPlaceLibre = (tables_[i]->getNbPlaces() - nbClients);
				
				if (nbPlaceLibre < nbPlaceMin) {
					
					id = tables_[i]->getId();
					nbPlaceMin = nbPlaceLibre;
					tableTrouver = true;
				}
			}
		
	
	if (tableTrouver) {
		for (int i = 0; i < nbTables_; i++) {
			if (tables_[i]->getId() == id) {
				placeListeTable = i;
			}
		}
		tables_[placeListeTable]->placerClient();
	}
		
	
	else 
		cout << "Erreur: Le client ne pouvait pas etre placer pour une quantite insuffisante de table." << endl;
}

/***************************************************************************
 * Description: Fonction pour afficher le restaurant
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
void Restaurant::afficher() const{

	cout << "Le restaurant PolyFood a fait un pofit de: "<< chiffreAffaire_<< "$" <<endl;
	cout << "Les tables et leur disponibilite: " << endl;
	for (unsigned int i = 0; i < nbTables_; i++) {
		
		cout << "La table numero "<< i + 1<< " est ";
		if (tables_[i]->estOccupee()) {
			cout << "prise." << endl;
		}
		else {
			cout << "libre." << endl;
			 
		}


	}

}

/***************************************************************************
 * Description: Destructeur de la classe Restaurant
 * in:
 * out:
 * in \ out:
 ****************************************************************************/
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













