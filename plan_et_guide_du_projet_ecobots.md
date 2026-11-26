# PROJET INFORMATIQUE 1 (ING1) : ECOBOTS
**Sujet :** Simulation de surveillance et nettoyage d'une réserve naturelle par drone et robot tout terrain.
**Langage :** C (Mode console)

---

## 1. CALENDRIER OFFICIEL

* **Semaine du 02/11/2026 :** Inscription et constitution des équipes (3 ou 4 étudiants du même groupe de TD).
* **Semaine du 09/11/2026 :** Lancement du projet et distribution du sujet.
* **Fin de semaine du 23/11/2026 :** Rendu à mi-parcours (dossier de conception uniquement, pas de code exigé).
* **Fin de semaine du 14/12/2026 :** Rendu final (code source complet + compte rendu final).
* **Semaines du 04/01/2027 et 11/01/2027 :** Soutenances orales devant jury.

---

## 2. RÉPARTITION DES RÔLES (ÉQUIPE DE 4)

### Membre 1 : Lead Développeur & Architecte (Toi)
* **Rôle :** Responsable de l'architecture du code et du moteur de simulation.
* **Pour le rendu mi-parcours (23/11) :**
  * Définir toutes les structures de données C (grille, drone, robot, déchets).
  * Mettre en place l'architecture modulaire des fichiers (`main.c`, `simulation.h/.c`, `affichage.h/.c`).
  * Commencer le codage du moteur de base (déplacements, détection, collecte).
* **Pour le rendu final (14/12) :**
  * Finaliser et déboguer le moteur de simulation.
  * Intégrer les extensions dans le code principal.
  * Réaliser le graphe d'appels final des fonctions.

### Membre 2 : Développeur IHM & Contrôles Clavier
* **Rôle :** Responsable de l'interface console et des interactions utilisateur.
* **Pour le rendu mi-parcours (23/11) :**
  * Concevoir la maquette visuelle de l'écran console (symboles, couleurs, légende, zone de statut).
  * Réaliser le logigramme de la boucle principale et de la gestion des touches clavier.
* **Pour le rendu final (14/12) :**
  * Coder le module `affichage.c` en utilisant `affichage_console.h` et `<conio.h>`.
  * Réaliser les captures d'écran commentées pour la partie tests du rapport final.

### Membre 3 : Concepteur Algorithmique & Extensions
* **Rôle :** Responsable de la logique algorithmique et du développement des bonus.
* **Pour le rendu mi-parcours (23/11) :**
  * Rédiger les logigrammes détaillés des algorithmes (apparition aléatoire des déchets, détection sur 8 cases voisines, collisions).
  * Choisir et concevoir le fonctionnement des 2 extensions obligatoires.
* **Pour le rendu final (14/12) :**
  * Coder les fonctions liées aux extensions choisies.
  * Rédiger la section listant les modifications apportées par rapport au rapport de mi-parcours.

### Membre 4 : Chef de Projet, Qualité & Documentation
* **Rôle :** Responsable de la planification, des tests et de la rédaction des dossiers.
* **Pour le rendu mi-parcours (23/11) :**
  * Créer le planning prévisionnel (diagramme de Gantt) et le tableau de répartition des tâches.
  * Mettre en forme le tableau des données et de leurs types C.
  * Assembler et relire le rapport de mi-parcours.
* **Pour le rendu final (14/12) :**
  * Élaborer les scénarios de tests et vérifier le respect strict du cahier des charges.
  * Rédiger le planning réel, les bilans (individuels et collectif) et la section sources/aide IA.
  * Préparer le support de présentation pour la soutenance.

---

## 3. CE QU'IL FAUT FAIRE ET COMMENT LE FAIRE

### ÉTAPE A : Le Dossier de Mi-Parcours (Semaine du 23/11/2026)
Ce dossier présente votre conception pour le jeu de base avant de coder. Il doit contenir 4 éléments :

1. **Planning prévisionnel et répartition des tâches :**
   * *Comment faire :* Faire un tableau ou diagramme de Gantt du 09/11/2026 au 11/01/2027 découpé par semaines (S1-S2 : Conception, S3-S4 : Codage jeu de base + tests, S5 : Extensions + rapport final, Vacances/Janvier : Préparation soutenance) en associant un responsable à chaque tâche.
2. **Analyse logique et chronologique (Logigramme global) :**
   * *Comment faire :* Utiliser Draw.io ou Lucidchart. Représenter la boucle complète : `Début` -> `Initialisation grille et entités` -> `Tant que simulation en cours` (Lecture clavier non bloquante -> Déplacement drone/robot -> Apparition aléatoire déchet -> Vérification détection -> Vérification ramassage/dépôt -> Rafraîchissement affichage) -> `Fin`.
3. **Tableau des principales données et de leurs types :**
   * *Comment faire :* Créer un tableau à 4 colonnes (`Nom de la donnée`, `Type C`, `Rôle`, `Valeurs possibles`).
   * *Données indispensables :*
     * `grille` : `int[LIGNES][COLONNES]` (0 = libre, 1 = obstacle, 2 = centre de collecte, 3 = déchet caché, 4 = déchet détecté).
     * `Drone` : `struct { int x; int y; }` (coordonnées actuelles).
     * `Robot` : `struct { int x; int y; int charge_actuelle; int capacite_max; }` (coordonnées et transport).
4. **Logigrammes des principaux algorithmes :**
   * *Comment faire :* Dessiner les étapes précises de chaque mécanique :
     * *Détection par le drone :* Double boucle `for` de `-1` à `+1` autour de `(drone.x, drone.y)`. Vérifier que les coordonnées restent dans la grille. Si la case contient un déchet caché (`3`), le passer à détecté (`4`).
     * *Apparition des déchets :* Tirer `x` et `y` avec `rand()`. Vérifier si `grille[x][y] == 0` (case libre). Si oui, placer un déchet (`3`).
     * *Déplacement du robot :* Vérifier que la case cible est dans la grille et n'est pas un obstacle (`!= 1`). Si la case contient un déchet détecté (`4`) et que le robot a de la place, ramasser le déchet (`grille[x][y] = 0` et `charge_actuelle++`). Si la case est un centre de collecte (`2`), vider la charge (`charge_actuelle = 0`).

---

### ÉTAPE B : Le Développement Technique (Règles et Contraintes)

1. **Architecture modulaire obligatoire :**
   * `main.c` : Contient uniquement le `main()` et la boucle principale qui appelle les fonctions de simulation et d'affichage.
   * `simulation.h` et `simulation.c` : Contiennent uniquement les structures et les fonctions de calcul/logique. **Aucun `printf` ni appel graphique autorisé dans ces fichiers.**
   * `affichage.h` et `affichage.c` : Contiennent uniquement les fonctions d'affichage console et de lecture clavier.
2. **Gestion de la console et du clavier :**
   * Utiliser `<conio.h>` avec `kbhit()` et `getch()` pour lire les touches sans bloquer le programme (ex: ZQSD pour le drone, IJKL ou flèches pour le robot).
   * Utiliser `affichage_console.h` (fonctions `gotoligcol`, `color`) pour mettre à jour uniquement les cases modifiées et éviter le scintillement de l'écran.
3. **Fonctionnalités obligatoires du jeu de base :**
   * Grille rectangulaire avec zones libres, obstacles infranchissables, au moins un centre de collecte et des déchets.
   * Apparition aléatoire de déchets sur des cases libres en continu.
   * Le drone peut survoler toutes les cases **sauf les obstacles infranchissables**.
   * Un déchet n'est détecté (et visible/ramassable pour le robot) que si le drone passe dessus ou sur l'une des **8 cases voisines**.
   * Le robot se déplace au sol (bloqué par les obstacles), ramasse les déchets détectés et les dépose dans un centre de collecte.

---

### ÉTAPE C : Les Extensions (Minimum 2 au choix)
**Attention :** Les extensions ne rapportent des points que si le jeu de base fonctionne à 100 %.

Liste des extensions proposées par le sujet (en choisir 2) :
1. **Différents types de déchets et statistiques** (ex: plastique, verre, métal avec compteurs affichés à côté de la grille).
2. **Niveau de batterie du drone et du robot avec stations de recharge** (compteur d'énergie qui baisse à chaque mouvement et remonte sur une case station).
3. **Génération aléatoire de la réserve** (placement aléatoire des obstacles au démarrage en s'assurant qu'aucune zone n'est inaccessible).
4. **Gestion de zones prioritaires dans la réserve** (zones où les déchets doivent être ramassés plus vite ou rapportent plus).
5. **Optimisation des déplacements du robot de collecte** (calcul d'itinéraire ou déplacement automatique vers le déchet détecté le plus proche).
*(Note : Un mode graphique avec raylib ou Allegro est autorisé en plus du mode console, mais déconseillé si vous ne maîtrisez pas parfaitement chaque fonction et pointeur utilisé, car le jury posera des questions techniques précises dessus).*

---

### ÉTAPE D : Le Rendu Final (14/12/2026) et Soutenances (Janvier 2027)
L'archive finale doit contenir le code source propre (commenté et indenté) ainsi qu'un compte rendu incluant :
1. **Planning réel et répartition réelle** des tâches (comparaison avec le prévisionnel).
2. **Liste des modifications** apportées par rapport à la conception du rapport de mi-parcours.
3. **Graphe d'appels final** du programme (schéma montrant quelle fonction appelle quelle autre fonction depuis `main`).
4. **Tests et résultats** avec captures d'écran commentées prouvant le bon fonctionnement de chaque règle (détection 8 cases, blocage obstacles, collecte, dépôt, extensions).
5. **Bilans individuels et collectif** sur le déroulement du projet.
6. **Sources et transparence** : mentionner les supports de cours, sites consultés et l'usage éventuel d'outils d'intelligence artificielle.