#include <stdio.h>
#include <string.h>
#include "reproduction.h"
#include "fourmis.h"

// Fonction pour gérer la reproduction de la reine
void reproductionReine(Fourmi *colonie, int *tailleColonie, GestionNonAdultes *nonAdultes, Climat *temps) {
    if (strcmp(temps->saison, "Automne") == 0 || strcmp(temps->saison, "Hiver") == 0) {
        printf("Pas de reproduction en Automne ou Hiver.\n");
        return;
    }

    static int joursDepuisReproduction = 0;
    joursDepuisReproduction++;

    if (joursDepuisReproduction < 30) {
        printf("La reine ne se reproduira qu'après %d jours.\n", 30 - joursDepuisReproduction);
        return;
    }

    joursDepuisReproduction = 0; // Réinitialisation du compteur

    // Vérification qu'un mâle actif est disponible
    int maleActifTrouve = 0;
    for (int i = 0; i < *tailleColonie; i++) {
        if (colonie[i].type == MALE && colonie[i].statut == 3) {
            maleActifTrouve = 1;
            break;
        }
    }

    if (maleActifTrouve) {
        printf("La reine trouve un mâle actif et commence la reproduction.\n");
        nonAdultes->nboeufs += 10; // Ajout de 10 œufs
        printf("10 œufs ont été pondus. Total d'œufs : %d\n", nonAdultes->nboeufs);
    } else {
        printf("Aucun mâle actif disponible dans la colonie. Pas de reproduction possible.\n");
    }
}
