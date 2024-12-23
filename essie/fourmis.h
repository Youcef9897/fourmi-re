#ifndef FOURMIS_H
#define FOURMIS_H

#include "structures.h"

// Déclaration des fonctions
void gererLesMortsEtVieillirFourmis(Fourmi *colonie, int *tailleColonie, Climat *temps, GestionNonAdultes *nonAdultes);
void genererColonie(Fourmi *colonie, int *tailleColonie);
void initialiserFourmi(Fourmi *fourmi, TypeFourmi type, int age, int pv);
void afficherFourmi(Fourmi fourmi);
TypeFourmi assignerRoleAdulte();
const char* roleToString(TypeFourmi type);
void mettreAJourStatut(Fourmi *f);
void affecterActivite(ZoneFourmiliere zone, const char *description);
void afficherUneZone(ZoneFourmiliere zone);
void compterTypesFourmis(Fourmi colonie[], int taille);
void initialiserZones();

#endif // FOURMIS_H
