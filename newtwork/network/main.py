import networkx as nx
import matplotlib.pyplot as plt

def clean_str(str):
	if str[-1] == '\n':
		return str[:-1]
	else:
		return str

input = open('input_unnown.txt', 'r')

n = int(input.readline().split(' ')[-1])
arr = [0] * n
arr_pairs = []

count_isle = 1
islands = 0

for line in input.readlines():
	first, second = int(clean_str(line).split(' ')[0]), int(clean_str(line).split(' ')[1])
	arr_pairs += [(first, second)]
	if arr[first - 1] == arr[second - 1] == 0:
		arr[first - 1] = arr[second - 1] = count_isle
		count_isle += 1
		islands += 1
	elif arr[first - 1] != 0 and arr[second - 1] != 0:
		for i in range(n):
			if arr[i] == arr[second - 1]:
				arr[i] = arr[first - 1]
		islands -= 1
	elif arr[first - 1] != 0 or arr[second - 1] != 0:
		if arr[first - 1] != 0:
			arr[second - 1] = arr[first - 1]
		elif arr[second - 1] != 0:
			arr[first - 1] = arr[second - 1]
	count_isle += 1

input.close()

graph = nx.Graph()

for pair in arr_pairs:
	graph.add_edge(pair[0], pair[1])

for i in range(n):
	if arr[i] == 0:
		arr[i] = count_isle
		graph.add_node(str(i + 1))
		count_isle += 1
		islands += 1

print(islands - 1)
nx.draw(graph, with_labels = True)
plt.show()



