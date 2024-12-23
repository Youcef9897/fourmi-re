#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fourmis.h"
#include "nourriture.h"
#include "climat.h"
#include "reproduction.h"

int main() {
    // Initialisation des structures principales
    Climat climat = {1, 1, "Été", "Période d'activité"};
    StockNourriture stockNourriture = {50.0, 50.0, 50.0, 50.0};
    StockMateriaux stockMateriaux = {30, 30, 30, 30};
    int tailleColonie = 0;
    Fourmi colonie[100]; // Augmenté pour gérer les transitions et nouveaux nés
    GestionNonAdultes gestionNonAdultes = {0, 0, 0}; // Initialisation pour la gestion des non-adultes

    // Génération initiale de la colonie
    genererColonie(colonie, &tailleColonie);

    // Initialisations supplémentaires
    srand(time(NULL));
    definirClimat(&climat);
    initialiserZones();

    int joursDepuisDerniereReproduction = 0; // Suivi de la reproduction

    printf("Début de la simulation...\n");

    while (1) {
        afficherClimat(&climat);

        if (strcmp(climat.periode, "Hibernation") == 0) {
            printf("La colonie est en hibernation. Aucune activité aujourd'hui.\n");
        } else {
            printf("Activité normale dans la colonie aujourd'hui.\n");

            // Affichage de l'état général de la colonie
            printf("\n--- État général de la colonie ---\n");
            printf("Nombre total de fourmis : %d\n", tailleColonie);

            // Affichage détaillé de chaque fourmi
            for (int i = 0; i < tailleColonie; i++) {
                const char *role = roleToString(colonie[i].type);
                printf("Rôle: %s, Âge: %d jours, Statut: %d, PV: %d\n", 
                       role, colonie[i].age, colonie[i].statut, colonie[i].pv);
            }

            // Gestion quotidienne
            gererLesMortsEtVieillirFourmis(colonie, &tailleColonie, &climat, &gestionNonAdultes);

            // Consommation des ressources
            consommationRessources(colonie, &tailleColonie, &stockNourriture,
                                   gestionNonAdultes.nboeufs, gestionNonAdultes.nblarves, gestionNonAdultes.nbnymphes);

            // Collecte des ressources
            collecteRessources(colonie, &tailleColonie, &stockNourriture, &stockMateriaux, climat.saison);

            // Gestion de la reproduction tous les 30 jours
            joursDepuisDerniereReproduction++;
            if (joursDepuisDerniereReproduction >= 30) {
                joursDepuisDerniereReproduction = 0;
                reproductionReine(colonie, &tailleColonie, &gestionNonAdultes, &climat);
            }
        }

        // Pause utilisateur
        printf("Voulez-vous continuer au jour suivant ? (o/n) : ");
        char reponse;
        scanf(" %c", &reponse);

        // Validation de l'entrée utilisateur
        if (reponse == 'n' || reponse == 'N') {
            break;
        }

        // Passage au jour suivant
        avancerJour(&climat);
        if (climat.jourActuel == 1) {
            climat.cycle++;
        }
    }

    printf("Fin de la simulation.\n"); 
    printf("MERCI D'AVOIR JOUÉ !\n");
    return 0;
}
