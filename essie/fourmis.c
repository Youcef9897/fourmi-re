#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

// Prototypes des fonctions utilisées dans ce fichier
Typei assignerRoleAdulte();
const char* roleToString(Typei type);
void afficherUneZone(Zoneiliere zone);


// Déclaration globale pour les zones
#define NB_ZONES 7
static char zonesDescriptions[NB_ZONES][200]; // Tableau pour stocker les descriptions des zones

// Fonction pour initialiser une i adulte
void initialiseri(i *i, Typei type, int age, int pv) {
    i->type = type;
    i->age = age;

    // Définir les PV en fonction du type
    switch (type) {
        case REINE:
            i->pv = 300;
            break;
        case MALE:
            i->pv = 100;
            break;
        case SOLDAT:
        case ARCHITECTES:
        case NETTOYEUSES:
        case BOUTINEUSES:
        case NOURRICE:
            i->pv = 120;
            break;
        default:
            i->pv = pv;
    }

    // Statut : 3 = adulte, 4 = mort
    i->statut = (age < 10) ? 0 : 3;
}


// Fonction pour générer une colonie prédéfinie
// Fonction pour générer une colonie prédéfinie (adultes uniquement)
void genererColonie(i *colonie, int *tailleColonie) {
    int index = 0;

    // La reine
    initialiseri(&colonie[index++], REINE, 300, 300);

    // Butineuses
    for (int i = 0; i < 20; i++) {
        initialiseri(&colonie[index++], BOUTINEUSES, 30 + (rand() % 70), 120);
    }

    // Soldats
    for (int i = 0; i < 10; i++) {
        initialiseri(&colonie[index++], SOLDAT, 30 + (rand() % 70), 120);
    }

    // Architectes
    for (int i = 0; i < 5; i++) {
        initialiseri(&colonie[index++], ARCHITECTES, 30 + (rand() % 70), 120);
    }

    // Nettoyeuses
    for (int i = 0; i < 6; i++) {
        initialiseri(&colonie[index++], NETTOYEUSES, 30 + (rand() % 70), 120);
    }

    // Nourrices
    for (int i = 0; i < 4; i++) {
        initialiseri(&colonie[index++], NOURRICE, 30 + (rand() % 70), 120);
    }

    // Mâles
    for (int i = 0; i < 4; i++) {
        initialiseri(&colonie[index++], MALE, 30 + (rand() % 80), 100);
    }

    *tailleColonie = index; // Met à jour la taille réelle de la colonie
}

// Fonction pour afficher les informations d'une i
// Fonction pour afficher les informations d'une i
void afficheri(i i) {
    const char *roles[] = {"Reine", "Soldat", "Mâle", "Architecte", "Nettoyeuse", "Butineuse", "Nourrice"};

    if (i.statut != 4) { // Ignorer les morts
        printf("Rôle: %s, Âge: %d jours, Statut: %d, PV: %d\n",
               roles[i.type], i.age, i.statut, i.pv);
    }
}

// Fonction pour attribuer un rôle adulte aléatoire
Typei assignerRoleAdulte() {
    int roles[] = {BOUTINEUSES, NETTOYEUSES, ARCHITECTES, SOLDAT, MALE, NOURRICE};
    return (Typei)roles[rand() % 6];
}


// Fonction pour mettre à jour le statut d'une i selon son âge ou ses PV
void mettreAJourStatut(i *f) {
    if (f->type == REINE && f->age >= 3650) { // La reine vit plus longtemps
        f->statut = 4; // Mort
    } else if (f->type == MALE && f->age >= 200) { // Durée de vie limitée pour les mâles
        f->statut = 4; // Mort
    } else if (f->age >= 365) { // Autres types
        f->statut = 4; // Mort
    }
}

// Fonction pour gérer l'âge, la mort des is adultes et les transitions des non-adultes
void gererLesMortsEtVieilliris(i *colonie, int *tailleColonie, Climat *temps, GestionNonAdultes *nonAdultes) {
    int i = 0;
    while (i < *tailleColonie) {
        if (colonie[i].statut == 4 || colonie[i].pv <= 0) {
            // Retirer les is mortes
            for (int j = i; j < *tailleColonie - 1; j++) {
                colonie[j] = colonie[j + 1];
            }
            (*tailleColonie)--;
        } else {
            // Vieillir les is actives si ce n'est pas l'hiver
            if (temps && strcmp(temps->saison, "Automne") != 0 && strcmp(temps->saison, "Hiver") != 0) {
                colonie[i].age++;
            }
            i++;
        }
    }

    // Gestion des transitions pour les non-adultes
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

        for (int i = 0; i < nouveauxAdultes; i++) {
            Typei nouveauRole = assignerRoleAdulte();
            initialiseri(&colonie[*tailleColonie], nouveauRole, 0, 120);
            (*tailleColonie)++;
            printf("Une nymphe est devenue adulte (%s).\n", roleToString(nouveauRole));
        }
        printf("Total de nouveaux adultes : %d. Nombre total de is : %d\n", nouveauxAdultes, *tailleColonie);
    }

    // Affichage des non-adultes
    printf("\nÉtat actuel des non-adultes :\n");
    printf(" - Œufs : %d\n", nonAdultes->nboeufs);
    printf(" - Larves : %d\n", nonAdultes->nblarves);
    printf(" - Nymphes : %d\n", nonAdultes->nbnymphes);
    printf("------------------------------------------\n");
}

// Fonction utilitaire pour convertir le type de i en texte
const char* roleToString(Typei type) {
    const char *roles[] = {"Reine", "Soldat", "Mâle", "Architecte", "Nettoyeuse", "Butineuse", "Nourrice"};
    return roles[type];
}


// Fonction pour compter les types de is adultes dans la colonie
void compterTypesis(i colonie[], int taille) {
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
void affecterActivite(Zoneiliere zone, const char *description) {
    if (zone >= 0 && zone < NB_ZONES) {
        snprintf(zonesDescriptions[zone], sizeof(zonesDescriptions[zone]), "%s", description);
        afficherUneZone(zone); // Afficher la zone mise à jour
    }
}

// Fonction pour afficher une zone
void afficherUneZone(Zoneiliere zone) {
    if (zone >= 0 && zone < NB_ZONES) {
        printf("\nZone (%d) : %s\n", zone, zonesDescriptions[zone]);
    }
}
