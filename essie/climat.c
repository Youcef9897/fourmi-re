#include <stdio.h>
#include <string.h>
#include "climat.h"

// Fonction pour définir le climat initial
void definirClimat(Climat *climat) {
    // Vous pouvez ajouter des logiques ici si nécessaire
    // Par exemple, définir la saison en fonction de certains critères
}

// Fonction pour afficher le climat actuel
void afficherClimat(const Climat *climat) {
    printf("\n--- Climat Actuel ---\n");
    printf("Saison : %s\n", climat->saison);
    printf("Période : %s\n", climat->periode);
    printf("Cycle : %d\n", climat->cycle);
    printf("Jour Actuel : %d\n", climat->jourActuel);
    printf("-----------------------\n");
}

// Fonction pour avancer d'un jour
void avancerJour(Climat *climat) {
    climat->jourActuel++;
    // Exemple de changement de saison
    if (climat->jourActuel > 90) { // Suppose une saison de 90 jours
        climat->jourActuel = 1;
        climat->cycle++;
        if (strcmp(climat->saison, "Été") == 0) {
            strcpy(climat->saison, "Automne");
            strcpy(climat->periode, "Période de transition");
        }
        else if (strcmp(climat->saison, "Automne") == 0) {
            strcpy(climat->saison, "Hiver");
            strcpy(climat->periode, "Hibernation");
        }
        else if (strcmp(climat->saison, "Hiver") == 0) {
            strcpy(climat->saison, "Printemps");
            strcpy(climat->periode, "Période de transition");
        }
        else if (strcmp(climat->saison, "Printemps") == 0) {
            strcpy(climat->saison, "Été");
            strcpy(climat->periode, "Période d'activité");
        }
    }
}
