#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "structures.h"
#include "FourmisColonie.h"  // Inclus le fichier fourmis.h
#include "Ressources.h" 
#include "climat.h"
#include "combat.h"  
#include "reproduction.h"

int main() {
    for (int j = 0; j < 10; j++) {  // Boucle pour faire clignoter 10 fois
        // Efface l'écran
        printf("\033[2J");
        // Positionne le curseur au début
        printf("\033[H");

        // Affiche le cadre
        printf("\033[38;5;196m███████╗ ██████╗ ██╗   ██╗██████╗ ███╗   ███╗██╗██╗      █████╗ ███╗   ██╗██████╗ \033[0m\n");
        printf("\033[38;5;214m██╔════╝██╔═══██╗██║   ██║██╔══██╗████╗ ████║██║██║     ██╔══██╗████╗  ██║██╔══██╗\033[0m\n");
        printf("\033[38;5;226m█████╗  ██║   ██║██║   ██║██████╔╝██╔████╔██║██║██║     ███████║██╔██╗ ██║██║  ██║\033[0m\n");
        printf("\033[38;5;22m██╔══╝  ██║   ██║██║   ██║██  ██║ ██║╚██╔╝██║██║██║     ██╔══██║██║╚██╗██║██║  ██║\033[0m\n");
        printf("\033[38;5;21m██║     ╚██████╔╝╚██████╔╝██║ ███╗██║ ╚═╝ ██║██║███████╗██║  ██║██║ ╚████║██████╔╝\033[0m\n");
        printf("\033[38;5;129m╚═╝      ╚═════╝  ╚═════╝ ╚═╝ ╚══╝╚═╝     ╚═╝╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝ \033[0m\n\n");

        // Attend 500 millisecondes
        usleep(500000);

        // Efface l'écran
        printf("\033[2J");
        printf("\033[H");

        // Attend 500 millisecondes avant d'afficher à nouveau
        usleep(500000);
    }
    int c = getchar();

    // Vérifier si c est Entrée (code ASCII 10 pour '\n')
    if (c == '\n') {
        // Initialisation des structures principales
        Colonie etatColonie = {1000, 0}; // Par exemple, 1000 PV au départ, 0 fourmis.
        Climat climat = {1, 1, "Été", "Période d'activité"}; // Jour 1, cycle 1, saison initiale : Été.
        StockNourriture stockNourriture = {50.0, 50.0, 50.0, 50.0}; // Stocks de nourriture initiaux
        StockMateriaux stockMateriaux = {30, 30, 30, 30}; // Stocks de matériaux initiaux
        Fourmi colonie[100]; // Limite à 100 fourmis pour cet exemple
        int tailleColonie = 0; // Taille initiale de la colonie
        GestionReproduction gestionreproduction = {0, 0, 0, 0.0}; // Gestion des non-adultes
        int nbOeufs = 0;  // Nombre initial d'œufs
    
        // Génération initiale de la colonie
        genererColonie(colonie, &tailleColonie, &etatColonie);
    
        // Initialisation supplémentaire
        srand(time(NULL)); // Initialisation du générateur aléatoire
        initialiserZones(); // Initialisation des zones
    
        printf("🐜 Début de la simulation de la colonie de fourmis...\n");
    
        while (1) {
            // Activité 1 : Vérifier si la période est l'hibernation
            if (strcmp(climat.periode, "Hibernation") == 0) {
                afficherClimat(&climat);
                printf("\n❄️ Nous sommes en hibernation. Aucune activité à faire pendant cette période.\n");
            } else {
                // Activité 2 : Afficher l'état général de la colonie
                afficherEtatColonie(&etatColonie);
                afficherClimat(&climat);
                printf("\n--- 🏠 État général de la colonie ---\n");
                for (int i = 0; i < tailleColonie; i++) {
                    afficherFourmi(colonie[i]);  // Afficher chaque fourmi
                }
    
                // Activité 3 : Gérer les morts et vieillir les fourmis
                gererLesMortsEtVieillirFourmis(colonie, &tailleColonie, &climat, &etatColonie);
                
                // Activité 4 : Collecte des ressources - Nourriture
                printf("\n--- 🌾 Activité 4 : Collecte des ressources (Nourriture) ---\n");
                collecteNourriture(colonie, tailleColonie, &stockNourriture, climat.saison);
                
                // Activité 5 : Collecte des ressources - Matériaux
                printf("\n--- 🪵 Activité 5 : Collecte des ressources (Matériaux) ---\n");
                collecteMateriaux(colonie, tailleColonie, &stockMateriaux, &etatColonie);
    
                // Affichage des stocks de matériaux après la collecte
                printf("\n--- 📦 Stocks Restants de Matériaux ---\n");
                printf("Bois : %d, Pierres : %d, Feuilles : %d, Argiles : %d\n", stockMateriaux.bois, stockMateriaux.pierres, stockMateriaux.feuilles, stockMateriaux.argiles);
    
                // Activité 6 : Gérer les combats
                printf("\n--- ⚔️ Activité 6 : Gestion des combats ---\n");
                lancerCombat(colonie, tailleColonie, &etatColonie, &stockNourriture); // Appel à la fonction de combat
    
                // Activité 7 : Consommation des ressources
                printf("\n--- 🍽️ Activité 7 : Consommation des ressources ---\n");
                consommationNourriture(colonie, tailleColonie, &stockNourriture);
    
                // Activité 8 : Gérer la reproduction
                printf("\n--- 🐣 Activité 8 : Gestion de la reproduction ---\n");
                reproduction(colonie, &tailleColonie, &gestionreproduction, nbOeufs);
    
                // Afficher l'état des non-adultes après la reproduction
                afficherNonAdultes(&gestionreproduction);
    
                // Activité 9 : Consommation des ressources pour les non-adultes
                printf("\n--- 🍼 Activité 9 : Consommation des ressources pour les non-adultes ---\n");
                consommationRessourcesNonAdultes(&gestionreproduction, &stockNourriture);
            }
    
            // Pause utilisateur
            printf("\nVoulez-vous continuer au jour suivant ? (o/n) : ");
            char reponse;
            scanf(" %c", &reponse);
    
            if (reponse == 'n' || reponse == 'N') {
                break;  // Le 'break' doit être dans la boucle while
            }
            printf("     ██╗ ██████╗  ██╗   ██╗██████╗          ███████╗██╗   ██╗██╗██╗   ██╗ █████╗ ███╗   ██╗████████╗\n");
            printf("     ██║██╔═══██╗ ██║   ██║██╔══██╗         ██╔════╝██║   ██║██║██║   ██║██╔══██╗████╗  ██║╚══██╔══╝\n");
            printf("     ██║██║   ██║ ██║   ██║██████╔╝         ███████╗██║   ██║██║██║   ██║███████║██╔██╗ ██║   ██║\n");
            printf("██   ██║██║   ██║ ██║   ██║██  ██║          ╚════██║██║   ██║██║╚██╗ ██╔╝██╔══██║██║╚██╗██║   ██║\n");
            printf("╚█████╔╝╚██████╔╝ ╚██████╔╝██║ ███╗         ███████║╚██████╔╝██║ ╚████╔╝ ██║  ██║██║ ╚████║   ██║   \n");
            printf(" ╚════╝  ╚═════╝   ╚═════╝ ╚═╝ ╚══╝         ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   \n");
            // Activité 10 : Passage au jour suivant
            printf("\n--- 📅 Activité 10 : Passage au jour suivant ---\n");
            avancerJour(&climat);
        }
    
        printf("Fin de la simulation.\n");
        printf("MERCI D'AVOIR JOUÉ ! 🙏\n");
        return 0;
    }
}
