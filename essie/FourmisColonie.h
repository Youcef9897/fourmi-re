#ifndef FOURMIS_H
#define FOURMIS_H

#include "structures.h" // Inclusion du fichier d'en-tête contenant les structures utilisées

// Déclarations des fonctions

// Affiche l'état actuel de la colonie
void afficherEtatColonie(Colonie *colonie);

// Initialise les zones de la fourmilière
void initialiserZones();

// Affecte une activité à une zone de la fourmilière avec une description
void affecterActivite(ZoneFourmiliere zone, const char *description);

// Initialise les fourmis dans la colonie avec des paramètres spécifiques
void initialiserFourmis(Fourmi *colonie, int *index, TypeFourmi type, int nbFourmis, int ageMin, int ageMax);

// Génère la colonie de fourmis et met à jour son état
void genererColonie(Fourmi *colonie, int *tailleColonie, Colonie *etatColonie);

// Affiche les informations d'une fourmi
void afficherFourmi(Fourmi fourmi);

// Gère les morts et le vieillissement des fourmis dans la colonie en fonction du climat et de l'état de la colonie
void gererLesMortsEtVieillirFourmis(Fourmi *colonie, int *tailleColonie, Climat *temps, Colonie *etatColonie);

// Initialise les alertes pour la colonie
void initialiserAlertes();

// Modifie une alerte et affiche sa nouvelle description
void modifierEtAfficherAlerte(Alerte alerte, const char* description);

#endif // FOURMISCOLONIE_H
