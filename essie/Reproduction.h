#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include "structures.h"

// Fonction pour gérer la reproduction dans la colonie, incluant un facteur temporel
void reproduction(Fourmi *colonie, int *tailleColonie, GestionReproduction *gestionRepgestionReproduction, StockNourriture *stockNourriture, int nbOeufs);

// Fonction pour faire évoluer les non-adultes (œufs -> larves -> nymphes -> adultes)
void evoluerNonAdultes(Fourmi *colonie, int *tailleColonie, GestionReproduction *gestionReproduction);

// Fonction pour consommer des ressources pour les non-adultes
void consommationRessourcesNonAdultes(GestionReproduction *gestionReproduction, StockNourriture *stockNourriture);

// Fonction pour afficher l'état des non-adultes (œufs, larves, nymphes)
void afficherNonAdultes(GestionReproduction *gestionReproduction);

#endif // REPRODUCTION_H
