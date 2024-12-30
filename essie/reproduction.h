#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include "structures.h"

// Fonction pour gérer la reproduction dans la fourmilière
void reproduction(Fourmi *colonie, int *tailleColonie, GestionNonAdultes *gestionNonAdultes, StockNourriture *stockNourriture, int nbOeufs);

// Fonction pour déposer des œufs dans la colonie
void deposerOeufs(Fourmi *colonie, int *tailleColonie, int nbOeufs);

// Fonction pour faire évoluer les non-adultes (œufs -> larves -> nymphes -> adultes)
void evoluerNonAdultes(Fourmi *colonie, int *tailleColonie, GestionNonAdultes *gestionNonAdultes);

// Fonction pour afficher les états des non-adultes (œufs, larves, nymphes)
void afficherNonAdultes(GestionNonAdultes *gestionNonAdultes);

// Fonction pour consommer des ressources pour les non-adultes (œufs, larves, nymphes)
void consommerRessourcesNonAdultes(GestionNonAdultes *gestionNonAdultes, StockNourriture *stockNourriture);

#endif // REPRODUCTION_H
