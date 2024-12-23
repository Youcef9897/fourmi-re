#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structures.h"
#include "fourmis.h"
#include "nourriture.h"
#include "climat.h"
#include "reproduction.h"

int main() {
    // Initialisation des structures principales
    Climat climat = {1, 1, "Été", "Période d'activité"}; // Jour 1, cycle 1, saison initiale
    StockNourriture stockNourriture = {50.0, 50.0, 50.0, 50.0}; // Stocks de nourriture initiaux
    StockMateriaux stockMateriaux = {30, 30, 30, 30}; // Stocks de matériaux initiaux
    Fourmi colonie[100]; // Limite à 100 fourmis pour cet exemple
    int tailleColonie = 0; // Taille initiale de la colonie
    GestionNonAdultes gestionNonAdultes = {0, 0, 0}; // Gestion des non-adultes

    // Génération initiale de la colonie
    genererColonie(colonie, &tailleColonie);

    // Initialisation supplémentaire
    srand(time(NULL)); // Générateur aléatoire
    definirClimat(&climat); // Définir le climat
    initialiserZones(); // Initialiser les zones

    int joursDepuisDerniereReproduction = 0; // Suivi du temps

    printf("Début de la simulation de la colonie de fourmis...\n");

    while (1) {
        // Afficher les informations climatiques
        afficherClimat(&climat);

        if (strcmp(climat.periode, "Hibernation") == 0) {
            printf("La colonie est en hibernation. Aucune activité aujourd'hui.\n");
        } else {
            printf("\n--- Activité normale de la colonie aujourd'hui ---\n");

            // Afficher l'état général de la colonie
            printf("\n--- État général de la colonie ---\n");
            printf("Nombre total de fourmis : %d\n", tailleColonie);

            for (int i = 0; i < tailleColonie; i++) {
                const char *role = roleToString(colonie[i].type);
                printf("Rôle: %s, Âge: %d jours, Statut: %d, PV: %d\n", 
                       role, colonie[i].age, colonie[i].statut, colonie[i].pv);
            }

            // Gérer les morts et vieillir les fourmis
            gererLesMortsEtVieillirFourmis(colonie, &tailleColonie, &climat, &gestionNonAdultes);

            // Consommation des ressources
            consommationRessources(colonie, tailleColonie, &stockNourriture, &gestionNonAdultes);

            // Collecte des ressources
            collecteRessources(colonie, &tailleColonie, &stockNourriture, &stockMateriaux, climat.saison);

            // Reproduction tous les 30 jours
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

        if (reponse == 'n' || reponse == 'N') {
            break;
        }

        // Passage au jour suivant
        avancerJour(&climat);

        // Mise à jour du cycle
        if (climat.jourActuel == 1) {
            climat.cycle++;
        }
    }

    printf("Fin de la simulation.\n");
    printf("MERCI D'AVOIR JOUÉ !\n");
    return 0;
}
