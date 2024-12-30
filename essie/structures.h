#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <stdbool.h>

typedef enum {
    ZONE_MONDE_EXTERNE = 0,
    ZONE_ENTREE_PRINCIPALE,
    ZONE_STOCKAGE_NOURRITURE,
    ZONE_DEFENSE_COLONIE,
    ZONE_CHAMBRE_ROYALE,
    ZONE_STOCKAGE_OEUFS,
    ZONE_CIMETIERE
} ZoneFourmiliere;

typedef struct {
    ZoneFourmiliere zone;         // Zone actuelle
    char description[100];        // Description de l'activité
} Activite;



typedef struct {
    int nboeufs;       // Nombre d'œufs
    int nblarves;      // Nombre de larves
    int nbnymphes;     // Nombre de nymphes
    float consommationParJour; // Total de consommation par jour
} GestionNonAdultes;

typedef enum {
    REINE,
    SOLDAT,
    MALE,
    ARCHITECTES,
    NETTOYEUSES,
    BOUTINEUSES,
    NOURRICE,
} TypeFourmi;

typedef struct {
    TypeFourmi type; // Type de fourmi
    int age;
    int statut; // Statut numérique (exemple : 0=Oeuf, 1=Larve, etc.)
    int pv;
} Fourmi;

typedef struct {
    int jourActuel;
    int cycle;        // Cycle actuel
    char saison[10];
    char periode[20];
} Climat;

typedef struct {
    int bois, pierres, feuilles, argiles;
} StockMateriaux;

typedef struct {
    float sucre, champignons, proteines, graines;
} StockNourriture;      

typedef struct {
    float reine;
    float males;
    float nourrices;
    float nettoyeuses;
    float architectes;
    float butineuses;
    float soldats;
    float nonAdultes;
} GestionConsommation;

typedef struct {
    int nbSoldats;
    int niveauAlerte;  // 0: Normal, 1: Élevé, 2: Critique
    int nbEnnemisDetectes;
    int combatsEnCours;
    int otagesCaptures;
    int PVcolonie;
} Securite;

typedef enum {
    ALERTE_ODEUR = 0,        // Alerte si une odeur est détectée
    ALERTE_VERIF_VISUELLE,   // Alerte pour la vérification visuelle des fourmis
    ALERTE_SONORE,           // Alerte sonore si le stockage de nourriture est vide
    ALERTE_GUIDAGE_TACTILE,   // Alerte pour guider une ouvrière à une zone spécifique
    NB_ALERTES                // Nombre total d'alertes
} Alerte;

// Structure pour associer chaque alerte à une description
typedef struct {
    Alerte alerte;            // Type d'alerte
    char description[256];    // Description associée à l'alerte
} AlerteDescription;


typedef struct {
    int population[4]; // [Œufs, Larves, Nymphes, Adultes]
    float nourritureParStade[4]; // Consommation de nourriture par stade
} Elevage;

#endif // STRUCTURES_H
