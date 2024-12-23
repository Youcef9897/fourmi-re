#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

// Prototypes des fonctions utilisées dans ce fichier
TypeFourmi assignerRoleAdulte();
const char* roleToString(TypeFourmi type);
void afficherUneZone(ZoneFourmiliere zone);


// Déclaration globale pour les zones
#define NB_ZONES 7
static char zonesDescriptions[NB_ZONES][200]; // Tableau pour stocker les descriptions des zones

// Fonction pour initialiser une i adulte
#define NB_ZONES 7
static char zonesDescriptions[NB_ZONES][200]; // Tableau pour stocker les descriptions des zones

// Fonction pour initialiser une fourmi adulte
void initialiserFourmi(Fourmi *fourmi, TypeFourmi type, int age, int pv) {
    fourmi->type = type;
    fourmi->age = age;

    // Définir les PV en fonction du type
    switch (type) {
        case REINE:
            fourmi->pv = 300;
            break;
        case MALE:
            fourmi->pv = 100;
            break;
        case SOLDAT:
        case ARCHITECTES:
        case NETTOYEUSES:
        case BOUTINEUSES:
        case NOURRICE:
            fourmi->pv = 120;
            break;
        default:
            fourmi->pv = pv;
    }

    // Statut : 3 = adulte, 4 = mort
    fourmi->statut = (age < 10) ? 0 : 3;
}

// Fonction pour générer une colonie prédéfinie
void genererColonie(Fourmi *colonie, int *tailleColonie) {
    int index = 0;

    // La reine
    initialiserFourmi(&colonie[index++], REINE, 300, 300);

    // Butineuses
    for (int i = 0; i < 20; i++) {
        initialiserFourmi(&colonie[index++], BOUTINEUSES, 30 + (rand() % 70), 120);
    }

    // Soldats
    for (int i = 0; i < 10; i++) {
        initialiserFourmi(&colonie[index++], SOLDAT, 30 + (rand() % 70), 120);
    }

    // Architectes
    for (int i = 0; i < 5; i++) {
        initialiserFourmi(&colonie[index++], ARCHITECTES, 30 + (rand() % 70), 120);
    }

    // Nettoyeuses
    for (int i = 0; i < 6; i++) {
        initialiserFourmi(&colonie[index++], NETTOYEUSES, 30 + (rand() % 70), 120);
    }

    // Nourrices
    for (int i = 0; i < 4; i++) {
        initialiserFourmi(&colonie[index++], NOURRICE, 30 + (rand() % 70), 120);
    }

    // Mâles
    for (int i = 0; i < 4; i++) {
        initialiserFourmi(&colonie[index++], MALE, 30 + (rand() % 80), 100);
    }

    *tailleColonie = index; // Met à jour la taille réelle de la colonie
}

// Fonction pour afficher les informations d'une fourmi
void afficherFourmi(Fourmi fourmi) {
    const char *roles[] = {"Reine", "Soldat", "Mâle", "Architecte", "Nettoyeuse", "Butineuse", "Nourrice"};

    if (fourmi.statut != 4) { // Ignorer les morts
        printf("Rôle: %s, Âge: %d jours, Statut: %d, PV: %d\n",
               roles[fourmi.type], fourmi.age, fourmi.statut, fourmi.pv);
    }
}

// Fonction pour attribuer un rôle adulte aléatoire
TypeFourmi assignerRoleAdulte() {
    TypeFourmi roles[] = {BOUTINEUSES, NETTOYEUSES, ARCHITECTES, SOLDAT, MALE, NOURRICE};
    return roles[rand() % 6];
}

// Fonction pour mettre à jour le statut d'une fourmi selon son âge ou ses PV
void mettreAJourStatut(Fourmi *f) {
    if (f->type == REINE && f->age >= 3650) { // La reine vit plus longtemps
        f->statut = 4; // Mort
    } else if (f->type == MALE && f->age >= 200) { // Durée de vie limitée pour les mâles
        f->statut = 4; // Mort
    } else if (f->age >= 365) { // Autres types
        f->statut = 4; // Mort
    }
}

// Fonction pour gérer l'âge, la mort des is adultes et les transitions des non-adultes
void gererLesMortsEtVieillirFourmis(Fourmi *colonie, int *tailleColonie, Climat *temps, GestionNonAdultes *nonAdultes) {
    int i = 0;

    // Parcours des fourmis pour gérer les morts et vieillir les vivants
    while (i < *tailleColonie) {
        if (colonie[i].statut == 4 || colonie[i].pv <= 0) { // Fourmi morte
            // Retirer la fourmi morte en décalant les éléments suivants
            for (int j = i; j < *tailleColonie - 1; j++) {
                colonie[j] = colonie[j + 1];
            }
            (*tailleColonie)--; // Réduire la taille de la colonie
        } else {
            // Vieillir les fourmis actives sauf en hiver ou en automne
            if (temps && strcmp(temps->saison, "Automne") != 0 && strcmp(temps->saison, "Hiver") != 0) {
                colonie[i].age++;
            }
            i++; // Passer à la fourmi suivante
        }
    }

    // Gestion des transitions des non-adultes (œufs → larves → nymphes → adultes)
    printf("\n--- Transition des non-adultes ---\n");

    // Œufs → Larves
    if (nonAdultes->nboeufs >= 5) {
        int nouvellesLarves = nonAdultes->nboeufs / 5;
        nonAdultes->nboeufs -= nouvellesLarves * 5;
        nonAdultes->nblarves += nouvellesLarves;
        printf("%d œufs sont devenus des larves. Total de larves : %d\n", nouvellesLarves, nonAdultes->nblarves);
    }

    // Larves → Nymphes
    if (nonAdultes->nblarves >= 5) {
        int nouvellesNymphes = nonAdultes->nblarves / 5;
        nonAdultes->nblarves -= nouvellesNymphes * 5;
        nonAdultes->nbnymphes += nouvellesNymphes;
        printf("%d larves sont devenues des nymphes. Total de nymphes : %d\n", nouvellesNymphes, nonAdultes->nbnymphes);
    }

    // Nymphes → Adultes
    if (nonAdultes->nbnymphes >= 5) {
        int nouveauxAdultes = nonAdultes->nbnymphes / 5;
        nonAdultes->nbnymphes -= nouveauxAdultes * 5;

        for (int j = 0; j < nouveauxAdultes; j++) {
            TypeFourmi nouveauRole = assignerRoleAdulte(); // Rôle aléatoire
            initialiserFourmi(&colonie[*tailleColonie], nouveauRole, 0, 120);
            (*tailleColonie)++;
            printf("Une nymphe est devenue adulte (%s).\n", roleToString(nouveauRole));
        }
        printf("Total de nouveaux adultes : %d. Nombre total de fourmis : %d\n", nouveauxAdultes, *tailleColonie);
    }

    // Affichage des non-adultes
    printf("\nÉtat actuel des non-adultes :\n");
    printf(" - Œufs : %d\n", nonAdultes->nboeufs);
    printf(" - Larves : %d\n", nonAdultes->nblarves);
    printf(" - Nymphes : %d\n", nonAdultes->nbnymphes);
    printf("------------------------------------------\n");
}

// Fonction utilitaire pour convertir le type de fourmi en texte
const char* roleToString(TypeFourmi type) {
    const char *roles[] = {"Reine", "Soldat", "Mâle", "Architecte", "Nettoyeuse", "Butineuse", "Nourrice"};
    return roles[type];
}

// Fonction pour compter les types de is adultes dans la colonie
void compterTypesis(Fourmi colonie[], int taille) {
    int counts[7] = {0};

    for (int i = 0; i < taille; i++) {
        if (colonie[i].statut != 4) { // Ignorer les morts
            counts[colonie[i].type]++;
        }
    }

    const char *roles[] = {"Reine", "Soldat", "Mâle", "Architecte", "Nettoyeuse", "Butineuse", "Nourrice"};
    printf("\n--- Répartition des is adultes ---\n");
    for (int i = 0; i < 7; i++) {
        printf(" - %s : %d\n", roles[i], counts[i]);
    }
    printf("----------------------------------------\n");
}

// Fonction pour initialiser les descriptions des zones
void initialiserZones() {
    strcpy(zonesDescriptions[ZONE_MONDE_EXTERNE], "Monde externe : Exploration.");
    strcpy(zonesDescriptions[ZONE_ENTREE_PRINCIPALE], "Entrée principale : Accès et passage.");
    strcpy(zonesDescriptions[ZONE_STOCKAGE_NOURRITURE], "Stockage nourriture : Ressources alimentaires.");
    strcpy(zonesDescriptions[ZONE_DEFENSE_COLONIE], "Défense de la colonie : Protection.");
    strcpy(zonesDescriptions[ZONE_CHAMBRE_ROYALE], "Chambre royale : Reine et reproduction.");
    strcpy(zonesDescriptions[ZONE_STOCKAGE_OEUFS], "Stockage des œufs : Soins et développement.");
    strcpy(zonesDescriptions[ZONE_CIMETIERE], "Cimetière : Restes des is.");
}

// Fonction pour affecter une activité à une zone
void affecterActivite(ZoneFourmiliere zone, const char *description) {
    if (zone >= 0 && zone < NB_ZONES) {
        snprintf(zonesDescriptions[zone], sizeof(zonesDescriptions[zone]), "%s", description);
        afficherUneZone(zone); // Afficher la zone mise à jour
    }
}

    

// Fonction pour afficher une zone
void afficherUneZone(ZoneFourmiliere zone) {
    if (zone >= 0 && zone < NB_ZONES) {
        printf("\nZone (%d) : %s\n", zone, zonesDescriptions[zone]);
    }
}
