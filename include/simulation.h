#ifndef SIMULATION_H
#define SIMULATION_H

#include "types.h"

// Initialisation
void init_simulation(Simulation *sim);
void init_grille(Simulation *sim);

// Déplacements et collisions
bool deplacer_drone(Simulation *sim, int dx, int dy);
bool deplacer_robot(Simulation *sim, int dx, int dy);

// Règles du jeu de base
void detecter_dechets_autour_drone(Simulation *sim);
void generer_dechet_aleatoire(Simulation *sim);
bool ramasser_dechet_robot(Simulation *sim);
bool deposer_dechets_centre(Simulation *sim);

// Cycle de simulation et point d'accroche extensions
void mettre_a_jour_simulation(Simulation *sim);
void gerer_extensions(Simulation *sim); // Réservé au Membre 3

#endif // SIMULATION_H