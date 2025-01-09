#include <stdio.h> // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard pour les fonctions utilitaires
#include "FourmisColonie.h" // Inclusion du fichier d'en-tête pour la gestion de la colonie de fourmis
#include "reproduction.h" // Inclusion du fichier d'en-tête pour la gestion de la reproduction

// Fonction pour gérer la reproduction dans la fourmilière
void reproduction(Fourmi *colonie, int *tailleColonie, GestionReproduction *gestionRepgestionReproduction, StockNourriture *stockNourriture, int nbOeufs) {
    int nbMales = 0; // Initialisation du compteur de mâles
    for (int i = 0; i < *tailleColonie; i++) { // Boucle pour parcourir la colonie
        if (colonie[i].type == MALE && colonie[i].statut == 3) { // Vérification si la fourmi est un mâle adulte
            nbMales++; // Incrémentation du compteur de mâles
        }
    }

    int nbReines = 0; // Initialisation du compteur de reines
    for (int i = 0; i < *tailleColonie; i++) { // Boucle pour parcourir la colonie
        if (colonie[i].type == REINE && colonie[i].statut == 3) { // Vérification si la fourmi est une reine adulte
            nbReines++; // Incrémentation du compteur de reines
        }
    }

    // Faire évoluer les non-adultes (œufs, larves, nymphes)
    evoluerNonAdultes(colonie, tailleColonie, gestionRepgestionReproduction); // Appel de la fonction pour faire évoluer les non-adultes

    if (nbReines > 0 && nbMales > 0) { // Vérification s'il y a au moins une reine et un mâle
        affecterActivite(ZONE_CHAMBRE_ROYALE, "Les mâles se dirigent vers la chambre royale pour féconder la reine."); // Affectation de l'activité de reproduction
        printf("La reproduction a eu lieu !\n"); // Affichage d'un message de reproduction
        nbOeufs = rand() % 10 + 5; // Génération aléatoire du nombre d'œufs pondus par la reine (entre 5 et 15)
        GestionReproduction *gestion = malloc(sizeof(GestionReproduction)); // Allocation dynamique de mémoire pour la gestion de la reproduction
        gestion->nboeufs += nbOeufs; // Ajout du nombre d'œufs pondus à la gestion de la reproduction
        printf("La reine a déposé %d œufs.\n", nbOeufs); // Affichage du nombre d'œufs pondus
        affecterActivite(ZONE_STOCKAGE_OEUFS, "Les nourrices recollectent et transportent des œufs vers la zone de stockage.");
    } else {
        printf("Pas de reproduction : Il faut une reine et des mâles actifs.\n"); // Affichage d'un message indiquant l'absence de reproduction
    }
    gestionRepgestionReproduction->nboeufs += nbOeufs; // Mise à jour du nombre d'œufs dans la gestion de la reproduction
    printf("nombre d'oeufs : %d\n", gestionRepgestionReproduction->nboeufs); // Affichage du nombre total d'œufs

}


// Fonction pour faire évoluer les non-adultes (œufs -> larves -> nymphes -> adultes)
void evoluerNonAdultes(Fourmi *colonie, int *tailleColonie, GestionReproduction *gestionRepgestionReproduction) {
    int temp = 0; // Initialisation d'une variable temporaire
    if (gestionRepgestionReproduction->nboeufs > 0) { // Vérification s'il y a des œufs
        temp = gestionRepgestionReproduction->nblarves; // Stockage du nombre de larves actuel
        gestionRepgestionReproduction->nblarves = gestionRepgestionReproduction->nboeufs; // Les œufs deviennent des larves
        printf("%d œufs sont devenus des larves.\n", gestionRepgestionReproduction->nboeufs); // Affichage du nombre d'œufs devenus des larves
        gestionRepgestionReproduction->nboeufs = 0; // Réinitialisation du nombre d'œufs
        printf("Un œuf est devenu une larve.\n"); // Affichage d'un message indiquant qu'un œuf est devenu une larve
        
    } else if (gestionRepgestionReproduction->nblarves > 0) { // Vérification s'il y a des larves
        gestionRepgestionReproduction->nbnymphes = gestionRepgestionReproduction->nblarves; // Les larves deviennent des nymphes
        gestionRepgestionReproduction->nblarves = 0; // Réinitialisation du nombre de larves
        printf("Une larve est devenue une nymphe.\n"); // Affichage d'un message indiquant qu'une larve est devenue une nymphe
    }
    if (gestionRepgestionReproduction->nbnymphes > 0) { // Vérification s'il y a des nymphes
        gestionRepgestionReproduction->nbnymphes--; // Une nymphe devient une fourmi adulte
    }
    printf("Une nymphe est devenue une fourmi adulte.\n"); // Affichage d'un message indiquant qu'une nymphe est devenue une fourmi adulte
    if (gestionRepgestionReproduction->nblarves > 0) { // Vérification s'il y a des larves
        gestionRepgestionReproduction->nbnymphes = temp; // Mise à jour du nombre de nymphes avec la valeur temporaire
    }
}

// Fonction pour afficher les états des non-adultes (œufs, larves, nymphes)
void afficherNonAdultes(GestionReproduction *gestionRepgestionReproduction) {
    printf("État des non-adultes:\n"); // Affichage de l'état des non-adultes
    printf(" - Œufs: %d\n", gestionRepgestionReproduction->nboeufs); // Affichage du nombre d'œufs
    printf(" - Larves: %d\n", gestionRepgestionReproduction->nblarves); // Affichage du nombre de larves
    printf(" - Nymphes: %d\n", gestionRepgestionReproduction->nbnymphes); // Affichage du nombre de nymphes
}
   
    
// Fonction pour consommer des ressources pour les non-adultes
void consommationRessourcesNonAdultes(GestionReproduction *gestionRepgestionReproduction, StockNourriture *stockNourriture) {
    int totalRepgestionReproduction = gestionRepgestionReproduction->nboeufs + gestionRepgestionReproduction->nblarves + gestionRepgestionReproduction->nbnymphes; // Calcul du nombre total de non-adultes
    float consommationParIndividu = 0.1; // Définition de la consommation par individu
    float totalConsommation = totalRepgestionReproduction * consommationParIndividu; // Calcul de la consommation totale

    static int activiteAffectee = 0; // Variable statique pour vérifier si l'activité a déjà été affectée

    if (totalConsommation <= stockNourriture->sucre) { // Vérification si les ressources suffisent
        stockNourriture->sucre -= totalConsommation; // Réduction des ressources disponibles
        if (!activiteAffectee) { // Vérification si l'activité n'a pas encore été affectée
            affecterActivite(ZONE_STOCKAGE_OEUFS, "Les nourrices se dirigent vers les œufs pour commencer à les nourrir."); // Affectation de l'activité de nourrissage
            activiteAffectee = 1; // Marquer l'activité comme affectée
        }
        printf("Les non-adultes ont consommé %.2f unités de sucre. Il reste %.2f unités de sucre.\n", totalConsommation, stockNourriture->sucre); // Affichage de la consommation et des ressources restantes
    } else {
        printf("Pas assez de sucre pour nourrir les non-adultes. Consommation nécessaire : %.2f, sucre disponible : %.2f.\n", totalConsommation, stockNourriture->sucre); // Affichage d'un message indiquant le manque de ressources
    }
}
