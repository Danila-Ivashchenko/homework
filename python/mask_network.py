
def to_ten_sistem(number):
	new_number = 0
	pow = 1
	while(len(number) > 0):
		new_number += int(number[-1]) * pow
		number = number[:-1]
		pow *= 2
	return new_number

def get_mask(size):
	right_size = 32 - size
	mask = ['1' for i in range(32)]
	new_mask = []
	for i in range(right_size):
		mask[32 - i - 1] = '0'
	buf = ""
	counter = 0
	for i in range(32):
		buf += mask[i]
		counter += 1
		if counter == 8:
			new_mask += [to_ten_sistem(buf)]
			counter = 0
			buf = ""
	return f"{new_mask[0]}.{new_mask[1]}.{new_mask[2]}.{new_mask[3]}"

def session():
	inp = input("Введите число от 0 до 32 для расчёта маски: ")
	try:
		print(get_mask(int(inp)))
		print("Для выхода введи пустую строку или '-1'")
		if inp == "" or inp == "-1":
			return
		session()
	except:
		print("Неправильный ввод")
		print("Для выхода введи пустую строку или '-1'")
		if inp == "" or inp == "-1":
			return
		session()
	return

session()

