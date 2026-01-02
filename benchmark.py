import os
import subprocess
import random
import time

def generer_fichier_test(nom_fichier, nb_mots):
    mots = ["le", "la", "les", "un", "une", "des", "et", "ou", "mais", "donc", 
            "chat", "chien", "maison", "jardin", "fleur", "soleil", "lune", "etoile",
            "manger", "dormir", "courir", "sauter", "parler", "ecouter", "regarder",
            "rouge", "bleu", "vert", "jaune", "noir", "blanc", "orange", "violet",
            "grand", "petit", "gros", "maigre", "rapide", "lent", "fort", "faible",
            "programmation", "algorithme", "structure", "donnee", "memoire", "pointeur",
            "ordinateur", "clavier", "ecran", "souris", "internet", "reseau", "wifi"]
    
    with open(nom_fichier, "w") as f:
        for _ in range(nb_mots):
            f.write(random.choice(mots) + " ")
    
    print(f"Fichier généré : {nom_fichier} ({nb_mots} mots)")

def lancer_benchmark():
    # Créer le dossier pour les données de test
    dossier_data = "data_test"
    if not os.path.exists(dossier_data):
        os.makedirs(dossier_data)

    # Tailles des fichiers à tester
    tailles = [1000, 5000, 10000, 20000, 50000, 100000] # Vous pouvez augmenter si nécessaire
    
    # Nettoyer les fichiers de performances précédents
    for i in range(1, 4):
        if os.path.exists(f"performances_algo{i}.csv"):
            os.remove(f"performances_algo{i}.csv")
            
    # Créer un fichier de performances unifié
    if os.path.exists("performances.csv"):
        os.remove("performances.csv")

    print("=== DÉBUT DU BENCHMARK ===")
    
    # Compiler le programme
    subprocess.run(["make", "clean"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    subprocess.run(["make"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    print("Programme compilé.\n")

    for taille in tailles:
        fichier_test = os.path.join(dossier_data, f"test_{taille}.txt")
        
        # Générer le fichier
        generer_fichier_test(fichier_test, taille)
        
        print(f"--> Tests sur {taille} mots...")
        
        # Lancer les 3 algos séparément car le mode 4 n'existe peut-être pas ou écrit différemment
        # On va utiliser le binaire ./programme <algo> <fichier> <nb_mots> <afficher>
        # On n'affiche pas (0) pour ne pas polluer
        
        # Algo 1
        subprocess.run(["./programme", "1", fichier_test, "10", "0"], capture_output=True)
        # Algo 2
        subprocess.run(["./programme", "2", fichier_test, "10", "0"], capture_output=True)
        # Algo 3
        subprocess.run(["./programme", "3", fichier_test, "10", "0"], capture_output=True)
        
        print(f"    Terminé pour {taille} mots.")
        
        # Nettoyage fichier test
        # os.remove(fichier_test)

    print("\n=== BENCHMARK TERMINÉ ===")
    
    # Fusionner les fichiers CSV si nécessaire ou s'assurer que visualisation.py lit tout
    # Ici, vos algos écrivent dans performances_algoX.csv
    # On va les concaténer dans performances.csv pour faciliter la visualisation
    
    with open("performances.csv", "w") as outfile:
        # Pas d'entête globale car le format est simple
        for i in range(1, 4):
            fichier_algo = f"performances_algo{i}.csv"
            if os.path.exists(fichier_algo):
                with open(fichier_algo, "r") as infile:
                    outfile.write(infile.read())
                    
    print("Données fusionnées dans 'performances.csv'.")
    print("Lancez 'python3 visualisation.py' pour voir les courbes.")

if __name__ == "__main__":
    lancer_benchmark()

