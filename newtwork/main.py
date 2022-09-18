input = open('input.txt', 'r')
output = open('output.txt', 'w')

array = []
array_pairs = []
array_islands = []

def arr_to_str(arr):
	print(arr)
	str = ""
	for item in arr:
		for i in item:
			str += f"{i}, "
	return str[:-1]

def find_pair(pair, arr):
	for item in arr:
		if pair == item:
			return True
	return False

def find_island(island, arr):
	for item in island:
		for island_checkd in arr:
			if item in island_checkd:
				return True
	return False


def clean_str(str):
	if str[-1] == '\n':
		return str[:-1]
	else:
		return str

str = input.readline()
n = int(str.split(' ')[-1])

array_of_points = [0 for i in range(n)]

str = input.readline()

while (str != ""):
	first, second = int(clean_str(str).split(' ')[0]), int(clean_str(str).split(' ')[1])
	if not(first in array):
		array += [first]
	if not(second in array):
		array += [second]
	array_pairs += [[first, second]]
	str = input.readline()

print(array_pairs)

count_islands = 0

for i in range(len(array_pairs)):
	buf = [array_pairs[i]]
	for j in range(len(array_pairs)):
		if i != j:
			if (array_pairs[i][0] in array_pairs[j] or array_pairs[i][1] in array_pairs[j]) and not(find_pair(array_pairs[i], array_islands) and find_pair(array_pairs[j], array_islands)):
				buf += [array_pairs[j]]
	if len(buf) > 0 and not(find_island(buf, array_islands)):
		count_islands += 1
		for pair in buf:
			for point in pair:
				array_of_points[point - 1] = count_islands
		array_islands += [buf]


for island in array_islands:
	output.write(arr_to_str(island) + '\n')

print(array_of_points)
for i in range(n):
	if array_of_points[i] == 0:
		count_islands += 1
		array_of_points[i] = count_islands

print(array_of_points)
print("Необходимо добавить: ", count_islands - 1, " связей")

output.close()
input.close()



