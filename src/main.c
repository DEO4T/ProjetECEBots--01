#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "types.h"
#include "simulation.h"
#include "affichage.h"

int main(void) {
    srand((unsigned int)time(NULL));

    Simulation sim;
    init_simulation(&sim);
    init_affichage();

    rafraichir_ecran(&sim);

    // Boucle principale de la simulation
    while (sim.en_cours) {
        traiter_entrees_clavier(&sim);
        mettre_a_jour_simulation(&sim);
        rafraichir_ecran(&sim);

        Sleep(100); // Cadence à 10 cycles par seconde
    }

    return 0;
}