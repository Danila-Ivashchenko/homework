import json
import requests


URL = "https://stt.api.cloud.yandex.net/speech/v1/stt:recognize"
TOKEN = "t1.9euelZrKysfPk5yRlozJmMmJjsuZk-3rnpWais-QkJ7OlZOcic6Llpaenprl8_cIUyVj-e8pcBk1_N3z90gBI2P57ylwGTX8.wJ0IJmXJKTbutP8aSjhT36vHZWT6csFnNj_LWl3Lxc7wEyc4HoKg7tGF25UxboKVUHLsPhnEamaGdIrwrUrVDw"
ID_FOLDER = "b1gtf3dqupicap0o7l1v"

def read_file(filename):
    with open(filename, "rb") as f:
        file = f.read()
    return file

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

def text_to_audio(text,TOKEN, ID_FOLDER, lang='ru-RU', voice="alena", emotion="neutral", filename="new_file.ogg"):
    headers, params = set_t_to_a_params(text, TOKEN, ID_FOLDER, lang, voice, emotion)
    url =  "https://tts.api.cloud.yandex.net/speech/v1/tts:synthesize"
    responce = requests.post(url, params=params, headers=headers)
    chunks = responce.iter_content(chunk_size=1024)
    with open(filename, "wb") as out:
        for chunk in chunks:
            out.write(chunk)
    return True

text_to_audio("Федя хох)", TOKEN, ID_FOLDER, voice="filipp", emotion="good", filename="about_feador.ogg")
# print(audio_to_text("new_file.ogg", TOKEN, ID_FOLDER))