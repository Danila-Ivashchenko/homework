filename = input("Введите имя файла: ")
file = open(filename, 'r')
new_filename = "new_" + filename
new_file = open(new_filename, 'w')

is_comm = False

for line in file.readlines():
	new_line = ""
	for char_p in line:
		print(char_p)
		if char_p == '#':
			is_comm = True
			break
		else:
			new_line += char_p

	print(new_line)
	new_file.write(new_line)
	is_comm = False

new_file.close()
file.close()