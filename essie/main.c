#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "structures.h"
#include "fourmis.h" // Inclus le fichier fourmis.h
#include "nourriture.h"
#include "climat.h"
#include "combat.h"
#include "reproduction.h"

int main()
{
    for (int i = 0; i < 3; i++)
    { // Boucle pour faire clignoter 10 fois
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
    // Affiche le cadre
    printf("\033[38;5;196m███████╗ ██████╗ ██╗   ██╗██████╗ ███╗   ███╗██╗██╗      █████╗ ███╗   ██╗██████╗ \033[0m\n");
    printf("\033[38;5;214m██╔════╝██╔═══██╗██║   ██║██╔══██╗████╗ ████║██║██║     ██╔══██╗████╗  ██║██╔══██╗\033[0m\n");
    printf("\033[38;5;226m█████╗  ██║   ██║██║   ██║██████╔╝██╔████╔██║██║██║     ███████║██╔██╗ ██║██║  ██║\033[0m\n");
    printf("\033[38;5;22m██╔══╝  ██║   ██║██║   ██║██  ██║ ██║╚██╔╝██║██║██║     ██╔══██║██║╚██╗██║██║  ██║\033[0m\n");
    printf("\033[38;5;21m██║     ╚██████╔╝╚██████╔╝██║ ███╗██║ ╚═╝ ██║██║███████╗██║  ██║██║ ╚████║██████╔╝\033[0m\n");
    printf("\033[38;5;129m╚═╝      ╚═════╝  ╚═════╝ ╚═╝ ╚══╝╚═╝     ╚═╝╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝ \033[0m\n\n");


    printf("--- APPUYER SUR ENTREE POUR COMMENCER LA PARTIE ---\n");
    int c = getchar();
    // Vérifier si c est Entrée (code ASCII 10 pour '\n')
    if (c == '\n')
    {
        // Initialisation des structures principales
        Colonie etatColonie = {1000, 0};                            // Par exemple, 1000 PV au départ, 0 fourmis.
        Climat climat = {1, 1, "Été", "Période d'activité"};        // Jour 1, cycle 1, saison initiale : Été.
        StockNourriture stockNourriture = {50.0, 50.0, 50.0, 50.0}; // Stocks de nourriture initiaux
        StockMateriaux stockMateriaux = {30, 30, 30, 30};           // Stocks de matériaux initiaux
        Fourmi colonie[100];                                        // Limite à 100 fourmis pour cet exemple
        int tailleColonie = 0;                                      // Taille initiale de la colonie
        GestionReproduction gestionreproduction = {0, 0, 0, 0.0};   // Gestion des non-adultes
        int nbOeufs = 0;                                            // Nombre initial d'œufs

        // Génération initiale de la colonie
        genererColonie(colonie, &tailleColonie, &etatColonie);

        // Initialisation supplémentaire
        srand(time(NULL));  // Initialisation du générateur aléatoire
        initialiserZones(); // Initialisation des zones

        usleep(700000);
        printf("Début de la simulation de la colonie de fourmis...\n");

        while (1)
        {
            // Activité 1 : Vérifier si la période est l'hibernation
            if (strcmp(climat.periode, "Hibernation") == 0)
            {
                afficherClimat(&climat);
                
                usleep(700000);
                printf("\nNous sommes en hibernation. Aucune activité à faire pendant cette période.\n");
            }
            else
            {
                // Activité 2 : Afficher l'état général de la colonie
                afficherEtatColonie(&etatColonie);
                afficherClimat(&climat);
                char answer[4];
                
                usleep(700000);
                printf("\n Voulez vous voir l'état de la colonie ? (o/n)");
                char ref;
                scanf(" %c", &ref);
                if (ref == 'o')
                {
                    
                    usleep(700000);
                    printf("\n--- État général de la colonie ---\n");
                    for (int i = 0; i < tailleColonie; i++)
                    {
                        afficherFourmi(colonie[i]); // Afficher chaque fourmi
                    }
                }
                
                usleep(700000);
                printf("\n Voulez vous voir le déroulement de la journée ? (o/n)");
                char tap;
                scanf(" %c", &tap);
                if (tap == 'o')
                {
                    // Activité 3 : Gérer les morts et vieillir les fourmis
                    gererLesMortsEtVieillirFourmis(colonie, &tailleColonie, &climat, &etatColonie);

                    // Activité 4 : Collecte des ressources - Nourriture
                    usleep(700000);
                    printf("\n--- Activité 4 : Collecte des ressources (Nourriture) ---\n");
                    collecteNourriture(colonie, tailleColonie, &stockNourriture, climat.saison);

                    // Activité 5 : Collecte des ressources - Matériaux
                    usleep(700000);
                    printf("\n--- Activité 5 : Collecte des ressources (Matériaux) ---\n");
                    collecteMateriaux(colonie, tailleColonie, &stockMateriaux, &etatColonie);

                    // Affichage des stocks de matériaux après la collecte
                    usleep(700000);
                    printf("\n--- Stocks Restants de Matériaux ---\n");
                    usleep(700000);
                    printf("Bois : %d, Pierres : %d, Feuilles : %d, Argiles : %d\n", stockMateriaux.bois, stockMateriaux.pierres, stockMateriaux.feuilles, stockMateriaux.argiles);

                    // Activité 6 : Gérer les combats
                    usleep(700000);
                    printf("\n--- Activité 6 : Gestion des combats ---\n");
                    lancerCombat(colonie, tailleColonie, &etatColonie, &stockNourriture); // Appel à la fonction de combat

                    // Activité 7 : Consommation des ressources
                    usleep(700000);
                    printf("\n--- Activité 7 : Consommation des ressources ---\n");
                    consommationNourriture(colonie, tailleColonie, &stockNourriture);

                    // Activité 8 : Gérer la reproduction
                    usleep(700000);
                    printf("\n--- Activité 8 : Gestion de la reproduction ---\n");
                    reproduction(colonie, &tailleColonie, &gestionreproduction, nbOeufs);

                    // Afficher l'état des non-adultes après la reproduction
                    afficherNonAdultes(&gestionreproduction);

                    // Activité 9 : Consommation des ressources pour les non-adultes
                    usleep(700000);
                    printf("\n--- Activité 9 : Consommation des ressources pour les non-adultes ---\n");
                    consommationRessourcesNonAdultes(&gestionreproduction, &stockNourriture);
                }
            }
            // Pause utilisateur
            
            usleep(700000);
            printf("\nVoulez-vous continuer au jour suivant ? (o/n) : ");
            char reponse;
            scanf(" %c", &reponse);

            if (reponse == 'n' || reponse == 'N')
            {
                break; // Le 'break' doit être dans la boucle while
            }
            usleep(700000);
            printf("     ██╗ ██████╗  ██╗   ██╗██████╗          ███████╗██╗   ██╗██╗██╗   ██╗ █████╗ ███╗   ██╗████████╗\n");
            printf("     ██║██╔═══██╗ ██║   ██║██╔══██╗         ██╔════╝██║   ██║██║██║   ██║██╔══██╗████╗  ██║╚══██╔══╝\n");
            printf("     ██║██║   ██║ ██║   ██║██████╔╝         ███████╗██║   ██║██║██║   ██║███████║██╔██╗ ██║   ██║\n");
            printf("██   ██║██║   ██║ ██║   ██║██  ██║          ╚════██║██║   ██║██║╚██╗ ██╔╝██╔══██║██║╚██╗██║   ██║\n");
            printf("╚█████╔╝╚██████╔╝ ╚██████╔╝██║ ███╗         ███████║╚██████╔╝██║ ╚████╔╝ ██║  ██║██║ ╚████║   ██║   \n");
            printf(" ╚════╝  ╚═════╝   ╚═════╝ ╚═╝ ╚══╝         ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   \n");
            // Activité 10 : Passage au jour suivant
            usleep(700000);
            printf("\n--- Activité 10 : Passage au jour suivant ---\n");
            avancerJour(&climat);
        }
        
        usleep(700000);
        printf("Fin de la simulation.\n");
        
        usleep(700000);
        printf("MERCI D'AVOIR JOUÉ !\n");
        return 0;
    }
}
