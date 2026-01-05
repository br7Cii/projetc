import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import sys
import os

def generer_graphique_mots(fichier_entree, titre="Mots les plus fréquents", fichier_sortie="graphique_mots.png"):
    """
    Génère un graphique en barres des mots les plus fréquents à partir d'un fichier de résultats.
    
    Format attendu du fichier (une ligne par mot) :
    mot frequence
    exemple: les 26
    """
    if not os.path.exists(fichier_entree):
        print(f"Erreur : Le fichier '{fichier_entree}' est introuvable.")
        return
    
    mots = []
    frequences = []
    
    with open(fichier_entree, 'r', encoding='utf-8') as f:
        for ligne in f:
            ligne = ligne.strip()
            if not ligne:
                continue
            
            # Séparer le mot et sa fréquence
            parties = ligne.split()
            if len(parties) >= 2:
                mot = parties[0]
                freq = int(parties[1])
                mots.append(mot)
                frequences.append(freq)
    
    if not mots:
        print("Aucune donnée valide trouvée dans le fichier.")
        return
    
    # Limiter à 20 mots maximum pour la lisibilité
    if len(mots) > 20:
        mots = mots[:20]
        frequences = frequences[:20]
    
    # Création du graphique
    plt.style.use('ggplot')
    fig, ax = plt.subplots(figsize=(12, 8))
    x_pos = range(len(mots))
    bars = ax.bar(x_pos, frequences, color='steelblue', edgecolor='navy', linewidth=0.5)

    ax.set_xticks(x_pos)
    ax.set_xticklabels(mots, rotation=45, ha='right')
    ax.set_xlabel('Mots', fontsize=12, fontweight='bold')
    ax.set_ylabel('Fréquence', fontsize=12, fontweight='bold')
    ax.set_title(titre, fontsize=16, fontweight='bold', pad=20)
    
    for i, (bar, freq) in enumerate(zip(bars, frequences)):
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2, height, 
               f' {freq}', 
               ha='center', va='bottom', fontsize=10, fontweight='bold')
    
    ax.grid(True, axis='y', linestyle='--', alpha=0.3)
    
    plt.tight_layout()
    
    plt.savefig(fichier_sortie, dpi=150, bbox_inches='tight')
    print(f"Graphique généré avec succès : {fichier_sortie}")
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 graphique_mots.py <fichier_resultats> [fichier_image]")
        print("  fichier_resultats : fichier contenant les résultats (format: mot frequence)")
        print("  fichier_image : nom du fichier image à générer (optionnel, défaut: graphique_mots.png)")
        sys.exit(1)
    
    fichier_entree = sys.argv[1]
    fichier_image = sys.argv[2] if len(sys.argv) > 2 else "graphique_mots.png"
    
    generer_graphique_mots(fichier_entree, fichier_sortie=fichier_image)

