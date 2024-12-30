#ifndef COMBAT_H
#define COMBAT_H

#include "fourmis.h"
#include "structures.h"

float calculerProbabiliteCoupMortel(int pvEnnemie, int pvDefenseur);  // Modification du type de retour en float
void combatFourmis(Fourmi *Ennemie, Fourmi *soldat);
void lancerCombat(Fourmi *colonie, int tailleColonie);

#endif
