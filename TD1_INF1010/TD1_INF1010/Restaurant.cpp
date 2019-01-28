#include "Restaurant.h"


Restaurant::Restaurant() {
	*nom_ = "inconnu";
	momentJournee_ = Matin;
	chiffreAffaire_ = 0;
	menuMatin_ = nullptr; ////////// vrm pas sur quoi mettre pour tout le reste
	menuMidi_ = nullptr;
	menuSoir_ = nullptr;
	capaciteTables_ = 0;
	nbTables_ = 0;
	tables_ = new Table* [INTTABLES];
	for (int i = 0; i < INTTABLES; i++) {
		tables_[i] = nullptr;
	}
	
}

Restaurant::Restaurant(string& fichier, string& nom, TypeMenu moment) {

	*nom_ = nom;
	momentJournee_ = moment;
	chiffreAffaire_ = 0;
	
	switch (moment) {
	case 0:
		menuMatin_ = &Menu(fichier, moment);
		break;
	case 1:
		menuMidi_ = &Menu(fichier, moment);
		break;
	case 2:
		menuSoir_ = &Menu(fichier, moment);
		break;
	}
	tables_ = new Table*[INTTABLES];
	for (int i = 0; i < INTTABLES; i++) {
		tables_[i] = nullptr;
	}
	lireTable(fichier);
	capaciteTables_ = 0;//////////// a partir d ici je ne suis pas sur
	nbTables_ = 0;
	 
}

void Restaurant::setMoment(TypeMenu moment) {

	momentJournee_ = moment;
}

string Restaurant::getNom() {

	return *nom_;
}

TypeMenu Restaurant::getMoment() {

	return momentJournee_;
}













