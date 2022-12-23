import requests

URL = 'https://translate.api.cloud.yandex.net/translate/v2/translate'

def get_text(filename):
    text = ""
    try:
        with open(filename, "r", encoding="UTF-8") as f:
            for line in f.readlines():
                text += line
    except:
        text = "no_such_file"
    return text

def set_params(text, lang, im_token, folder_id):
    body = {
        "targetLanguageCode": lang,
        "texts": text,
        "folderId": folder_id,
    }
    headers = {
        "Content-Type": "application/json",
        "Authorization": "Bearer {0}".format(im_token)
    }
    return body, headers

def translate(text, lang, im_token, folder_id):
    body, headers = set_params(text, lang, im_token, folder_id)
    response = requests.post(URL, json=body, headers = headers).json()
    return response['translations'][0]['text']


def write_to_file(filename, text):
    with open(filename, 'w', encoding="UTF-8") as f:
        f.write(text)
    return True


def print_menu():
    print("[1] Перевести текст из файла")
    print("[2] Перевести введённый текст")
    print("[3] Установить параметры")
    print("[4] Выход")

IM_TOKEN = ""
FOLDER_ID = ""
# IM_TOKEN = 't1.9euelZqZjJPOjMnGmMfHj4yOzZLLzO3rnpWais-QkJ7OlZOcic6Llpaenprl8_dtdHti-e9MWyFW_t3z9y0jeWL570xbIVb-.zkuN0jopjD2InalJun3-ZUbAQWDzI1UvAT2bwGBuDWh8B1iwbBRpGxT4jOHNtElSZihpl-lmXhtJNWLvDYSDBA'
# FOLDER_ID = 'b1gtf3dqupicap0o7l1v'

command = 0
print("Yandex переводчик")
print()
command = 3
while command != 4:
    if command == 0:
        pass
    if command == 1:
        filename = input("Введите имя файла - ")
        text = get_text(filename)
        if text == "no_such_file":
            print(f"{filename} не находится в данной директории")
        else:
            lang = input("Введите язык, на который необходимо перевести - ")
            new_text = translate(text, lang, IM_TOKEN, FOLDER_ID)
            if write_to_file('new_' + filename, new_text):
                print("Файл успешно переведён")
    elif command == 2:
        text = input("Введите текст для перевода - ")
        lang = input("Введите язык, на который необходимо перевести - ")
        new_text = translate(text, lang, IM_TOKEN, FOLDER_ID)
        print(new_text)
    elif command == 3:
        IM_TOKEN = input("Введите IAM_TOKEN - ")
        FOLDER_ID = input("Введите FOLDER_ID - ")
    else:
        print("Команда введена неверно")
    print()
    print_menu()
    print()
    command = int(input("Введите команду - "))




print(translate("соси бибу", "en", IM_TOKEN, FOLDER_ID))
