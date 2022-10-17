file = open("degree_dataset_1000_vertices.txt", "r")
file_out = open("output.txt", "w")
line = file.readline()
count, n = [int(c) for c in line.split(' ')]
peaks = []
for i in range(count):
	peaks += [0]
for line in file.readlines():
	f, s = [int(c) for c in line.split(' ')]
	peaks[f - 1] += 1
	peaks[s - 1] += 1
file.close
for peak in peaks:
	file_out.write(str(peak) + ' ')
file_out.close