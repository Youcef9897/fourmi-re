#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"
#include "fourmis.h"

#define CONSOMMATION_PAR_FOURMI 1.0 // Chaque fourmi adulte consomme 1 unité par jour
#define CONSOMMATION_PAR_5_PETITS 1.0 // Nourrices consomment 1 unité pour 5 œufs, larves, ou nymphes

void collecteRessources(Fourmi *colonie, int *taille, StockNourriture *stockNourriture, StockMateriaux *stockMateriaux, const char *saison) {
    if (strcmp(saison, "Été") != 0 && strcmp(saison, "Printemps") != 0) {
        printf("Aucune collecte en Automne ou Hiver.\n");
        return;
    }

    int boutineusesActives = 0;
    for (int i = 0; i < *taille; i++) {
        if (colonie[i].type == BOUTINEUSES && colonie[i].statut == 3) { // Butineuses adultes
            boutineusesActives++;
        }
    }

    if (boutineusesActives == 0) {
        printf("Pas de BOUTINEUSES actives disponibles pour la collecte.\n");
        return;
    }

    affecterActivite(ZONE_MONDE_EXTERNE, "Les BOUTINEUSES explorent le monde extérieur à la recherche de ressources.");

    stockNourriture->sucre += boutineusesActives * 2; // Exemple
    stockNourriture->graines += boutineusesActives * 2;
    stockNourriture->champignons += boutineusesActives * 1;
    stockNourriture->proteines += boutineusesActives * 1;

    stockMateriaux->bois += boutineusesActives;
    stockMateriaux->pierres += boutineusesActives;
    stockMateriaux->feuilles += boutineusesActives;
    stockMateriaux->argiles += boutineusesActives;

    affecterActivite(ZONE_ENTREE_PRINCIPALE, "Les BOUTINEUSES reviennent avec les ressources.");

    printf("\nCollecte terminée :\n");
    printf("Sucre : %.1f, Champignons : %.1f, Protéines : %.1f, Graines : %.1f\n",
           stockNourriture->sucre, stockNourriture->champignons, stockNourriture->proteines, stockNourriture->graines);
}

void calculerConsommation(Fourmi *colonie, int tailleColonie, GestionNonAdultes *nonAdultes, GestionConsommation *consommation) {
    consommation->reine = consommation->males = consommation->nourrices = 0;
    consommation->nettoyeuses = consommation->architectes = consommation->butineuses = 0;
    consommation->soldats = consommation->nonAdultes = 0;

    for (int i = 0; i < tailleColonie; i++) {
        if (colonie[i].statut != 4 && colonie[i].statut == 3) {
            switch (colonie[i].type) {
                case REINE: consommation->reine += CONSOMMATION_PAR_FOURMI; break;
                case MALE: consommation->males += CONSOMMATION_PAR_FOURMI; break;
                case NOURRICE: consommation->nourrices += CONSOMMATION_PAR_FOURMI; break;
                case NETTOYEUSES: consommation->nettoyeuses += CONSOMMATION_PAR_FOURMI; break;
                case ARCHITECTES: consommation->architectes += CONSOMMATION_PAR_FOURMI; break;
                case BOUTINEUSES: consommation->butineuses += CONSOMMATION_PAR_FOURMI; break;
                case SOLDAT: consommation->soldats += CONSOMMATION_PAR_FOURMI; break;
            }
        }
    }

    consommation->nonAdultes += ceil(nonAdultes->nboeufs / 5.0) * CONSOMMATION_PAR_5_PETITS;
    consommation->nonAdultes += ceil(nonAdultes->nblarves / 5.0) * CONSOMMATION_PAR_5_PETITS;
    consommation->nonAdultes += ceil(nonAdultes->nbnymphes / 5.0) * CONSOMMATION_PAR_5_PETITS;
}

void consommationRessources(Fourmi *colonie, int tailleColonie, StockNourriture *stockNourriture, GestionNonAdultes *nonAdultes) {
    GestionConsommation consommation;
    calculerConsommation(colonie, tailleColonie, nonAdultes, &consommation);

    float consommationTotale = consommation.reine + consommation.males + consommation.nourrices +
                               consommation.nettoyeuses + consommation.architectes +
                               consommation.butineuses + consommation.soldats + consommation.nonAdultes;

    if (consommationTotale > 0) {
        float consommationParRessource = consommationTotale / 4.0;

        stockNourriture->sucre = (stockNourriture->sucre > consommationParRessource) ? stockNourriture->sucre - consommationParRessource : 0;
        stockNourriture->champignons = (stockNourriture->champignons > consommationParRessource) ? stockNourriture->champignons - consommationParRessource : 0;
        stockNourriture->proteines = (stockNourriture->proteines > consommationParRessource) ? stockNourriture->proteines - consommationParRessource : 0;
        stockNourriture->graines = (stockNourriture->graines > consommationParRessource) ? stockNourriture->graines - consommationParRessource : 0;

        printf("\n--- Stocks restants de nourriture ---\n");
        printf("Sucre : %.1f, Champignons : %.1f, Protéines : %.1f, Graines : %.1f\n",
               stockNourriture->sucre, stockNourriture->champignons, stockNourriture->proteines, stockNourriture->graines);
    } else {
        printf("\nAucune consommation aujourd'hui.\n");
    }
}
