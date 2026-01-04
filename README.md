#              Projet C                     #


ENG Johnatan 
CHING Brian
TP3

Description :
Ce projet consiste à développer trois algorithmes permettant de compter l’occurrence des mots dans un texte. Chaque algorithme utilise une approche différente pour gérer et organiser les mots afin de mesurer leur fréquence. L’objectif est à la fois d’analyser l’efficacité des algorithmes et de comprendre différentes structures de données pour le traitement de texte.

-------------------------------------------------
Fichiers inclus :
-------------------------------------------------

1. **fonction_allocation.h**  
   - Script qui comporte les structures et fonctions nécessaires pour l'allocation mémoire.  

2. **fonction_allocation.c**
   - Contient toutes les fonctions d’allocation mémoire utilisées dans le projet.
   - Permet de gérer la mémoire dynamiquement pour les listes ou tableaux de mots.
   - Inclut le suivi des allocations et désallocations pour détecter d’éventuelles fuites mémoire.

3. **fonction_commun.h**
   - Script qui contient la structure utilisée pour les algorithmes 1 et 3.

4. **algo1.h**
   - Contient toutes les déclarations des fonctions utilisées pour l'algorithme 1.

5. **algo1.c** 
   - Contient toutes les fonctions permettant de compter l'occurence sous forme de liste chaînée.
   - Permet d'insérer les nouveaux mots en tête de liste.
   - Inclut un tri par fusion par rapport à l'occurence de manière décroissante.
   - Fournit des fonctions pour afficher les résultats, écrire dans un fichier de sortie, et enregistrer les performances

6. **algo2.h**
   - Contient toutes les déclarations des fonctions et des structures utilisées pour l'algorithme 2.

7. **algo2.c**
   - Contient toutes les fonctions permettant de compter l’occurrence des mots sous forme de tableau dynamique.
   - Permet d’ajouter de nouveaux mots au tableau et de réallouer dynamiquement la mémoire si nécessaire.
   - Inclut un tri des mots par fréquence de manière décroissante.
   - Fournit des fonctions pour afficher les résultats, écrire dans un fichier de sortie, et enregistrer les performances.

8. **algo3.h**
   - Contient toutes les déclarations des fonctions utilisées pour l'algorithme 3.  

9. **algo3.c** 
   - Contient toutes les fonctions permettant de compter l'occurence sous forme de liste chaînée.
   - Permet d'insérer les nouveaux mots en ordre alphabétique grâce à la recherche dichotomique.
   - Inclut un tri par fusion par rapport à l'occurence de manière décroissante.
   - Fournit des fonctions pour afficher les résultats, écrire dans un fichier de sortie, et enregistrer les performances

10. **makefile** 
   - Permet de compiler tous les fichiers C en même temps.

11. **visualisation.py**
   - Script Python permettant de visualiser graphiquement les performances des différents algorithmes.
   - Lit un fichier CSV contenant les données de performances :
      - Mémoire cumulée allouée (cumul_alloc),
      - Mémoire maximale utilisée (max_alloc),
      - Temps d’exécution,
      - Nom de l’algorithme.
   
   - Génère deux graphiques côte à côte :
      - Temps d’exécution par algorithme,
      - Utilisation mémoire (cumul et maximum).
      - Sauvegarde le graphique sous le nom graphique_performances.png.
   
   - Permet de comparer facilement l’efficacité et la consommation mémoire des algorithmes.

12. **graphique_mots.py**
   - Script Python permettant de générer un graphique en barres des mots les plus fréquents à partir d’un fichier de résultats.
   - Personnalise le graphique avec :
      - Barres verticales colorées,
      - Valeurs affichées au-dessus de chaque barre,
      - Grille horizontale pour faciliter la lecture.
   - Limite l’affichage aux 20 mots les plus fréquents pour la lisibilité.
   - Permet de sauvegarder le graphique dans un fichier PNG.
   - Utile pour visualiser rapidement quels mots apparaissent le plus dans un texte ou comparer plusieurs textes.

13. **benchmark.py**
   - Script Python permettant de tester et comparer les performances des trois algorithmes sur des fichiers textes de tailles variables.
   - Génération de fichiers texte de test contenant un nombre donné de mots aléatoires.
   - Lancement automatique des trois algorithmes (algo1, algo2, algo3) sur chaque fichier de test.
   - Collecte et fusion des résultats de performance (temps d’exécution et mémoire utilisée) dans un fichier unique performances.csv.
   - Nettoyage automatique des fichiers temporaires et anciens fichiers de performances.

-------------------------------------------------
Instructions d'installation :
-------------------------------------------------

1. Téléchargez le fichier du projet. 
2. Assurez-vous d'avoir Visual Studio dans votre machine. 
3. Sur le terminal, ecrivez **make programme**
4. Sur le terminal, ecrivez **./programme <algo> <fichier_texte> <nombre_mots> <Afficher> <Fichier_sortie> [longueur_min]**
   - <algo> : 1, 2 ou 3 pour choisir l’algorithme correspondant (algo1, algo2, algo3).
   - <fichier_texte> : chemin vers le fichier texte à analyser.
   - <nombre_mots> : nombre de mots les plus fréquents à afficher ou sauvegarder.
   - <afficher> : 0 pour ne pas afficher les résultats à l’écran, 1 pour afficher.
   - [longueur_min] (optionnel) : longueur minimale des mots à prendre en compte.

-------------------------------------------------
Instructions d'utilisation :
-------------------------------------------------

1. Compiler et lancer les différents algorithmes via le Makefile :
   make programme

2. Lancer un algorithme spécifique sur un fichier texte :
   ./programme <algo> <fichier_texte> <nombre_mots> <Afficher> <Fichier_sortie> [longueur_min]

3. Lancer le programme benchmark.py pour stocker les performances de toutes les algorithmes sous forme de fichier csv.

4. Lancer le programme visualiation.py pour afficher les performances sous forme de graphique.

5. Lancer le programme graphique_mots.py pour voir les occurences des mots sous forme graphique :

Remarques :

-------------------------------------------------
- Assurez vous de mettre tous les arguments obligatoires lors de la compilation.
- N'oubliez pas de mettre le fichier où les occurences sont comptées quand vous utilisez le programme graphique_mots.py.
-------------------------------------------------

Difficultés rencontrées :

-------------------------------------------------
- Faire l'affichage avec Python. 
- Faire les fonctions d'allocations.
- Gérer les mots contenant des apostrophes ou des tirets, pour que des mots comme l’avion ou porte-monnaie soient comptés correctement comme un seul mot.
-------------------------------------------------

