import matplotlib.pyplot as plt
import csv
import sys

def visualiser_performances(fichier_csv):
    try:
        algos = []
        temps = []
        memoire_cumul_alloc = []
        memoire_max = []

        with open(fichier_csv, 'r') as csvfile:
            lecteur = csv.reader(csvfile)
            for ligne in lecteur:
                if not ligne: continue
                # Format attendu : cumul_alloc, cumul_desalloc, max_alloc, temps, [nom_algo]
                if len(ligne) >= 4:
                    memoire_cumul_alloc.append(int(ligne[0]) / 1024) # Conversion en Ko
                    memoire_max.append(int(ligne[2]) / 1024)         # Conversion en Ko
                    temps.append(float(ligne[3]))
                    
                    nom = ligne[4] if len(ligne) > 4 else f"Algo {len(algos)+1}"
                    algos.append(nom)

        if not algos:
            print("Aucune donnée trouvée dans le fichier CSV.")
            return

        # Configuration des graphiques
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

        # Graphique 1 : Temps d'exécution
        ax1.bar(algos, temps, color='skyblue')
        ax1.set_title('Temps d\'exécution par Algorithme')
        ax1.set_ylabel('Temps (secondes)')
        ax1.set_xlabel('Algorithme')

        # Graphique 2 : Utilisation Mémoire
        x = range(len(algos))
        width = 0.35
        ax2.bar([i - width/2 for i in x], memoire_cumul_alloc, width, label='Cumul Alloc (Ko)', color='lightgreen')
        ax2.bar([i + width/2 for i in x], memoire_max, width, label='Max Alloc (Ko)', color='salmon')
        
        ax2.set_title('Utilisation Mémoire')
        ax2.set_ylabel('Mémoire (Ko)')
        ax2.set_xticks(x)
        ax2.set_xticklabels(algos)
        ax2.legend()

        plt.tight_layout()
        plt.savefig('graphique_performances.png', dpi=100)
        print("Graphique sauvegardé sous 'graphique_performances.png'")
        plt.close() 

    except FileNotFoundError:
        print(f"Erreur : Le fichier '{fichier_csv}' est introuvable.")
    except Exception as e:
        print(f"Une erreur s'est produite : {e}")

if __name__ == "__main__":
    fichier = "performances.csv"
    if len(sys.argv) > 1:
        fichier = sys.argv[1]
    visualiser_performances(fichier)

