import json
import os
import requests


URL = "https://stt.api.cloud.yandex.net/speech/v1/stt:recognize"


def read_file(filename):
    with open(filename, "rb") as f:
        file = f.read()
    return file

def get_text(filename):
    text = ""
    with open(filename, "r", encoding="UTF-8") as f:
        for line in f.readlines():
            text += line
    return  text
def set_a_to_t_params(TOKEN, ID_FOLDER, lang="ru-Ru"):
    headers = {'Authorization': f'Bearer {TOKEN}'}
    params = {
        'lang': lang,
        'folderId': ID_FOLDER,
        'sampleRateHertz': 48000,
    }
    return headers, params

def set_t_to_a_params(text, TOKEN, ID_FOLDER, lang="ru-RU", voice="alena", emotion="neutral"):
    headers = {'Authorization': f'Bearer {TOKEN}'}
    params = {
        'text' : text,
        'lang': lang,
        'voice' : voice,
        'emotion' : emotion,
        'folderId': ID_FOLDER,
        'sampleRateHertz': 48000,
    }
    return headers, params

def audio_to_text(filename, TOKEN, ID_FOLDER):
    headers, params = set_a_to_t_params(TOKEN, ID_FOLDER)
    audio = read_file(filename)
    responce = requests.post(URL, params=params, headers=headers, data=audio)
    text = responce.json()["result"]
    with open(filename.split(".")[0] + ".txt", "w", encoding="UTF-8") as out:
        out.write(text)
    return text

def text_to_audio(filename,TOKEN, ID_FOLDER, lang='ru-RU', voice="alena", emotion="neutral"):
    text = get_text(filename)
    headers, params = set_t_to_a_params(text, TOKEN, ID_FOLDER, lang, voice, emotion)
    url =  "https://tts.api.cloud.yandex.net/speech/v1/tts:synthesize"
    responce = requests.post(url, params=params, headers=headers)
    chunks = responce.iter_content(chunk_size=1024)
    with open(filename.split(".")[0] + ".ogg", "wb") as out:
        for chunk in chunks:
            out.write(chunk)
    return True


TOKEN = "t1.9euelZrMlIqbnpXJj5yVlciQnM6Lie3rnpWais-QkJ7OlZOcic6Llpaenprl8_cjEQZj-e9QAAUS_t3z92M_A2P571AABRL-.gOBX76B6Hs3jPwMekiARb_XmSTSc58AkCSFjGF4MbiQfvK60DR5qaFC-S3lU2EPdnMnZf3rUahrAvIhw6YF3CQ"
ID_FOLDER = "b1gtf3dqupicap0o7l1v"

# text_to_audio("Федя хох)", TOKEN, ID_FOLDER, voice="filipp", emotion="good")
# print(audio_to_text("new_file.ogg", TOKEN, ID_FOLDER))

def print_menu():
    print("[1] Распознование речи")
    print("[2] Перевод текста в речь")
    print("[3] Ввод token")
    print("[4] Ввод folder id")
    print("[5] Выход")


print("Приложение для работы с Yabdex speachkit")
print("Для работы введите token и folder id")
print("Введите token")
TOKEN = input()
# print("Введите folder id")
# ID_FOLDER = input()
print_menu()
command = int(input())
while(command != 5):
    if command == 1:
        print("Введите имя 'ogg' файла: ")
        filename = input()
        if (audio_to_text(filename, TOKEN, ID_FOLDER) != ''):
            print("Файл записан")
        else:
            print("Файл был пустым или произошла обшибка")
    elif command == 2:
        print("Введите имя файла c текстом: ")
        filename = input()
        text = get_text(filename)
        if (text_to_audio(filename, TOKEN, ID_FOLDER, voice="filipp", emotion="good")):
            print("Файл записан")
        else:
            print("Файл был пустым или произошла обшибка")
    elif command == 3:
        print("Введите token")
        TOKEN = input()
    elif command == 4:
        print("Введите folder id")
        ID_FOLDER = input()
    # else:
    #     print("Команда введена неверно")
    #     print(command)
    print()
    print_menu()
    command = int(input())
