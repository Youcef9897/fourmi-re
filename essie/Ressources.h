#ifndef NOURRITURE_H
#define NOURRITURE_H

#include "structures.h"
#include "fourmis.h" // Inclusion pour accéder aux fonctions des fourmis

// Fonction pour collecter de la nourriture par les fourmis
void collecteNourriture(Fourmi *colonie, int taille, StockNourriture *stockNourriture, const char *saison);

// Fonction pour collecter des matériaux par les fourmis
void collecteMateriaux(Fourmi *colonie, int taille, StockMateriaux *stockMateriaux, Colonie *etatColonie);

// Fonction pour gérer la consommation de nourriture par les fourmis
void consommationNourriture(Fourmi *colonie, int tailleColonie, StockNourriture *stockNourriture);

#endif // NOURRITURE_H
