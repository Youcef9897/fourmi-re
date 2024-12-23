#include <stdio.h>
#include <string.h>
#include "structures.h"

// Ajouter une activité avec une description et des zones
void definirActivite(Activite *activite, const char *description, const char *zones) {
    strcpy(activite->description, description);
    strcpy(activite->zones, zones);
}

// Afficher une activité
void afficherActivite(const Activite *activite) {
    printf("%s\n", activite->description);
    printf("Zones affectées : %s\n", activite->zones);
}
