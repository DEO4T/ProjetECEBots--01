#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

// Dimensions de la réserve
#define LIGNES 32
#define COLONNES 32

// Types de cases de la réserve (Case.terrain)
#define CASE_LIBRE 0
#define CASE_OBSTACLE 1
#define CASE_CENTRE_COLLECTE 2
#define CASE_STATION_RECHARGE 3

// États d'un déchet (Case.etat_dechet)
#define DECHET_AUCUN 0
#define DECHET_CACHE 1
#define DECHET_DETECTE 2

// Coordonnées 2D d'un élément
typedef struct {
    int x; // Colonne : [0, COLONNES - 1]
    int y; // Ligne   : [0, LIGNES - 1]
} Position;

// Représentation d'une case unique de la réserve
typedef struct {
    int terrain;     // 0 = libre, 1 = obstacle, 2 = centre de collecte, 3 = station de recharge
    int etat_dechet; // 0 = aucun, 1 = déchet caché, 2 = déchet détecté
} Case;

// Drone de surveillance aérien
typedef struct {
    Position pos;    // Position actuelle du drone sur la grille
} Drone;

// Robot terrestre de collecte
typedef struct {
    Position pos;        // Position actuelle du robot au sol
    int charge_actuelle; // 0 au départ, <= capacite_max
    int capacite_max;    // Fixé à 3 dans init_simulation
} Robot;

// Structure globale regroupant tout l'état de la simulation
typedef struct {
    Case grille[LIGNES][COLONNES];
    Drone drone;
    Robot robot;
    int tour_actuel;
    bool en_cours;
} Simulation;

#endif // TYPES_H