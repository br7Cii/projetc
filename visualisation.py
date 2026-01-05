import matplotlib.pyplot as plt
import csv
import sys
import os

def visualiser_performances(fichier_csv):
    if not os.path.exists(fichier_csv):
        print(f"Erreur : Le fichier '{fichier_csv}' est introuvable.")
        return

    # Structure pour stocker les données : { "Algo1": { "x": [], "y_time": [], "y_mem": [] }, ... }
    data = {}

    try:
        with open(fichier_csv, 'r') as csvfile:
            lecteur = csv.reader(csvfile)
            for ligne in lecteur:
                if not ligne: continue
                
                if len(ligne) >= 7:
                    nb_total = int(ligne[0])
                    max_alloc = int(ligne[4]) / 1024
                    temps = float(ligne[5])
                    nom_algo = ligne[6]
                    
                    if nom_algo not in data:
                        data[nom_algo] = {"x": [], "y_time": [], "y_mem": []}
                    
                    data[nom_algo]["x"].append(nb_total)
                    data[nom_algo]["y_time"].append(temps)
                    data[nom_algo]["y_mem"].append(max_alloc)

        # Création des graphiques
        plt.style.use('ggplot')
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
        fig.suptitle('Comparaison des Performances des Algorithmes', fontsize=16)

        markers = ['o', 's', '^']
        colors = ['#3498db', '#e74c3c', '#2ecc71']

        # Graphique 1 : Temps
        for i, (algo, d) in enumerate(data.items()):
            # Trier les points par nombre de mots (x) pour avoir une courbe propre
            points = sorted(zip(d["x"], d["y_time"]))
            x_vals, y_vals = zip(*points) if points else ([], [])
            
            ax1.plot(x_vals, y_vals, 
                     marker=markers[i % len(markers)], 
                     color=colors[i % len(colors)], 
                     label=algo, linewidth=2, markersize=6)

        ax1.set_title('Temps d\'exécution par algorithme')
        ax1.set_xlabel('Nombre de mots (N)')
        ax1.set_ylabel('Temps (secondes)')
        ax1.legend()
        ax1.grid(True, linestyle='--', alpha=0.7)

        # Graphique 2 : Mémoire
        for i, (algo, d) in enumerate(data.items()):
            # Trier les points par nombre de mots (x)
            points = sorted(zip(d["x"], d["y_mem"]))
            x_vals, y_vals = zip(*points) if points else ([], [])
            
            ax2.plot(x_vals, y_vals, 
                     marker=markers[i % len(markers)], 
                     color=colors[i % len(colors)], 
                     label=algo, linewidth=2, markersize=6)

        ax2.set_title('Complexité Spatiale')
        ax2.set_xlabel('Taille du fichier (nombre de mots)')
        ax2.set_ylabel('Mémoire Max (Ko)')
        ax2.legend()
        ax2.grid(True)

        plt.tight_layout(rect=[0, 0.03, 1, 0.95])
        output_file = 'courbes_performances.png'
        plt.savefig(output_file, dpi=150)
        print(f"Graphique sauvegardé sous '{output_file}'")
        plt.close()

    except Exception as e:
        print(f"Une erreur s'est produite : {e}")

if __name__ == "__main__":
    fichier = "performances.csv"
    if len(sys.argv) > 1:
        fichier = sys.argv[1]
    visualiser_performances(fichier)
