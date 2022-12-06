import networkx as nx
from matplotlib import pyplot as plt

filename_1 = "email-Eu-core.txt"
filename_2 = "3980.edges"

edges = nx.read_edgelist(filename_1)
nodes = nx.read_adjlist(filename_1)

my_graph = nx.Graph()
nodes_gr = edges.nodes
edges_gr = edges.edges

my_graph.add_edges_from(edges.edges())
my_graph.add_nodes_from(nodes)

edges_counts = []
clear_edges = []

for edge in edges_gr:
    flag = True
    for item in clear_edges:
        if item[0] == edge[1] and item[1] == edge[0]:
            flag = False
            print(edge, item)
    if flag:
        clear_edges += [edge]

for node_1 in my_graph.nodes:
    for node_2 in my_graph.nodes:
        if node_1 != node_2:
            try:
                n= nx.shortest_path_length(my_graph, node_1, node_2)
                if len(edges_counts) < n:
                    for i in range(n):
                        if len(edges_counts) < n:
                            edges_counts += [0]
                    edges_counts[n - 1] += 1
                else:
                    edges_counts[n - 1] += 1
            except nx.NetworkXNoPath:
                pass

# print(edges_counts)
x = [i + 1 for i in range(len(edges_counts))]
# print(x)

fig, ax = plt.subplots()
ax.bar(x, edges_counts, width=0.3)
for bar in ax.patches:
    ax.annotate(bar.get_height(), (bar.get_x() + bar.get_width() / 2, bar.get_height()), ha="center", va="bottom")


moda = 0
max_edges_count = 0
sum_edges_cunt = 0
for i in range(len(edges_counts)):
    sum_edges_cunt += edges_counts[i]
    if edges_counts[i] > max_edges_count:
        max_edges_count = edges_counts[i]
        moda = i + 1

mediana_count = sum_edges_cunt / 2
min_dif = max(edges_counts)
mediana = 1
for i in range(len(edges_counts)):
    if abs(mediana_count - edges_counts[i]) < min_dif:
        min_dif = abs(mediana_count - edges_counts[i])
        mediana = i + 1

rects1 = ax.bar(len(edges_counts), 0.35, label=f'''мода = {moda}''')
rects2 = ax.bar(len(edges_counts), 0.35, label=f'''медиана = {mediana}''')
rects3 = ax.bar(len(edges_counts), 0.35, label=f'''кол-во вершин = {len(nodes)}''')
rects3 = ax.bar(len(edges_counts), 0.35, label=f'''кол-во рёбер = {len(edges_gr)}''')
ax.legend()
ax.set_title("Частоты длин связей между вершинами")
ax.set_xlabel("Длина пути между вершинами")
ax.set_ylabel("Частоты")

plt.show()

