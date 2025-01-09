#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structures.h"
#include "FourmisColonie.h"

#define NB_ZONES 7 // Nombre de zones dans la fourmilière
#define NB_ALERTES 4 // Nombre d'alertes possibles

// Déclarations globales pour les zones et alertes
static char zonesDescriptions[NB_ZONES][200]; // Tableau pour stocker les descriptions des zones
static char alertesDescriptions[NB_ALERTES][200]; // Tableau pour stocker les descriptions des alertes

// Tableau des rôles et PV associés
const char *roles[] = {"Reine", "Mâle", "Soldat", "Architecte", "Nettoyeuse", "Butineuse", "Nourrice"};
const int pvFourmis[] = {300, 100, 120, 120, 120, 120, 120}; // PV des fourmis par type

// Fonction pour afficher l'état de la colonie
void afficherEtatColonie(Colonie *colonie) {
    printf("\n--- État de la colonie ---\n");
    printf("Points de vie de la colonie : %d ❤️\n", colonie->PvColonie); // Affiche les points de vie de la colonie
    printf("Nombre total de fourmis : %d 🐜\n", colonie->nbTotalFourmis); // Affiche le nombre total de fourmis
}

// Fonction pour initialiser les descriptions des zones
void initialiserZones() {
    // Initialisation des descriptions des zones de la fourmilière
    strcpy(zonesDescriptions[ZONE_MONDE_EXTERNE], "Monde externe : Exploration.");
    strcpy(zonesDescriptions[ZONE_ENTREE_PRINCIPALE], "Entrée principale : Accès et passage.");
    strcpy(zonesDescriptions[ZONE_STOCKAGE_NOURRITURE], "Stockage nourriture : Ressources alimentaires.");
    strcpy(zonesDescriptions[ZONE_DEFENSE_COLONIE], "Défense de la colonie : Protection.");
    strcpy(zonesDescriptions[ZONE_CHAMBRE_ROYALE], "Chambre royale : Reine et reproduction.");
    strcpy(zonesDescriptions[ZONE_STOCKAGE_OEUFS], "Stockage des œufs : Soins et développement.");
    strcpy(zonesDescriptions[ZONE_CIMETIERE], "Cimetière : Restes des fourmis mortes.");
}

// Fonction pour affecter une activité à une zone
void affecterActivite(ZoneFourmiliere zone, const char *description) {
    if (zone >= 0 && zone < NB_ZONES) {
        // Copie de la description dans le tableau correspondant à la zone
        strcpy(zonesDescriptions[zone], description);

        // Affichage des informations de la zone
        printf("\nZone (%d) : %s\n", zone, zonesDescriptions[zone]);
    }
}

// Fonction pour initialiser une fourmi et la générer dans la colonie
void initialiserFourmis(Fourmi *colonie, int *index, TypeFourmi type, int nbFourmis, int ageMin, int ageMax) {
    for (int i = 0; i < nbFourmis; i++) {
        colonie[*index].type = type;
        colonie[*index].age = ageMin + (rand() % (ageMax - ageMin + 1)); // Âge aléatoire de la fourmi
        
        // Définir les PV en fonction du type de la fourmi
        colonie[*index].pv = pvFourmis[type];

        // Assignation du statut en fonction de l'âge
        if (colonie[*index].age < 10) {
            colonie[*index].statut = 0;  // Œuf
        } else if (colonie[*index].age < 20) {
            colonie[*index].statut = 1;  // Larve
        } else if (colonie[*index].age < 30) {
            colonie[*index].statut = 2;  // Nymphe
        } else {
            colonie[*index].statut = 3;  // Adulte
        }

        // Durée de vie spécifique selon le type de fourmi
        if (type == REINE) {
            if (colonie[*index].age >= 3650) {  // Si la Reine a 10 ans (3650 jours) ou plus, elle meurt
                colonie[*index].statut = 4;  // Morte
            }
        } else if (type == MALE) {
            if (colonie[*index].age >= 100) {  // Si un Mâle a 100 ans ou plus, il meurt
                colonie[*index].statut = 4;  // Morte
            }
        } else {
            if (colonie[*index].age >= 120) {  // Si une autre fourmi a 120 ans ou plus, elle meurt
                colonie[*index].statut = 4;  // Morte
            }
        }

        (*index)++;
    }
}

// Modification de la fonction genererColonie dans fourmiscolonie.c
void genererColonie(Fourmi *colonie, int *tailleColonie, Colonie *etatColonie) {
    int index = 0;

    // Initialisation de la Reine
    colonie[index].type = REINE;
    colonie[index].age = 300; // Âge de la Reine
    colonie[index].pv = pvFourmis[REINE];
    colonie[index].statut = 3;  // Statut initial de la Reine
    index++;

    // Génération des autres fourmis selon leur type
    initialiserFourmis(colonie, &index, BUTINEUSE, 15, 30, 100);
    initialiserFourmis(colonie, &index, SOLDAT, 15, 30, 100);
    initialiserFourmis(colonie, &index, ARCHITECTE, 7, 30, 100);
    initialiserFourmis(colonie, &index, NETTOYEUSE, 4, 30, 100);
    initialiserFourmis(colonie, &index, NOURRICE, 4, 30, 100);
    initialiserFourmis(colonie, &index, MALE, 4, 30, 60);

    // Mise à jour de la taille de la colonie
    *tailleColonie = index;
    etatColonie->nbTotalFourmis = *tailleColonie;
    etatColonie->PvColonie = 1000 + 10 * (*tailleColonie); // Mise à jour des PV de la colonie
}

// Fonction pour afficher une fourmi
void afficherFourmi(Fourmi fourmi) {
    if (fourmi.statut != 4) { // Ignorer les mortes
        // Affiche les informations d'une fourmi : rôle, âge, statut et PV
        printf("🐜 Rôle: %s, Âge: %d jours, Statut: %d, PV: %d\n", roles[fourmi.type], fourmi.age, fourmi.statut, fourmi.pv);
    }
}

// Fonction pour gérer les morts et vieillir les fourmis
void gererLesMortsEtVieillirFourmis(Fourmi *colonie, int *tailleColonie, Climat *temps, Colonie *etatColonie) {
    int i = 0;
    while (i < *tailleColonie) {
        // Vérifie si la fourmi est morte ou a des PV inférieurs ou égaux à 0
        if (colonie[i].statut == 4 || colonie[i].pv <= 0) {
            printf("Fourmi [%s] âgée de %d jours est morte. 💀\n", roles[colonie[i].type], colonie[i].age);
            for (int j = i; j < *tailleColonie - 1; j++) {
                colonie[j] = colonie[j + 1]; // Retirer la fourmi morte
            }
            (*tailleColonie)--; // Réduire la taille de la colonie
        } else {
            // Vieillir les fourmis actives sauf en hiver ou automne
            if (temps && strcmp(temps->saison, "Automne") != 0 && strcmp(temps->saison, "Hiver") != 0) {
                colonie[i].age++; // Vieillir la fourmi
            }
            i++;
        }
    }
    
    // Mettre à jour le nombre total de fourmis après les morts
    int total = 0;
    for (int i = 0; i < *tailleColonie; i++) {
        if (colonie[i].statut != 4) { total++; } // Ignorer les mortes
    }
    etatColonie->nbTotalFourmis = total;
    printf("\nNombre total de fourmis mis à jour : %d 🐜\n", total);
}

// Fonction pour initialiser les alertes et la communication entre les fourmis
void initialiserAlertes() {
    strcpy(alertesDescriptions[ALERTE_ODEUR], "Alerte Olfactive: Intrus détecté !");
    strcpy(alertesDescriptions[ALERTE_VERIF_VISUELLE], "Alerte Visuelle: Vérification nécessaire.");
    strcpy(alertesDescriptions[ALERTE_SONORE], "Alerte Sonore: Nourriture insuffisante.");
    strcpy(alertesDescriptions[ALERTE_GUIDAGE_TACTILE], "Alerte Tactile: Guidage nécessaire.");
}

// Fonction pour modifier et afficher une alerte
void modifierEtAfficherAlerte(Alerte alerte, const char* description) {
    if (alerte >= 0 && alerte < NB_ALERTES) {
        // Si la description est différente de l'actuelle, on modifie
        if (strcmp(alertesDescriptions[alerte], description) != 0) {
            strcpy(alertesDescriptions[alerte], description); // Mise à jour de la description de l'alerte
        }
        // Affiche l'alerte (modifiée ou non)
        printf("\nAlerte (%d) : %s 🚨\n", alerte, alertesDescriptions[alerte]);
    }
}
