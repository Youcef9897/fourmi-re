#ifndef NOURRITURE_H
#define NOURRITURE_H

#include "structures.h"
#include "fourmis.h" // Inclusion pour accéder aux fonctions des fourmis

// Fonction pour gérer la collecte des ressources
void collecteRessources(Fourmi *colonie, int *taille, 
                        StockNourriture *stockNourriture, 
                        StockMateriaux *stockMateriaux, 
                        const char *saison);
    
// Fonction pour calculer la consommation de nourriture
void calculerConsommation(Fourmi *colonie, int tailleColonie, 
                          GestionNonAdultes *nonAdultes, 
                          GestionConsommation *consommation);

// Fonction pour gérer la consommation des ressources
void consommationRessources(Fourmi *colonie, int tailleColonie, 
                             StockNourriture *stockNourriture, 
                             GestionNonAdultes *nonAdultes);

#endif // NOURRITURE_H
