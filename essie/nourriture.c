#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "nourriture.h"
#include "fourmis.h"

#define CONSOMMATION_PAR_FOURMI 1.0 // Chaque fourmi adulte consomme 1 unité par jour
#define CONSOMMATION_PAR_5_PETITS 1.0 // Nourrices consomment 1 unité pour 5 œufs, larves, ou nymphes

// Fonction de collecte des ressources
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

    // Zone de collecte - Les butineuses explorent le monde extérieur à la recherche de ressources
    affecterActivite(ZONE_MONDE_EXTERNE, "Les BOUTINEUSES explorent le monde extérieur à la recherche de ressources.");

    // Effectuer la collecte des ressources
    stockNourriture->sucre += boutineusesActives * 2;
    stockNourriture->graines += boutineusesActives * 2;
    stockNourriture->champignons += boutineusesActives * 1;
    stockNourriture->proteines += boutineusesActives * 1;

    stockMateriaux->bois += boutineusesActives;
    stockMateriaux->pierres += boutineusesActives;
    stockMateriaux->feuilles += boutineusesActives;
    stockMateriaux->argiles += boutineusesActives;

    // Zone de retour - Les butineuses reviennent avec les ressources collectées
    affecterActivite(ZONE_ENTREE_PRINCIPALE, "Les BOUTINEUSES reviennent avec les ressources.");

    printf("\n--- Collecte Terminée ---\n");
    printf("Sucre : %.1f, Champignons : %.1f, Protéines : %.1f, Graines : %.1f\n",
           stockNourriture->sucre, stockNourriture->champignons, stockNourriture->proteines, stockNourriture->graines);
}

// Fonction pour calculer la consommation de nourriture des fourmis
void calculerConsommation(Fourmi *colonie, int tailleColonie, GestionNonAdultes *nonAdultes, GestionConsommation *consommation) {
    // Initialisation à zéro
    consommation->reine = 0;
    consommation->males = 0;
    consommation->nourrices = 0;
    consommation->nettoyeuses = 0;
    consommation->architectes = 0;
    consommation->butineuses = 0;
    consommation->soldats = 0;
    consommation->nonAdultes = 0;

    // Zone de consommation - Les fourmis et la reine vont consommer les ressources collectées
    affecterActivite(ZONE_STOCKAGE_NOURRITURE, "Les fourmis et la reine vont consommer les ressources collectées.");

    // Calcul de la consommation pour chaque type de fourmi
    for (int i = 0; i < tailleColonie; i++) {
        if (colonie[i].statut != 4 && colonie[i].statut == 3) { // Ignore les fourmis mortes et non actives
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

    // Calcul de la consommation des non-adultes (œufs, larves, nymphe)
    consommation->nonAdultes += nonAdultes->nboeufs / 5 * CONSOMMATION_PAR_5_PETITS;
    consommation->nonAdultes += nonAdultes->nblarves / 5 * CONSOMMATION_PAR_5_PETITS;
    consommation->nonAdultes += nonAdultes->nbnymphes / 5 * CONSOMMATION_PAR_5_PETITS;
}

// Fonction pour appliquer la consommation des ressources
void consommationRessources(Fourmi *colonie, int tailleColonie, StockNourriture *stockNourriture, GestionNonAdultes *nonAdultes) {
    GestionConsommation consommation;
    calculerConsommation(colonie, tailleColonie, nonAdultes, &consommation);

    // Affichage de la consommation par type de fourmi
    printf("\n--- Consommation Totale de Nourriture ---\n");
    printf("Consommation des mâles : %.1f\n", consommation.males);
    printf("Consommation des reines : %.1f\n", consommation.reine);
    printf("Consommation des nourrices : %.1f\n", consommation.nourrices);
    printf("Consommation des nettoyeuses : %.1f\n", consommation.nettoyeuses);
    printf("Consommation des architectes : %.1f\n", consommation.architectes);
    printf("Consommation des butineuses : %.1f\n", consommation.butineuses);
    printf("Consommation des soldats : %.1f\n", consommation.soldats);
    printf("Consommation des non-adultes : %.1f\n", consommation.nonAdultes);

    // Calcul de la consommation totale
    float consommationTotale = consommation.reine + consommation.males + consommation.nourrices + consommation.nettoyeuses +
                               consommation.architectes + consommation.butineuses + consommation.soldats + consommation.nonAdultes;

    // Mise à jour des stocks de nourriture
    if (consommationTotale > 0) {   
        float consommationParRessource = consommationTotale / 4.0;

        stockNourriture->sucre -= consommationParRessource;
        stockNourriture->champignons -= consommationParRessource;
        stockNourriture->proteines -= consommationParRessource;
        stockNourriture->graines -= consommationParRessource;

        // Empêcher que les stocks deviennent négatifs
        if (stockNourriture->sucre < 0) stockNourriture->sucre = 0;
        if (stockNourriture->champignons < 0) stockNourriture->champignons = 0;
        if (stockNourriture->proteines < 0) stockNourriture->proteines = 0;
        if (stockNourriture->graines < 0) stockNourriture->graines = 0;


        // Vérification si l'un des stocks est vide et déclenchement de l'alerte sonore
        if (stockNourriture->sucre == 0 || stockNourriture->champignons == 0 || stockNourriture->proteines == 0 || stockNourriture->graines == 0) {
            modifierEtAfficherAlerte(ALERTE_SONORE,"Appel de l'alerte sonore si un stock est vide");
        }


        printf("\n--- Stocks Restants de Nourriture ---\n");
        printf("Sucre : %.1f, Champignons : %.1f, Protéines : %.1f, Graines : %.1f\n",
               stockNourriture->sucre, stockNourriture->champignons, stockNourriture->proteines, stockNourriture->graines);
    } else {
        printf("\nAucune consommation aujourd'hui.\n");
    }

    // Zone de fin de consommation - Les fourmis ont terminé leur consommation
    affecterActivite(ZONE_STOCKAGE_NOURRITURE, "Les fourmis ont terminé leur consommation.");
}






