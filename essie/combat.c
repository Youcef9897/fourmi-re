#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structures.h"
#include "fourmis.h"
#include "nourriture.h"
#include "climat.h"
#include "combat.h"  // Ajout de l'en-tête pour le combat

// Fonction pour calculer la probabilité d'un coup mortel
float calculerProbabiliteCoupMortel(int pvEnnemie, int pvDefenseur) {
    return (float)pvEnnemie / (pvEnnemie + pvDefenseur);
}

// Fonction pour simuler un combat entre deux fourmis
void combatFourmis(Fourmi *Ennemie, Fourmi *soldat) {
    printf("\n--- Début du combat ---\n");
    printf("Ennemie : Rôle = %d, PV = %d\n", Ennemie->type, Ennemie->pv);
    printf("Soldat : Rôle = %d, PV = %d\n", soldat->type, soldat->pv);

    // Le soldat se prépare au combat
    affecterActivite(ZONE_DEFENSE_COLONIE, "Le SOLDAT se prépare pour combattre l'ennemi.");

    while (Ennemie->pv > 0 && soldat->pv > 0) {
        float probaEnnemie = calculerProbabiliteCoupMortel(Ennemie->pv, soldat->pv);
        float probaSoldat = calculerProbabiliteCoupMortel(soldat->pv, Ennemie->pv);

        // Tour de l'ennemi
        if ((rand() % 100) / 100.0 < probaEnnemie) {
            printf("Coup mortel infligé par l'Ennemie !\n");
            soldat->pv = 0;  // Le soldat meurt
        } else {
            int degats = 1 + rand() % 5;
            soldat->pv -= degats;
            printf("L'Ennemie inflige %d dégâts. PV du soldat : %d\n", degats, soldat->pv);
        }

        if (soldat->pv <= 0) break;

        // Tour du soldat
        if ((rand() % 100) / 100.0 < probaSoldat) {
            printf("Coup mortel infligé par le soldat !\n");
            Ennemie->pv = 0;  // L'ennemi meurt
        } else {
            int degats = 1 + rand() % 5;
            Ennemie->pv -= degats;
            printf("Le soldat inflige %d dégâts. PV de l'Ennemie : %d\n", degats, Ennemie->pv);
        }
    }

    // Gestion de la fin du combat
    printf("\n--- Fin du combat ---\n");
    if (Ennemie->pv > 0) {
        printf("Victoire de l'Ennemie !\n");
    } else if (soldat->pv > 0) {
        // Si le soldat gagne, il mange l'ennemi et régénère ses PV à 120
        printf("Victoire du soldat !\n");
        soldat->pv = 120;  // Le soldat régénère ses PV à 120 après avoir mangé l'ennemi
        printf("Le soldat mange l'ennemi et se régénère. PV du soldat : %d\n", soldat->pv);
    } else {
        printf("Les deux combattants sont morts !\n");
    }
}

// Fonction pour lancer un combat entre une fourmi ennemie et un soldat
void lancerCombat(Fourmi *colonie, int tailleColonie) {
    // Recherche d'un soldat dans la colonie
    Fourmi *soldat = NULL;
    for (int i = 0; i < tailleColonie; i++) {
        if (colonie[i].type == SOLDAT) {
            soldat = &colonie[i];
            break;
        }
    }

    if (soldat == NULL) {
        printf("Aucun soldat disponible pour défendre la colonie !\n");
        return;
    }

    Fourmi ennemi = {.type = SOLDAT, .age = 30, .statut = 3, .pv = 100};

    // Description de la vérification des entrées par un soldat
    printf("Un soldat patrouille la zone 1 et vérifie les entrées des fourmis.\n");

    // Gérer les alertes avant le combat
    // Appels aux alertes
    modifierEtAfficherAlerte(ALERTE_VERIF_VISUELLE, "Vérification visuelle des fourmis entrantes dans la colonie.");
    modifierEtAfficherAlerte(ALERTE_ODEUR, "Odeur détectée par le soldat ennemi détecté.");

    printf("\nUn ennemi attaque la colonie !\n");
    printf("Ennemie - Rôle : Soldat, PV : %d\n", ennemi.pv);
    printf("Soldat - Rôle : %d, PV : %d\n", soldat->type, soldat->pv);

    // Lancer le combat
    combatFourmis(&ennemi, soldat);

    printf("\nÉtat après le combat :\n");
    printf("Ennemie - PV : %d\n", ennemi.pv);
    printf("Soldat - Rôle : %d, PV : %d\n", soldat->type, soldat->pv);

    // Affectation d'activité après le combat
    if (soldat->pv <= 0) {
        printf("Le soldat est mort au combat !\n");
        affecterActivite(ZONE_CIMETIERE, "Le SOLDAT est mort, les butineuses l'emmènent dans la tombe.");
    } else {
        printf("L'ennemi est mort, le soldat le mange et se régénère.\n");
        affecterActivite(ZONE_CIMETIERE, "L'ennemi est mort, le soldat le mange et se régénère.");
    }
}
