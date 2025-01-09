#ifndef COMBAT_H
#define COMBAT_H

#include "FourmisColonie.h"
#include "structures.h"

// Initialisation des ennemis (prédateurs ou autres)
void initialiserEnnemi(void *ennemi, int isPredateur);

// Gestion du combat entre les soldats et les ennemis
void combat(void *ennemi, Fourmi *soldat, Colonie *etatColonie, StockNourriture *stockNourriture, int isPredateur);

// Lancement du combat pour toute la colonie
void lancerCombat(Fourmi *colonie, int tailleColonie, Colonie *etatColonie, StockNourriture *stockNourriture);

#endif
