#include <stdlib.h>
#include "simulation.h"

// RAPPEL STRICT DU CDC : Aucun printf ni appel d'affichage dans ce fichier.

void init_simulation(Simulation *sim) {
    sim->tour_actuel = 0;
    sim->en_cours = true;

    // Position initiale du drone
    sim->drone.pos.x = 1;
    sim->drone.pos.y = 1;

    // Position et capacité initiale du robot
    sim->robot.pos.x = 2;
    sim->robot.pos.y = 2;
    sim->robot.charge_actuelle = 0;
    sim->robot.capacite_max = 3;

    init_grille(sim);

    // Génération de quelques déchets initiaux sur la réserve
    for (int i = 0; i < 3; i++) {
        generer_dechet_aleatoire(sim);
    }
}

void init_grille(Simulation *sim) {
    // 1. Remplir toute la réserve en zone libre sans déchet
    for (int y = 0; y < LIGNES; y++) {
        for (int x = 0; x < COLONNES; x++) {
            sim->grille[y][x].terrain = CASE_LIBRE;
            sim->grille[y][x].etat_dechet = DECHET_AUCUN;
        }
    }

    // 2. Placer le centre de collecte en (0, 0)
    sim->grille[0][0].terrain = CASE_CENTRE_COLLECTE;

    // 3. Placer une station de recharge (prévue dans ton tableau : terrain = 3)
    sim->grille[LIGNES - 1][COLONNES - 1].terrain = CASE_STATION_RECHARGE;

    // 4. Placer des obstacles infranchissables fixes pour le jeu de base
    for (int x = 8; x <= 14; x++) {
        sim->grille[5][x].terrain = CASE_OBSTACLE;
    }
    for (int y = 10; y <= 18; y++) {
        sim->grille[y][22].terrain = CASE_OBSTACLE;
    }
    sim->grille[12][10].terrain = CASE_OBSTACLE;
    sim->grille[12][11].terrain = CASE_OBSTACLE;
    sim->grille[13][10].terrain = CASE_OBSTACLE;
}

bool deplacer_drone(Simulation *sim, int dx, int dy) {
    int nx = sim->drone.pos.x + dx;
    int ny = sim->drone.pos.y + dy;

    // Blocage sur les bords de la réserve
    if (nx < 0 || nx >= COLONNES || ny < 0 || ny >= LIGNES) {
        return false;
    }

    // Blocage sur les obstacles infranchissables
    if (sim->grille[ny][nx].terrain == CASE_OBSTACLE) {
        return false;
    }

    sim->drone.pos.x = nx;
    sim->drone.pos.y = ny;

    // Détection automatique sur sa case et les 8 cases voisines
    detecter_dechets_autour_drone(sim);
    return true;
}

bool deplacer_robot(Simulation *sim, int dx, int dy) {
    int nx = sim->robot.pos.x + dx;
    int ny = sim->robot.pos.y + dy;

    // Blocage sur les bords de la réserve
    if (nx < 0 || nx >= COLONNES || ny < 0 || ny >= LIGNES) {
        return false;
    }

    // Blocage sur les obstacles infranchissables
    if (sim->grille[ny][nx].terrain == CASE_OBSTACLE) {
        return false;
    }

    sim->robot.pos.x = nx;
    sim->robot.pos.y = ny;

    // Interactions automatiques sur la case d'arrivée
    ramasser_dechet_robot(sim);
    deposer_dechets_centre(sim);
    return true;
}

void detecter_dechets_autour_drone(Simulation *sim) {
    // Parcours du voisinage 3x3 (case actuelle + 8 cases adjacentes)
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int cx = sim->drone.pos.x + dx;
            int cy = sim->drone.pos.y + dy;

            if (cx >= 0 && cx < COLONNES && cy >= 0 && cy < LIGNES) {
                if (sim->grille[cy][cx].etat_dechet == DECHET_CACHE) {
                    sim->grille[cy][cx].etat_dechet = DECHET_DETECTE;
                }
            }
        }
    }
}

void generer_dechet_aleatoire(Simulation *sim) {
    for (int essai = 0; essai < 50; essai++) {
        int x = rand() % COLONNES;
        int y = rand() % LIGNES;

        bool case_occupee = (x == sim->drone.pos.x && y == sim->drone.pos.y) ||
                            (x == sim->robot.pos.x && y == sim->robot.pos.y);

        if (!case_occupee &&
            sim->grille[y][x].terrain == CASE_LIBRE &&
            sim->grille[y][x].etat_dechet == DECHET_AUCUN) {
            
            sim->grille[y][x].etat_dechet = DECHET_CACHE;
            break;
        }
    }
}

bool ramasser_dechet_robot(Simulation *sim) {
    int rx = sim->robot.pos.x;
    int ry = sim->robot.pos.y;

    // Ramassage autorisé uniquement si le déchet a été détecté et si le robot n'est pas plein
    if (sim->grille[ry][rx].etat_dechet == DECHET_DETECTE &&
        sim->robot.charge_actuelle < sim->robot.capacite_max) {
        
        sim->grille[ry][rx].etat_dechet = DECHET_AUCUN;
        sim->robot.charge_actuelle++;
        return true;
    }
    return false;
}

bool deposer_dechets_centre(Simulation *sim) {
    int rx = sim->robot.pos.x;
    int ry = sim->robot.pos.y;

    // Dépôt automatique lorsque le robot atteint un centre de collecte avec des déchets
    if (sim->grille[ry][rx].terrain == CASE_CENTRE_COLLECTE &&
        sim->robot.charge_actuelle > 0) {
        
        sim->robot.charge_actuelle = 0;
        return true;
    }
    return false;
}

void gerer_extensions(Simulation *sim) {
    // [LAISSE VIDE POUR LE MEMBRE 3]
    // Ajouter ici les fonctions des 2 extensions (ex. : gestion batterie / station de recharge)
    (void)sim;
}

void mettre_a_jour_simulation(Simulation *sim) {
    sim->tour_actuel++;

    // Apparition aléatoire d'un déchet tous les 30 cycles
    if (sim->tour_actuel % 30 == 0) {
        generer_dechet_aleatoire(sim);
    }

    // Appel des extensions développées par le Membre 3
    gerer_extensions(sim);
}