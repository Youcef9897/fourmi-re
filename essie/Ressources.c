#include <stdio.h> // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard pour les fonctions utilitaires
#include <string.h> // Inclusion de la bibliothèque pour les fonctions de manipulation de chaînes
#include <stdbool.h> // Inclusion de la bibliothèque pour les types booléens
#include <time.h> // Inclusion de la bibliothèque pour les fonctions de manipulation du temps
#include "structures.h" // Inclusion du fichier d'en-tête pour les structures de données
#include "nourriture.h" // Inclusion du fichier d'en-tête pour les ressources
#include "fourmis.h" // Inclusion du fichier d'en-tête pour les fourmis et la colonie
#include <unistd.h>

#define CONSOMMATION_PAR_FOURMI 1.0 // Chaque fourmi adulte consomme 1 unité par jour

// Fonction de collecte des Nourriture
void collecteNourriture(Fourmi *colonie, int taille, StockNourriture *stockNourriture, const char *saison) {
    // Vérifie si la saison est Été ou Printemps pour permettre la collecte
    if (strcmp(saison, "Été") != 0 && strcmp(saison, "Printemps") != 0) {
        
        usleep(700000);
        printf("Aucune collecte en Automne ou Hiver.\n");
        return;
    }

    int boutineusesActives = 0; // Compteur de butineuses actives
    for (int i = 0; i < taille; i++) {
        // Compte les butineuses actives
        if (colonie[i].type == BUTINEUSE && colonie[i].statut == 3) {
            boutineusesActives++;
        }
    }

    // Vérifie s'il y a des butineuses actives disponibles
    if (boutineusesActives == 0) {
        
        usleep(700000);
        printf("Pas de BOUTINEUSES actives disponibles pour la collecte.\n");
        return;
    }

    // Zone de collecte - Les butineuses explorent le monde extérieur à la recherche de Nourriture
    
    affecterActivite(ZONE_MONDE_EXTERNE, "Les BOUTINEUSES explorent le monde extérieur à la recherche de Nourriture.");

    // Collecte de Nourriture
    stockNourriture->sucre += boutineusesActives * 2; // Ajoute du sucre au stock
    stockNourriture->graine += boutineusesActives * 2; // Ajoute des graines au stock
    stockNourriture->champignon += boutineusesActives * 1; // Ajoute des champignons au stock
    stockNourriture->feuille += boutineusesActives * 1; // Ajoute des protéines au stock

    // Zone de retour - Les butineuses reviennent avec la nourriture
    
    affecterActivite(ZONE_ENTREE_PRINCIPALE, "Les BOUTINEUSES reviennent avec les Nourriture.");
    
    usleep(700000);
    printf("\n--- Collecte Terminée ---\n");
    
    usleep(700000);
    printf("Sucres🍬: %.1f, Champignons🍄: %.1f, Feuilles🍃: %.1f, Graines🌱: %.1f\n",
           stockNourriture->sucre, stockNourriture->champignon, stockNourriture->feuille, stockNourriture->graine);
}

// Fonction de collecte des matériaux avec un choix aléatoire pour chaque architecte
void collecteMateriaux(Fourmi *colonie, int taille, StockMateriaux *stockMateriaux, Colonie *etatColonie) {
    int architectesActifs = 0; // Compteur d'architectes actifs
    for (int i = 0; i < taille; i++) {
        // Compte les architectes actifs
        if (colonie[i].type == ARCHITECTE && colonie[i].statut == 3) {
            architectesActifs++;
        }
    }

    // Vérifie s'il y a des architectes actifs disponibles
    if (architectesActifs == 0) {
        
        usleep(700000);
        printf("Pas d'ARCHITECTES actifs disponibles pour la collecte.\n");
        return;
    }

    // Zone de collecte - Les architectes collectent des matériaux
    
    affecterActivite(ZONE_MONDE_EXTERNE, "Les ARCHITECTES collectent activement des matériaux pour la colonie.");

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    for (int i = 0; i < architectesActifs; i++) {
        // Choix aléatoire du type de matériau collecté
        switch (rand() % 4) { // Nombre aléatoire entre 0 et 3 pour 4 matériaux
            case 0: stockMateriaux->bois++; break; // Ajoute du bois au stock
            case 1: stockMateriaux->pierres++; break; // Ajoute des pierres au stock
            case 2: stockMateriaux->feuilles++; break; // Ajoute des feuilles au stock
            case 3: stockMateriaux->argiles++; break; // Ajoute de l'argile au stock
        }
    }

    // Zone de retour - Les architectes reviennent avec les matériaux collectés
    
    affecterActivite(ZONE_ENTREE_PRINCIPALE, "Les ARCHITECTES reviennent à la colonie avec les matériaux collectés.");
    
    usleep(700000);
    printf("\n--- Collecte de Matériaux Terminée ---\n");
    
    usleep(700000);
    printf("🌳 Bois : %d, 🪨 Pierres : %d, 🍃 Feuilles : %d, 🧱 Argiles : %d\n",
       stockMateriaux->bois, stockMateriaux->pierres, stockMateriaux->feuilles, stockMateriaux->argiles);

    // Vérification et réparation de la colonie si nécessaire
    if (etatColonie->PvColonie < 1000) {
        
        usleep(700000);
        printf("\n--- Réparation de la Colonie ---\n");
        while (etatColonie->PvColonie < 1000) {
            // Réparation de la colonie en utilisant les matériaux disponibles
            if (stockMateriaux->bois >= 10) { stockMateriaux->bois -= 10; etatColonie->PvColonie += 10; }
            else if (stockMateriaux->pierres >= 10) { stockMateriaux->pierres -= 10; etatColonie->PvColonie += 10; }
            else if (stockMateriaux->feuilles >= 10) { stockMateriaux->feuilles -= 10; etatColonie->PvColonie += 10; }
            else if (stockMateriaux->argiles >= 10) { stockMateriaux->argiles -= 10; etatColonie->PvColonie += 10; }
            else { usleep(700000);
            printf("Matériaux insuffisants pour continuer les réparations. PV actuels : %d\n", etatColonie->PvColonie); break; }
            usleep(700000);
            printf("Réparation en cours... PV actuels : %d\n", etatColonie->PvColonie);
        }
    }
}

// Fonction pour calculer et appliquer la consommation des fourmis
void consommationNourriture(Fourmi *colonie, int tailleColonie, StockNourriture *stockNourriture) {
    GestionConsommation consommation = {0}; // Initialisation de la structure de gestion de la consommation

    // Zone de consommation - Les fourmis consomment les ressources
    affecterActivite(ZONE_STOCKAGE_NOURRITURE, "Les fourmis consomment les ressources.");

    // Calcul de la consommation pour chaque type de fourmi
    for (int i = 0; i < tailleColonie; i++) {
        if (colonie[i].statut == 3) { // Fourmis actives
            switch (colonie[i].type) {
                case REINE: consommation.consommationreine += CONSOMMATION_PAR_FOURMI; break;
                case MALE: consommation.consommationmales += CONSOMMATION_PAR_FOURMI; break;
                case NOURRICE: consommation.consommationnourrices += CONSOMMATION_PAR_FOURMI; break;
                case NETTOYEUSE: consommation.consommationnettoyeuses += CONSOMMATION_PAR_FOURMI; break;
                case ARCHITECTE: consommation.consommationarchitectes += CONSOMMATION_PAR_FOURMI; break;
                case BUTINEUSE: consommation.consommationbutineuses += CONSOMMATION_PAR_FOURMI; break;
                case SOLDAT: consommation.consommationsoldats += CONSOMMATION_PAR_FOURMI; break;
            }
        }
    }

    // Affichage de la consommation par type de fourmi
    
    usleep(700000);
    printf("\n--- Consommation de Nourriture par Type de Fourmi ---\n");
    
    usleep(700000);
    printf("Reine 👑: %.1f\n", consommation.consommationreine);
    
    usleep(700000);
    printf("Mâles ♂️: %.1f\n", consommation.consommationmales);
    
    usleep(700000);
    printf("Nourrices 🍼: %.1f\n", consommation.consommationnourrices);
    
    usleep(700000);
    printf("Nettoyeuses 🧹: %.1f\n", consommation.consommationnettoyeuses);
    
    usleep(700000);
    printf("Architectes 🏗️: %.1f\n", consommation.consommationarchitectes);
    
    usleep(700000);
    printf("Butineuses 🍯: %.1f\n", consommation.consommationbutineuses);
    
    usleep(700000);
    printf("Soldats 🛡️: %.1f\n", consommation.consommationsoldats);

    // Mise à jour des stocks de nourriture
    float consommationTotale = consommation.consommationreine + consommation.consommationmales + consommation.consommationnourrices + 
                               consommation.consommationnettoyeuses + consommation.consommationarchitectes + consommation.consommationbutineuses + consommation.consommationsoldats;

    if (consommationTotale > 0) {
        float consommationParRessource = consommationTotale / 4.0; // Répartition de la consommation totale sur les 4 types de ressources

        stockNourriture->sucre -= consommationParRessource; // Réduction du stock de sucre
        stockNourriture->champignon -= consommationParRessource; // Réduction du stock de champignons
        stockNourriture->feuille -= consommationParRessource; // Réduction du stock de protéines
        stockNourriture->graine -= consommationParRessource; // Réduction du stock de graines

        // Vérification des stocks
        if (stockNourriture->sucre < 0) stockNourriture->sucre = 0;
        if (stockNourriture->champignon < 0) stockNourriture->champignon = 0;
        if (stockNourriture->feuille < 0) stockNourriture->feuille = 0;
        if (stockNourriture->graine < 0) stockNourriture->graine = 0;

        // Alerte si stock vide
        if (stockNourriture->sucre == 0 || stockNourriture->champignon == 0 || stockNourriture->feuille == 0 || stockNourriture->graine == 0) {
            modifierEtAfficherAlerte(ALERTE_SONORE,"Un des stocks est vide");
        }

        // Affichage des stocks restants
        
        usleep(700000);
        printf("\n--- Stocks Restants de Nourriture ---\n");
        
        usleep(700000);
        printf("🍬 Sucre : %.1f, 🍄 Champignons : %.1f, 🍗 Protéines : %.1f, 🌱 Graines : %.1f\n",
       stockNourriture->sucre, stockNourriture->champignon, stockNourriture->feuille, stockNourriture->graine);

    } else {
        
        usleep(700000);
        printf("\nAucune consommation aujourd'hui.\n");
    }

    // Zone de fin de consommation - Les fourmis ont terminé leur consommation
    
    affecterActivite(ZONE_STOCKAGE_NOURRITURE, "Les fourmis ont terminé leur consommation.");
}
