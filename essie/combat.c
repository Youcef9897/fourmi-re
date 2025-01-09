#include <stdio.h> // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard pour les fonctions utilitaires
#include "combat.h" // Inclusion du fichier d'en-tête combat.h
#include <unistd.h> // Pour la fonction usleep
#include "FourmisColonie.h" // Inclusion du fichier d'en-tête FourmisColonie.h

// Fonction générique pour initialiser un ennemi (fourmi ennemie ou prédateur)
void initialiserEnnemi(void *ennemi, int isPredateur) {
    // Vérification visuelle (toujours réalisée)
    modifierEtAfficherAlerte(ALERTE_VERIF_VISUELLE, "🔍 Vérification visuelle des fourmis entrantes dans la colonie.");
    
    if (isPredateur) {
        printf("\033[1;31m"); // Changement de couleur en rouge
        printf("😱 Ahhh, un prédateur est détecté ! Les fourmis fuient pour échapper à l'attaque.\n");
        printf("\n\n");
        printf("\033[0m"); // Rétablissement de la couleur par défaut
        printf("\033[1;31m"); // Changement de couleur en rouge
        printf("███████╗██╗   ██╗ ██║     ██║ ███████╗  ████████╗ ██║ ██║ ██║\n");
        printf("██╔════╝██║   ██║  ██║   ██║  ██╔════╝      ║██║  ██║ ██║ ██║\n");
        printf("█████╗  ██║   ██║   ██║ ██║   █████╗      ║██║    ██║ ██║ ██║\n");
        printf("██╔══╝  ██║   ██║     ██║     ██╔══╝    ║██║      ╚═╝ ╚═╝ ╚═╝\n");
        printf("██║     ╚██████╔╝     ██║     ███████╗  ║███████╗ ██║ ██║ ██║\n");
        printf("╚═╝      ╚═════╝      ╚═╝     ╚══════╝  ╚═══════╝ ╚═╝ ╚═╝ ╚═╝\n");
        printf("\033[0m"); // Rétablissement de la couleur par défaut
        modifierEtAfficherAlerte(ALERTE_VERIF_VISUELLE, "😱 Ahhh un prédateur détecté, les soldats fuient de partout.");
    } else {
        // Si c'est une fourmi ennemie, initialisation des attributs
        printf("🔍 Le soldat ne reconnaît pas la fourmi et procède à une procédure olfactive pour la reconnaissance.\n");
        modifierEtAfficherAlerte(ALERTE_ODEUR, "👃 Odeur détectée par le soldat, ennemi détecté.");
        Fourmi *ennemie = (Fourmi *)ennemi; // Conversion du pointeur générique en pointeur de type Fourmi
        ennemie->type = SOLDAT; // Définition du type de la fourmi ennemie
        ennemie->age = 30; // Définition de l'âge de la fourmi ennemie
        ennemie->statut = 3; // Définition du statut de la fourmi ennemie
        ennemie->pv = 110; // Définition des points de vie de la fourmi ennemie
        printf("⚔️ Une fourmi ennemie a été initialisée : PV = %d\n", ennemie->pv); // Affichage des points de vie de la fourmi ennemie
        // En cas de doute, vérification olfactive
        printf("\n\n");
        printf("\033[1;31m");
        printf("███████╗ ██╗ ███████╗    ██╗  ██╗████████╗██║\n");
        printf("██╔════╝ ██║ ██╔══       ██║  ██║╚══██╔══╝██║\n");
        printf("█████╗   ██║ ██║    ███║ ███████║   ██║   ██║\n");
        printf("██╔══╝   ██║ ██║   ██║   ██╔══██║   ██║   ╚═╝\n");
        printf("██║      ██║ ╚██████╔    ██║  ██║   ██║   ██║\n");
        printf("╚═╝      ╚═╝  ╚═════╝    ╚═╝  ╚═╝   ╚═╝   ╚═╝\n");
        printf("\033[0m");
    }
}

// Fonction de combat
void combat(void *ennemi, Fourmi *soldat, Colonie *etatColonie, StockNourriture *stockNourriture, int isPredateur) {

    printf("\n--- 🛡️ Début du combat ---\n"); // Début du combat
    if (isPredateur) {
        // Si c'est un prédateur, la colonie est détruite immédiatement
        printf("😱 Un prédateur attaque la colonie et la détruit immédiatement. Fin de la simulation.\n");
        exit(0); // Fin de la simulation
    } else {
        // Si c'est une fourmi ennemie, le combat commence
        Fourmi *fourmiEnnemie = (Fourmi *)ennemi; // Conversion du pointeur générique en pointeur de type Fourmi
        printf("⚔️ Une fourmi ennemie attaque la colonie !\n");
        printf("Ennemie : PV = %d\n", fourmiEnnemie->pv); // Affichage des points de vie de la fourmi ennemie
        printf("Soldat : PV = %d\n", soldat->pv); // Affichage des points de vie du soldat

        affecterActivite(ZONE_DEFENSE_COLONIE, "🛡️ Le soldat défend la colonie contre une fourmi ennemie."); // Affectation de l'activité de défense
        modifierEtAfficherAlerte(ALERTE_GUIDAGE_TACTILE, "🛡️ Les soldats dirigent les butineuses et les architectes vers la zone de stockage."); // Modification et affichage de l'alerte

        while (fourmiEnnemie->pv > 0 && soldat->pv > 0) {
            // Tant que les deux combattants ont des points de vie
            int degatsSoldat = 1 + rand() % 5; // Calcul des dégâts infligés par le soldat
            int degatsEnnemi = 1 + rand() % 5; // Calcul des dégâts infligés par l'ennemi

            // Attaque du soldat
            fourmiEnnemie->pv -= degatsSoldat; // Réduction des points de vie de l'ennemi
            printf("⚔️ Le soldat inflige %d dégâts. PV de l'ennemi : %d\n", degatsSoldat, fourmiEnnemie->pv); // Affichage des dégâts infligés par le soldat

            if (fourmiEnnemie->pv <= 0) {
                // Si l'ennemi est mort
                printf("💀 L'ennemi est mort, le soldat le mange et se régénère.\n");
                affecterActivite(ZONE_CIMETIERE, "🧹 Nettoyeuses nettoient les restes et les débris dans la zone de défense."); // Affectation de l'activité de nettoyage
                soldat->pv += 20; // Régénération des points de vie du soldat
                return; // Fin du combat
            }

            // Attaque de l'ennemi
            soldat->pv -= degatsEnnemi; // Réduction des points de vie du soldat
            printf("⚔️ L'ennemi inflige %d dégâts. PV du soldat : %d\n", degatsEnnemi, soldat->pv); // Affichage des dégâts infligés par l'ennemi

            if (soldat->pv <= 0) {
                // Si le soldat est mort
                printf("💀 Le soldat est mort !\n");
                affecterActivite(ZONE_CIMETIERE, "💀 Le soldat est mort, les nettoyeuses l'emmènent dans la tombe et la tombe et nettoient la zone d'attaque."); // Affectation de l'activité de nettoyage
                etatColonie->PvColonie -= 100; // Réduction des points de vie de la colonie
                stockNourriture->sucre = (stockNourriture->sucre > 5) ? stockNourriture->sucre - 5 : 0; // Réduction du stock de sucre
                stockNourriture->graine = (stockNourriture->graine > 5) ? stockNourriture->graine - 5 : 0; // Réduction du stock de graines
                return; // Fin du combat
            }
        }
    }
}

// Fonction pour lancer un combat
void lancerCombat(Fourmi *colonie, int tailleColonie, Colonie *etatColonie, StockNourriture *stockNourriture) {
    int probabilite = rand() % 100; // Génération d'une probabilité aléatoire

    // 50 % : Pas d'attaque
    if (probabilite < 50) {
        printf("\033[1;32m"); // Changement de couleur en vert
        printf("\n--- 🐜 Aujourd'hui, la colonie n'est pas attaquée. Les fourmis continuent leurs activités. ---\n");
        printf("\033[0m"); // Rétablissement de la couleur par défaut;
        modifierEtAfficherAlerte(ALERTE_GUIDAGE_TACTILE, "🛡️ Les soldats dirigent les butineuses et les architectes vers la zone de stockage."); // Modification et affichage de l'alerte
        return; // Fin de la fonction
    }

    // Recherche d'un soldat dans la colonie
    Fourmi *soldat = NULL; // Initialisation du pointeur de soldat à NULL
    for (int i = 0; i < tailleColonie; i++) {
        if (colonie[i].type == SOLDAT && colonie[i].statut == 3) {
            // Si une fourmi soldat est trouvée
            soldat = &colonie[i]; // Affectation du pointeur de soldat
            break; // Sortie de la boucle
        }
    }

    if (soldat == NULL) {
        // Si aucun soldat n'est disponible
        printf("🚫 Aucun soldat disponible pour défendre la colonie !\n");
        return; // Fin de la fonction
    }

    // 5 % : Attaque du prédateur
    if (probabilite >= 95) {
        printf("\n--- 🐍 Combat : Un prédateur attaque la colonie ---\n");
        combat(NULL, NULL, etatColonie, stockNourriture, 1); // Lancement du combat avec un prédateur
        return; // Fin de la fonction
    }

    // 30 % : Soldat gagne
    if (probabilite >= 50 && probabilite < 80) {
        Fourmi fourmiEnnemie; // Déclaration d'une fourmi ennemie
        initialiserEnnemi(&fourmiEnnemie, 0); // Initialisation de la fourmi ennemie
        printf("\n--- ⚔️ Combat : Une fourmi ennemie attaque la colonie ---\n");
        combat(&fourmiEnnemie, soldat, etatColonie, stockNourriture, 0); // Lancement du combat avec une fourmi ennemie
        return; // Fin de la fonction
    }

    // 15 % : Ennemi gagne
    if (probabilite >= 80 && probabilite < 95) {
        Fourmi fourmiEnnemie; // Déclaration d'une fourmi ennemie
        initialiserEnnemi(&fourmiEnnemie, 0); // Initialisation de la fourmi ennemie
        printf("\n--- ⚔️ Combat : Une fourmi ennemie attaque la colonie ---\n");
        combat(&fourmiEnnemie, soldat, etatColonie, stockNourriture, 0); // Lancement du combat avec une fourmi ennemie
    }
}
