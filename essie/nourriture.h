#ifndef NOURRITURE_H
#define NOURRITURE_H

#include "structures.h"
#include "fourmis.h" // Inclusion pour accéder aux fonctions des fourmis

void collecteRessources(Fourmi *colonie, int *taille, StockNourriture *stockNourriture, StockMateriaux *stockMateriaux, const char *saison);
void calculerConsommation(Fourmi *colonie, int tailleColonie, GestionNonAdultes *nonAdultes, GestionConsommation *consommation);
void consommationRessources(Fourmi *colonie, int tailleColonie, StockNourriture *stockNourriture, GestionNonAdultes *nonAdultes);
#endif // NOURRITURE_H
