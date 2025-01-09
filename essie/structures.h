#ifndef STRUCTURES_H
#define STRUCTURES_H

// Définition des types de fourmis
typedef enum {
    REINE,         // Fourmi reine
    MALE,          // Fourmi mâle
    SOLDAT,        // Fourmi soldat
    ARCHITECTE,    // Fourmi architecte
    NETTOYEUSE,    // Fourmi nettoyeuse
    BUTINEUSE,     // Fourmi butineuse
    NOURRICE,      // Fourmi nourrice
} TypeFourmi;

// Structure représentant une fourmi
typedef struct {
    TypeFourmi type; // Type de fourmi
    int age;         // Âge de la fourmi
    int statut;      // Statut numérique (exemple : 0=Oeuf, 1=Larve, 2=Nymphe, 3=Adulte, 4=Mort)
    int pv;          // Points de vie de la fourmi
} Fourmi;

// ------------------------------------

// Définition du climat et des saisons
typedef struct {
    int jourActuel;  // Jour actuel dans le cycle
    int cycle;       // Cycle actuel
    char saison[10]; // Saison actuelle
    char periode[20];// Période actuelle de la saison
} Climat;

// Structure représentant une colonie de fourmis
typedef struct {
    int PvColonie;         // Points de vie de la colonie
    int nbTotalFourmis;    // Nombre total de fourmis dans la colonie
} Colonie;

// ------------------------------------

// Zones de la fourmilière
typedef enum {
    ZONE_MONDE_EXTERNE = 0,      // Monde extérieur
    ZONE_ENTREE_PRINCIPALE,      // Entrée principale de la fourmilière
    ZONE_STOCKAGE_NOURRITURE,    // Zone de stockage de la nourriture
    ZONE_DEFENSE_COLONIE,        // Zone de défense de la colonie
    ZONE_CHAMBRE_ROYALE,         // Chambre royale
    ZONE_STOCKAGE_OEUFS,         // Zone de stockage des œufs
    ZONE_CIMETIERE               // Cimetière
} ZoneFourmiliere;

// Structure représentant une activité dans une zone
typedef struct {
    ZoneFourmiliere zone;         // Zone actuelle
    char description[100];        // Description de l'activité
} Activite;

// Alertes et Communication dans la fourmilière
typedef enum {
    ALERTE_ODEUR = 0,        // Alerte si une odeur est détectée
    ALERTE_VERIF_VISUELLE,   // Alerte pour la vérification visuelle des fourmis
    ALERTE_SONORE,           // Alerte sonore si le stockage de nourriture est vide
    ALERTE_GUIDAGE_TACTILE,  // Alerte pour guider une ouvrière à une zone spécifique
    NB_ALERTES               // Nombre total d'alertes
} Alerte;

// Structure pour associer chaque alerte à une description
typedef struct {
    Alerte alerte;            // Type d'alerte
    char description[256];    // Description associée à l'alerte
} AlerteDescription;

// ------------------------------------

// Stockage des matériaux
typedef struct {
    int bois;      // Quantité de bois
    int pierres;   // Quantité de pierres
    int feuilles;  // Quantité de feuilles
    int argiles;   // Quantité d'argiles
} StockMateriaux;

// ------------------------------------

// Stockage de la nourriture
typedef struct {
    float sucre;         // Quantité de sucre : Sève des arbres , Fruits tombés au sol, Nectar des fleurs
    float champignon;   // Quantité de champignons : Champignons, Moisissures
    float feuille;     // Quantité de feuilles : Feuilles tombées au sol, Feuilles de plantes
    float graine;       // Quantité de graines : Plantes et herbes, Plantes tombées au sol
} StockNourriture;

// ------------------------------------

// Gestion de la consommation des fourmis
typedef struct {
    float consommationreine;        // Consommation de la reine
    float consommationmales;        // Consommation des mâles
    float consommationnourrices;    // Consommation des nourrices
    float consommationnettoyeuses;  // Consommation des nettoyeuses
    float consommationarchitectes;  // Consommation des architectes
    float consommationbutineuses;   // Consommation des butineuses
    float consommationsoldats;      // Consommation des soldats
} GestionConsommation;

// ------------------------------------

// Gestion de la reproduction
typedef struct {
    int nboeufs;                // Nombre d'œufs
    int nblarves;               // Nombre de larves
    int nbnymphes;              // Nombre de nymphes
    float consommationParJour;  // Total de consommation par jour
} GestionReproduction;


// Structure représentant un ennemi prédateur
typedef struct {
    int pv;                // Points de vie du prédateur
    int degats;            // Dégâts du prédateur
    TypeFourmi type;       // Type de l'ennemi 
                           // les prédateurs comme : Mammifères, Reptiles, Araignées, Oiseaux
                           // les Guêpes, les Mouches parasites, Fourmis guerrières d'autres espèces comme : légionnaires, sahariennes, etc. 
} EnnemiPredateur;

// ------------------------------------


#endif // STRUCTURES_H
