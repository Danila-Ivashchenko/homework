from ast import main
import random as rd
import string
from traceback import print_tb

def is_primary(num):
	for i in range(2, int(num / 2)):
		if num % i == 0:
			return False
	return True

def are_primary(num1, num2):
	for i in range(2, min(num1, num2) + 1):
		if num1 % i == 0 and num2 % i == 0:
			return False
	return True

def generate_primary_num2(max, min):
	arr = []
	for i in range(max, min, -1):
		if is_primary(i):
			arr += [i]

	index = 2 + int(rd.random() * (len(arr) - 3))
	return arr[index]

def generate_n(p, q):
	return p * q

def generate_f(p, q):
	return (p - 1) * (q - 1)

def generate_d(e, f):
	d = 3
	while True:
		if (e * d) % f == 1 and e != d:
			return d
		d += 1

def generate_e(f):
	e = 3
	while not(is_primary(e)) or not(are_primary(e, f)):
		e += 1
	return e

def generate_all():
	p, q = generate_primary_num2(200, 100), generate_primary_num2(200, 100)
	n = p * q
	f = (p - 1) * (q - 1)
	e = generate_e(f)
	d = generate_d(e, f)
	public_key = (e, n)
	privat_key = (d, n)

	return (privat_key, public_key)

def coding(mess, public_key):
	e, n = public_key[0], public_key[1]
	coded_mess = ""
	for letter in mess:
		if ord(letter) < n:
			coded_mess += str(ord(letter) ** e % n) + ' '
	return coded_mess[:-1]

def decoding(coded_mess, privat_key):
	d, n = privat_key[0], privat_key[1]
	new_mess = "".join([chr((int(letter) ** d) % n) for letter in coded_mess]) 
	return new_mess

def session():
	print("Генерация ключей происходит автоматически")
	keys = generate_all()
	privat_key, public_key = keys[0], keys[1]
	print("Приватный ключ: ", privat_key)
	print("Публичный ключ: ", public_key)
	manual()
	commands(privat_key, public_key)

def commands(privat_key, public_key):
	command = int(input("Введите команду: "))
	if command == 1:
		mess = input("Введите сообщение: ")
		coded_mess = coding(mess, public_key)
		print(coded_mess)
	elif command == 2:
		coded_mess = input("Введите сообщение: ").split(' ')
		print(coded_mess)
		mess = decoding(coded_mess, privat_key)
		print(mess)
	elif command == 3:
		print("Приватный ключ: ", privat_key)
		print("Публичный ключ: ", public_key)
	elif command == 4:
		manual()
	elif command == 5:
		return
	else:
		print("Команда нераспознана")
	return commands(privat_key, public_key)

def manual():
	print("Закодировать сообщение: 1")
	print("Декодировать сообщение: 2")
	print("Вывести ключи: 3")
	print("Вывести мануал: 4")
	print("Выйти из программы: 5")

session()