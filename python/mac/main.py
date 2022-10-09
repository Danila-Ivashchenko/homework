file = open("info.txt", "r")
inp = input("Введите mac-адрес формата ('F0-79-59-70-A7-20'): ")
inp = "".join([char.upper() for char in inp.split('-')[:3]])

for line in file.readlines():
	if line[:6] == inp:
		print(line[7:])