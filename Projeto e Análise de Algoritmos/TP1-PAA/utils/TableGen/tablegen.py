import matplotlib.pyplot as plt
import re
from pathlib import Path

def is_even(row):
    return row % 2 == 0

def extract_confidence_interval(filepath):
    with open(filepath, "r") as f:
        for line in f:
            if "Intervalo de Confiança" in line:
                match = re.search(r"\((.*); (.*)\)", line)
                if match:
                    return match.group(0)
    return None

def create_table(data, row_labels, ax):
    table = ax.table(cellText=data, rowLabels=row_labels, loc="center")
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1, 1.5)
    table.auto_set_column_width(col=list(range(len(data[0]))))
    for (row, col), cell in table.get_celld().items():
        cell.set_edgecolor("black")
        cell.get_text().set_horizontalalignment('center')
        if row == 0:
            cell.set_facecolor('#83c5be')
            cell.set_fontsize(13)
            cell.set_height(.08)
        elif is_even(row):
            cell.set_facecolor('#edf6f9')
        else:
            cell.set_facecolor('#e5e5e5')
    return table



filepath = Path("../../output/TPairedTests/")
folders = ["10","100","1000","10000","100000","1000000"]
algs = ["Insertion_Sort", "Merge_Sort", "Radix_Sort"]

results = {alg: [] for alg in algs}
for folder in folders:
    for alg in algs:
        file_path = filepath / f"n{folder}" / f"{alg}.out"
        confidence_interval = extract_confidence_interval(file_path)
        if confidence_interval:
            results[alg].append(confidence_interval)

fig, ax = plt.subplots()
ax.axis('off')

table_data = [folders] + list(results.values())
row_labels = ["Instância"] + [alg.replace("_", " ") for alg in algs]
create_table(table_data, row_labels, ax)

fig = plt.gcf()
fig.subplots_adjust(top=1, bottom=0, right=1, left=0, hspace=0, wspace=0)


plt.savefig("../../tables/algs_teste_t.png", bbox_inches='tight', pad_inches=0, transparent = True,  dpi=200)
