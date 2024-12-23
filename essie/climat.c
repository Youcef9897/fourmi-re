#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Pour sleep()
#include "structures.h"

// Fonction pour déterminer la saison et l'activité en fonction du jour
void definirClimat(Climat *climat) {
    int jour = climat->jourActuel;
    
    if (jour >= 1 && jour <= 30) {
        strcpy(climat->saison, "Été");
        strcpy(climat->periode, "Période d'activité");
    } else if (jour >= 31 && jour <= 60) {
        strcpy(climat->saison, "Automne");
        strcpy(climat->periode, "Hibernation");
    } else if (jour >= 61 && jour <= 90) {
        strcpy(climat->saison, "Hiver");
        strcpy(climat->periode, "Hibernation");
    } else if (jour >= 91 && jour <= 120) {
        strcpy(climat->saison, "Printemps");
        strcpy(climat->periode, "Période d'activité");
    }
}

// Fonction pour avancer d'un jour et actualiser le climat
void avancerJour(Climat *climat) {
    climat->jourActuel++;
    if (climat->jourActuel > 120) { // Si on dépasse 120 jours, on revient au jour 1
        climat->jourActuel = 1;
    }
    definirClimat(climat); // Actualiser la saison et la période
}

// Afficher le climat actuel
void afficherClimat(Climat *climat) {
    printf("Cycle %d - Jour %d - Saison : %s - %s\n",
           climat->cycle, climat->jourActuel, climat->saison, climat->periode);
}

// Fonction pour gérer l'interaction utilisateur à la fin de chaque cycle
int continuerSimulation(Climat *climat) {
    char reponse;

    printf("Fin du Cycle %d. Voulez-vous continuer au cycle %d ? (o/n) : ",
           climat->cycle, climat->cycle + 1);
    scanf(" %c", &reponse);

    if (reponse == 'n' || reponse == 'N') {
        printf("Simulation terminée après %d cycles.\n", climat->cycle);
        return 0; // Arrêter la simulation
    } else if (reponse == 'o' || reponse == 'O') {
        climat->cycle++;
        return 1; // Continuer la simulation
    } else {
        printf("Entrée invalide. Simulation terminée.\n");
        return 0; // Entrée invalide, arrêter par défaut
    }
}

// Fonction pour dérouler les jours avec gestion des cycles
void deroulerJours(Climat *climat) {
    printf("Début de la simulation...\n");

    while (1) {
        afficherClimat(climat);

        // Avancer d'un jour
        avancerJour(climat);

        // Vérifier si on termine un cycle (jourActuel == 1 indique un nouveau cycle)
        if (climat->jourActuel == 1) {
            if (!continuerSimulation(climat)) {
                break; // Arrêter si l'utilisateur choisit de ne pas continuer
            }
        }

        sleep(1); // Pause d'une seconde entre chaque jour
    }
}
