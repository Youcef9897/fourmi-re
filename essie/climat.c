#include <stdio.h>  // Inclusion de la bibliothèque standard d'entrée/sortie.
#include <string.h>  // Inclusion de la bibliothèque pour les opérations sur les chaînes de caractères.
#include "climat.h"  // Inclusion du fichier d'en-tête "climat.h".
#include <unistd.h>

// Tableau des saisons. Chaque entrée correspond à une saison de l'année.
const char *saisons[] = {"Été", "Automne", "Hiver", "Printemps"};

// Périodes associées aux saisons. Chaque saison a une période d'activité ou d'hibernation.
const char *periodes[] = {"Période d'activité", "Hibernation", "Hibernation", "Période d'activité"};

// Fonction pour avancer d'un jour dans le climat.
void avancerJour(Climat *climat) {
    climat->jourActuel++;  // Incrémentation du jour actuel de 1.

    // Si le jour actuel dépasse 30, cela signifie que nous avons complété une saison.
    if (climat->jourActuel > 30) {
        climat->jourActuel = 1;    // Réinitialisation du jour actuel à 1 (début de la nouvelle saison).

        // Transition des saisons en utilisant un index.
        int saisonIndex = -1;  // Initialisation de l'index de saison à -1 (valeur par défaut).
        for (int i = 0; i < 4; i++) {  // Boucle pour parcourir les saisons (4 saisons au total).
            if (strcmp(climat->saison, saisons[i]) == 0) {  // Comparaison de la saison actuelle avec les saisons du tableau.
                saisonIndex = (i + 1) % 4;  // Si la saison correspond à un élément du tableau, on passe à la saison suivante.
                break;  // On sort de la boucle après avoir trouvé la saison actuelle.
            }
        }

        // Si une saison valide a été trouvée, on met à jour la saison et la période dans le climat.
        if (saisonIndex != -1) {
            strcpy(climat->saison, saisons[saisonIndex]);  // Mise à jour de la saison actuelle.
            strcpy(climat->periode, periodes[saisonIndex]);  // Mise à jour de la période correspondante à la nouvelle saison.
        }

        // Si une année complète (quatre saisons) a été parcourue, on incrémente le cycle.
        if (saisonIndex == 0) {  // Si la saison est de nouveau "Été", cela signifie qu'une année est passée.
            climat->cycle++;  // Incrémentation du cycle (nouvelle année).
            usleep(700000);
            printf("\n🌞 Un nouveau cycle commence après l'été ! Cycle actuel : %d 🌞\n", climat->cycle);  // Affichage du nouveau cycle.
        }
    }
}

// Fonction pour afficher le climat actuel.
void afficherClimat(const Climat *climat) {
    usleep(700000);
    printf("\n--- 🌍 Climat Actuel 🌍 ---\n");
    usleep(700000);
    printf("🌸 Saison : %s\n", climat->saison);  // Affichage de la saison actuelle.
    usleep(700000);
    printf("🕒 Période : %s\n", climat->periode);  // Affichage de la période associée à la saison.
    usleep(700000);
    printf("🔄 Cycle : %d\n", climat->cycle);  // Affichage du cycle actuel (par exemple, l'année en cours).
    usleep(700000);
    printf("📅 Jour Actuel : %d\n", climat->jourActuel);  // Affichage du jour actuel dans la saison.
    usleep(700000);
    printf("-----------------------\n");
}
