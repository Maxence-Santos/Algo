import matplotlib.pyplot as plt
import pandas as pd


graph = 3 # choisir 1, 2 ou 3


if graph == 1:
    file_path = r'c:\Users\MATTHIEU\Documents\Cours\Informatique\C\TP confiture\resultats1.txt'
    data = pd.read_csv(file_path, delim_whitespace=True)
    unique_d_values = data['d'].unique()
    num_graphs = min(3, len(unique_d_values))

    fig, axes = plt.subplots(1, num_graphs, figsize=(20, 6))

    for i, d in enumerate(unique_d_values[:num_graphs]):
        ax = axes[i]
        subset_d = data[data['d'] == d]
        
        for k in subset_d['k'].unique():
            subset_k = subset_d[subset_d['k'] == k]
            ax.plot(subset_k['S'], subset_k['algo1_temps'], label=f'k={k}')
        
        ax.set_xlabel('S')
        ax.set_ylabel('Temps (s)')
        ax.set_title(f"Temps d'exécution de l'algorithme 1 en fonction de S et k pour d={d}")
        ax.legend()
        ax.grid(True)

    plt.tight_layout()
    plt.show()
elif graph == 2:
    file_path = r'c:\Users\MATTHIEU\Documents\Cours\Informatique\C\TP confiture\resultats2.txt'
    data = pd.read_csv(file_path, delim_whitespace=True)
    unique_d_values = data['d'].unique()
    num_graphs = min(3, len(unique_d_values))

    fig, axes = plt.subplots(1, num_graphs, figsize=(20, 6))

    for i, d in enumerate(unique_d_values[:num_graphs]):
        ax = axes[i]
        subset_d = data[data['d'] == d]
        
        for k in subset_d['k'].unique():
            subset_k = subset_d[subset_d['k'] == k]
            ax.plot(subset_k['S'], subset_k['algo2_temps'], label=f'k={k}')
        
        ax.set_xlabel('S')
        ax.set_ylabel('Temps (s)')
        ax.set_title(f"Temps d'exécution de l'algorithme 2 en fonction de S et k pour d={d}")
        ax.legend()
        ax.grid(True)

    plt.tight_layout()
    plt.show()
else:
    file_path = r'c:\Users\MATTHIEU\Documents\Cours\Informatique\C\TP confiture\resultats3.txt'
    data = pd.read_csv(file_path, delim_whitespace=True)
    unique_d_values = data['d'].unique()
    num_graphs = min(3, len(unique_d_values))

    fig, axes = plt.subplots(1, num_graphs, figsize=(20, 6))

    for i, d in enumerate(unique_d_values[:num_graphs]):
        ax = axes[i]
        subset_d = data[data['d'] == d]
        
        for k in subset_d['k'].unique():
            subset_k = subset_d[subset_d['k'] == k]
            ax.plot(subset_k['S'], subset_k['algo3_temps'], label=f'k={k}')
        
        ax.set_xlabel('S')
        ax.set_ylabel('Temps (s)')
        ax.set_title(f"Temps d'exécution de l'algorithme 3 en fonction de S et k pour d={d}")
        ax.legend()
        ax.grid(True)
        ax.set_ylim(0, 0.025)

    plt.tight_layout()
    plt.show()