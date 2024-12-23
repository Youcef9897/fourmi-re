#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include "structures.h"
#include "fourmis.h"

// Prototypes des fonctions
void reproductionReine(Fourmi *colonie, int *tailleColonie, GestionNonAdultes *nonAdultes, Climat *temps);
void consommationNonAdultes(int nbOeufs, int nbLarves, int nbNymphes, StockNourriture *stockNourriture);

#endif // REPRODUCTION_H
