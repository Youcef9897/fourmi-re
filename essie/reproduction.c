#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "fourmis.h"

#include <stdio.h>
#include <string.h>
#include "structures.h"
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

void consommationNonAdultes(int nbOeufs, int nbLarves, int nbNymphes, StockNourriture *stockNourriture) {
    float consommationTotale = 0.0;

    // Consommation basée sur le ratio (1 unité pour 5 non-adultes)
    float consommationOeufs = nbOeufs / 5.0;
    float consommationLarves = nbLarves / 5.0;
    float consommationNymphes = nbNymphes / 5.0;

    consommationTotale += consommationOeufs;
    consommationTotale += consommationLarves;
    consommationTotale += consommationNymphes;

    // Répartition équitable de la consommation sur les ressources
    float consommationParRessource = consommationTotale / 4.0;

    // Réduction des ressources en vérifiant la disponibilité
    stockNourriture->sucre = (stockNourriture->sucre >= consommationParRessource) ?
                             (stockNourriture->sucre - consommationParRessource) : 0;

    stockNourriture->champignons = (stockNourriture->champignons >= consommationParRessource) ?
                                   (stockNourriture->champignons - consommationParRessource) : 0;

    stockNourriture->proteines = (stockNourriture->proteines >= consommationParRessource) ?
                                 (stockNourriture->proteines - consommationParRessource) : 0;

    stockNourriture->graines = (stockNourriture->graines >= consommationParRessource) ?
                               (stockNourriture->graines - consommationParRessource) : 0;

    // Affichage des informations sur la consommation
    printf("\n--- Consommation des non-adultes ---\n");
    printf(" - %d œufs consomment %.2f unités\n", nbOeufs, consommationOeufs);
    printf(" - %d larves consomment %.2f unités\n", nbLarves, consommationLarves);
    printf(" - %d nymphes consomment %.2f unités\n", nbNymphes, consommationNymphes);
    printf("Consommation totale : %.2f unités réparties équitablement.\n", consommationTotale);
    printf("------------------------------------------\n");
}
