#include <stdio.h>
#include <stdlib.h>
#include "reproduction.h"

// Fonction pour gérer la reproduction dans la fourmilière
void reproduction(Fourmi *colonie, int *tailleColonie, GestionNonAdultes *gestionNonAdultes, StockNourriture *stockNourriture, int nbOeufs) {
    int nbMales = 0;
    for (int i = 0; i < *tailleColonie; i++) {
        if (colonie[i].type == MALE && colonie[i].statut == 3) {
            nbMales++;
        }
    }

    // Vérifier s'il y a des mâles et si la reine est présente
    int nbReines = 0;
    for (int i = 0; i < *tailleColonie; i++) {
        if (colonie[i].type == REINE && colonie[i].statut == 3) {
            nbReines++;
        }
    }

    // Faire évoluer les non-adultes (œufs, larves, nymphes)
    evoluerNonAdultes(colonie, tailleColonie, gestionNonAdultes);

    if (nbReines > 0 && nbMales > 0) {
        // La reine se reproduit
        printf("La reproduction a eu lieu !\n");
        nbOeufs = rand() % 10 + 5;  // La reine dépose entre 5 et 15 œufs
        deposerOeufs(colonie, tailleColonie, nbOeufs);
    } else {
        printf("Pas de reproduction : Il faut une reine et des mâles actifs.\n");
    }
    gestionNonAdultes->nboeufs += nbOeufs;
    printf("nombre d'oeufs : %d\n", gestionNonAdultes->nboeufs);

    

    // Consommer des ressources pour les non-adultes
    consommerRessourcesNonAdultes(gestionNonAdultes, stockNourriture);
}

// Fonction pour déposer des œufs dans la colonie
void deposerOeufs(Fourmi *colonie, int *tailleColonie, int nbOeufs) {
    GestionNonAdultes *gestion = malloc(sizeof(GestionNonAdultes));
    gestion->nboeufs += nbOeufs;
    printf("La reine a déposé %d œufs.\n", nbOeufs);
}

// Fonction pour faire évoluer les non-adultes (œufs -> larves -> nymphes -> adultes)
void evoluerNonAdultes(Fourmi *colonie, int *tailleColonie, GestionNonAdultes *gestionNonAdultes) {
    // Les œufs deviennent des larves, puis des nymphes et enfin des adultes
    if (gestionNonAdultes->nboeufs > 0) {
        gestionNonAdultes->nblarves= gestionNonAdultes->nboeufs ;
        gestionNonAdultes->nboeufs=0;
        printf("Un œuf est devenu une larve.\n");
    }

    else if (gestionNonAdultes->nblarves > 0) {
        gestionNonAdultes->nbnymphes=gestionNonAdultes->nblarves;
        gestionNonAdultes->nblarves=0;
        printf("Une larve est devenue une nymphe.\n");
    }

    if (gestionNonAdultes->nbnymphes > 0) {
        gestionNonAdultes->nbnymphes--;
        printf("Une nymphe est devenue une fourmi adulte.\n");
    }
}

// Fonction pour afficher les états des non-adultes (œufs, larves, nymphes)
void afficherNonAdultes(GestionNonAdultes *gestionNonAdultes) {
    printf("État des non-adultes:\n");
    printf(" - Œufs: %d\n", gestionNonAdultes->nboeufs);
    printf(" - Larves: %d\n", gestionNonAdultes->nblarves);
    printf(" - Nymphes: %d\n", gestionNonAdultes->nbnymphes);
}

// Fonction pour consommer des ressources pour les non-adultes (œufs, larves, nymphes)
void consommerRessourcesNonAdultes(GestionNonAdultes *gestionNonAdultes, StockNourriture *stockNourriture) {
    // Consommation des non-adultes
    float totalConsommation = (gestionNonAdultes->nboeufs + gestionNonAdultes->nblarves + gestionNonAdultes->nbnymphes) * 0.1;

    if (totalConsommation <= stockNourriture->sucre) {
        stockNourriture->sucre -= totalConsommation;
        printf("Les non-adultes ont consommé %.2f unités de sucre.\n", totalConsommation);
    } else {
        printf("Pas assez de sucre pour nourrir les non-adultes.\n");
    }
}
