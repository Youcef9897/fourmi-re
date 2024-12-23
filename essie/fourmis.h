#ifndef FOURMIS_H
#define FOURMIS_H

#include "structures.h"

void initialiserFourmi(Fourmi *fourmi, TypeFourmi type, int age, int pv);
void genererColonie(Fourmi *colonie, int *tailleColonie);
void afficherFourmi(Fourmi fourmi);
void mettreAJourStatut(Fourmi *f);
void gererLesMortsEtVieillirFourmis(Fourmi *colonie, int *tailleColonie, Climat *temps, GestionNonAdultes *nonAdultes);
TypeFourmi assignerRoleAdulte();
const char* roleToString(TypeFourmi type);
void compterTypesFourmis(Fourmi colonie[], int taille);
void initialiserZones(); 
void affecterActivite(ZoneFourmiliere zone, const char *description);
void afficherUneZone(ZoneFourmiliere zone);

#endif // FOURMIS_H
